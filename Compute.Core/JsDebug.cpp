
#include <SDL_assert.h>
#include "JsDebug.h"

#define TRACE printf

const int debugging_port = 5858;

void SendBuffer(int socket, const std::string& message)
{
    int n = send(socket, message.c_str(), message.size(), 0);
    SDL_assert(n >= 0);//, "ERROR writing to socket (%d)", WSAGetLastError());
}

void SendMessage(int socket, const std::string& message)
{
    // Send the header.
    std::stringstream ss;
    ss << "Content-Length";
    ss << ": ";
    ss << message.size();
    ss << "\r\n";

    SendBuffer(socket, ss.str()); //StringUtils::SPrintf("%s: %d\r\n", kContentLength, message.size()));                        
    SendBuffer(socket, "\r\n");   // Terminate header with empty line.
    SendBuffer(socket, message);  // Send message body as UTF-8.
}

void DebuggerAgentMessageHandler(const v8::Debug::Message& message)
{
    auto clientData = message.GetClientData();
    auto socket = 0;//_main_debug_client_socket;

    DebugData* cd = static_cast<DebugData*>(clientData);
    if (cd != nullptr)
        socket = cd->socket;

    if (socket <= 0)
        return;

    v8::String::Utf8Value val(message.GetJSON());
    SendMessage(socket, *val);
}

std::string GetRequest(int socket)
{
    int received;

    // Read header.
    int content_length = 0;
    while (true)
    {
        const int kHeaderBufferSize = 80;
        char header_buffer[kHeaderBufferSize];
        int header_buffer_position = 0;
        char c = '\0';  // One character receive buffer.
        char prev_c = '\0';  // Previous character.

                             // Read until CRLF.
        while (!(c == '\n' && prev_c == '\r'))
        {
            prev_c = c;
            received = recv(socket, &c, 1, 0);
            int wsa_error = WSAGetLastError();
            if (wsa_error == WSAECONNRESET)
                return std::string();
            SDL_assert(received >= 0);//, "ERROR reading from socket (%d)", wsa_error);

            // Add character to header buffer.
            if (header_buffer_position < kHeaderBufferSize) {
                header_buffer[header_buffer_position++] = c;
            }
        }

        // Check for end of header (empty header line).
        // Receive buffer contains CRLF.
        if (header_buffer_position == 2)
        {
            break;
        }

        // Terminate header.
        SDL_assert(header_buffer_position > 1);  // At least CRLF is received.
        SDL_assert(header_buffer_position <= kHeaderBufferSize);
        header_buffer[header_buffer_position - 2] = '\0';

        // Split header.
        char* key = header_buffer;
        char* value = nullptr;
        for (int i = 0; header_buffer[i] != '\0'; i++)
        {
            if (header_buffer[i] == ':')
            {
                header_buffer[i] = '\0';
                value = header_buffer + i + 1;
                while (*value == ' ')
                {
                    value++;
                }
                break;
            }
        }

        // Check that key is Content-Length.
        if (stricmp(key, "Content-Length") == 0)
        {
            // Get the content length value if present and within a sensible range.
            if (value == nullptr || strlen(value) > 7)
            {
                return std::string();
            }
            for (int i = 0; value[i] != '\0'; i++)
            {
                // Bail out if illegal data.
                if (value[i] < '0' || value[i] > '9')
                {
                    return std::string();
                }
                content_length = 10 * content_length + (value[i] - '0');
            }
        }
        else
        {
            // For now just print all other headers than Content-Length.
            TRACE("%s: %s\n", key, value != nullptr ? value : "(no value)");
        }
    }

    // Return now if no body.
    if (content_length == 0)
    {
        return std::string();
    }

    // Read body.
    std::string buffer;
    buffer.resize(content_length);
    received = recv(socket, &buffer[0], content_length, 0);
    if (received < content_length)
    {
        TRACE("Error request data size\n");
        return std::string();
    }

    buffer[content_length] = '\0';
    return buffer;
}


