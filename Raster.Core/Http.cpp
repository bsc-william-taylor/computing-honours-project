
#include "Http.h"

std::string httpRequest(const std::string& method, std::string domain, std::string route, int port)
{
    Poco::Net::HTTPClientSession session(domain);
    Poco::Net::HTTPRequest request(method, route);
    Poco::Net::HTTPResponse response;
   
    session.setPort(port);
    session.sendRequest(request);

    std::stringstream ss;
    Poco::StreamCopier::copyStream(session.receiveResponse(response), ss);
    return ss.str();
}

void raster::http::httpPost(const v8::FunctionCallbackInfo<v8::Value>& args)
{
}

void raster::http::httpGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::String::Utf8Value domain(args[0].As<v8::String>());
    v8::String::Utf8Value route(args[1].As<v8::String>());
    auto port = args[2].As<v8::Number>()->Value();

    auto result = httpRequest(Poco::Net::HTTPRequest::HTTP_GET, *domain, *route, port);
    auto value = v8::String::NewFromUtf8(args.GetIsolate(), result.c_str());

    args.GetReturnValue().Set(value);
}

void raster::registerHttp(v8::Local<v8::Object>& object)
{
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(v8::String::NewFromUtf8(isolate, "post"), v8::Function::New(isolate, http::httpPost));
    object->Set(v8::String::NewFromUtf8(isolate, "get"), v8::Function::New(isolate, http::httpGet));
}
