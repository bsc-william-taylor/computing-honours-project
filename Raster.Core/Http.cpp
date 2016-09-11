
#include "Http.h"
#include "JsExtensions.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

std::string httpRequest(const std::string& method, std::string domain, std::string route, int port)
{
    HTTPClientSession session(domain);
    HTTPRequest request(method, route);
    HTTPResponse response;
   
    session.setPort(port);
    session.sendRequest(request);

    std::stringstream ss;
    Poco::StreamCopier::copyStream(session.receiveResponse(response), ss);
    return ss.str();
}

void raster::http::httpPost(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    // TODO: Implement post method
}

void raster::http::httpGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::String::Utf8Value domainUtf(args[0].As<v8::String>());
    v8::String::Utf8Value routeUtf(args[1].As<v8::String>());

    auto port = args[2].As<v8::Number>()->Value();
    auto isolate = v8::Isolate::GetCurrent();    
    auto result = httpRequest(HTTPRequest::HTTP_GET, *domainUtf, *routeUtf, port);
   
    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, result.c_str()));
}

void raster::registerHttp(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "post", http::httpPost);
    AttachFunction(object, "get", http::httpGet);
}