void DebuggerThread(v8::Isolate * isolate, DebugMessage incoming)
{
    WSADATA wsa_data = { 0 };

    // Initialize Winsock
    int ws_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    SDL_assert(ws_result == 0);//, "WSAStartup failed: %d", ws_result);

    int sockfd, client_socket, portno, clilen;
    sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    SDL_assert(sockfd >= 0);//, "ERROR opening socket (%d)", WSAGetLastError());

    ::ZeroMemory(reinterpret_cast<char *>(&serv_addr), sizeof(serv_addr));
    portno = debugging_port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    int bindResult = bind(sockfd, reinterpret_cast<sockaddr *>(&serv_addr), sizeof(serv_addr));
    SDL_assert(bindResult >= 0);//, "ERROR on binding (%d)", WSAGetLastError());

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1)
    {
        client_socket = accept(sockfd, reinterpret_cast<sockaddr *>(&cli_addr), &clilen);
        SDL_assert(client_socket >= 0);

        TRACE("Client connected to debugger.\n");

        std::stringstream ss1, ss2;
        ss1 << "V8-Version: ";
        ss1 << v8::V8::GetVersion();
        ss1 << "\r\n";

        ss2 << "Embedding-Host: ";
        ss2 << "Compute";
        ss2 << "\r\n";

        // Say hello
        SendBuffer(client_socket, "Type: connect\r\n");
        SendBuffer(client_socket, ss1.str());
        SendBuffer(client_socket, "Protocol-Version: 1\r\n");
        SendBuffer(client_socket, ss2.str());
        SendBuffer(client_socket, "Content-Length: 0\r\n");
        SendBuffer(client_socket, "\r\n");

        while (1)
        {
            // Get request
            std::string request = GetRequest(client_socket);

            if (request.empty())
                break;

            bool is_closing_session = (request.empty());

            if (is_closing_session)
            {
                // If we lost the connection, then simulate a disconnect msg:
                request = "{\"seq\":1,\"type\":\"request\",\"command\":\"disconnect\"}";
            }
            else
            {
                // Check if we're getting a disconnect request:
                const char* disconnect_request_str = "\"type\":\"request\",\"command\":\"disconnect\"}";
                const char* result = strstr(request.c_str(), disconnect_request_str);
                if (result != nullptr)
                {
                    is_closing_session = true;
                }
            }


            auto buffer = ToUInt16Vector(request);
            auto debug = new DebugData;
            debug->socket = client_socket;

            incoming(buffer, debug);
            //v8::Debug::SendCommand(isolate, &data[0], data.size(), debug);

            if (is_closing_session)
            {
                // Session is closed.
                break;
            }
        }

        TRACE("Client disconnected from debugger.\n");
    }

    WSACleanup();
}

void DebugEventHandler(const v8::Debug::EventDetails& details)
{
    switch (details.GetEvent())
    {
        case v8::DebugEvent::Break: std::cout << "BREAK_DEBUG_EVENT" << std::endl; break;
        case v8::DebugEvent::Exception: std::cout << "EXCEPTION_DEBUG_EVENT" << std::endl; break;
        case v8::DebugEvent::NewFunction: std::cout << "NEW_FUNCTION_DEBUG_EVENT" << std::endl; break;
        case v8::DebugEvent::BeforeCompile:std::cout << "BEFORE_COMPILE_DEBUG_EVENT" << std::endl; break;
        case v8::DebugEvent::AfterCompile:std::cout << "AFTER_COMPILE_DEBUG_EVENT" << std::endl;  break;
        case v8::DebugEvent::CompileError:std::cout << "COPILE_ERROR_DEBUG_EVENT" << std::endl; break;
        case v8::DebugEvent::AsyncTaskEvent:std::cout << "ASYNC_TASK_DEBUG_EVENT" << std::endl;  break;
    }
}