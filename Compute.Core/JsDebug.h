
#pragma once

#include "ComputeCore.h"

struct DebugData : public v8::Debug::ClientData
{
    int socket;
};

template<typename S>
std::vector<uint16_t> ToUInt16Vector(const S& str)
{
    size_t s = str.size();
    std::vector<uint16_t> data(s);

    for (size_t i = 0; i < s; ++i)
    {
        if (str[i] != 0)
            data[i] = static_cast<uint16_t>(str[i]);
        else
            data[i] = ' ';
    }

    return data;
}

std::string GetRequest(int socket);

void SendMessage(int socket, const std::string& message);
void SendBuffer(int socket, const std::string& message);

void DebuggerAgentMessageHandler(const v8::Debug::Message& message);
void DebuggerThread(v8::Isolate * isolate);
void DebugEventHandler(const v8::Debug::EventDetails& details);