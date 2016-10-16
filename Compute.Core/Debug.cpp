
#include "Debug.h"
#include "JsDebug.h"
#include "JsRuntime.h"

v8::Persistent<v8::Function> incomingCallback;
v8::Persistent<v8::Function> outgoingCallback;
v8::Isolate * Isolate = nullptr;
std::thread background;

void sendMessage(v8::FunctionArgs args)
{
    //v8::Debug::ProcessDebugMessages(args.GetIsolate());
    /*
    auto d = new DebugData();
    auto num = GetNumber(args[1]);
    v8::String::Value v(args[0]);
    d->socket = num;
    v8::Debug::SendCommand(args.GetIsolate(), *v, v.length(), d);
    v8::Debug::ProcessDebugMessages(args.GetIsolate());
*/
}

auto invokeFunction = [](std::vector<uint16_t> message, DebugData* data)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto arg1 = v8::String::NewFromTwoByte(isolate, message.data(), v8::String::kNormalString, message.size());
    auto arg2 = v8::Number::New(isolate, data->socket);

    v8::Local<v8::Value> args[2];
    args[0] = arg1;
    args[1] = arg2;

    v8::Debug::ProcessDebugMessages(isolate);
    v8::TryCatch trycatch(isolate);
    auto function = incomingCallback.Get(isolate);
    function->Call(function, 2, args);
    CatchExceptions(trycatch);
};

auto incoming = [](auto msg, auto d)
{
    if(Isolate != nullptr)
    {
        v8::OnForeground<JsAsyncTask>(invokeFunction, msg, d);
        v8::Debug::SendCommand(Isolate, &msg[0], msg.size(), d);
    }
};


auto invokeOutgoing = [](auto message)
{
    auto isolate = v8::Isolate::GetCurrent();

    v8::Debug::ProcessDebugMessages(isolate);
    v8::Local<v8::Value> args[1];
    v8::TryCatch trycatch(isolate);
    args[0] = v8::NewString(message);

    auto function = outgoingCallback.Get(isolate);
    function->Call(function, 1, args);
    CatchExceptions(trycatch);
};

void outgoing(const v8::Debug::Message& message)
{
    auto string = GetString(message.GetJSON());
    v8::OnForeground<JsAsyncTask>(invokeOutgoing, string);
    DebuggerAgentMessageHandler(message);
};

void initDebug(v8::FunctionArgs args)
{
    auto isolate = args.GetIsolate();

    background = std::thread([=]() { DebuggerThread(isolate, incoming); });
    background.detach();

    v8::Debug::SetMessageHandler(isolate, outgoing);
}

void debugBreak(v8::FunctionArgs args)
{
    v8::Debug::DebugBreak(args.GetIsolate());
}

void on(v8::FunctionArgs args)
{
    if(args.Length() == 2)
    {
        incomingCallback.Reset(args.GetIsolate(), args[0].As<v8::Function>());
        outgoingCallback.Reset(args.GetIsolate(), args[1].As<v8::Function>());
    }
}

void getPID(v8::FunctionArgs args)
{
    args.GetReturnValue().Set((int)GetCurrentProcessId());
}


void compute::registerDebug(v8::Exports exports)
{
    Isolate = v8::Isolate::GetCurrent();

    AttachFunction(exports, "debugBreak", debugBreak);
    AttachFunction(exports, "send", sendMessage);
    AttachFunction(exports, "init", initDebug);
    AttachFunction(exports, "on", on);
    AttachFunction(exports, "get", getPID);
}