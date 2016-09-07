
#include "Http.h"
#include "JsRuntime.h"
#include "JsExtensions.h"

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
    v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> callback;
    callback.Reset(v8::Isolate::GetCurrent(), args[3].As<v8::Function>());

    v8::String::Utf8Value domainUtf(args[0].As<v8::String>());
    v8::String::Utf8Value routeUtf(args[1].As<v8::String>());

    std::string domain = *domainUtf;
    std::string route = *routeUtf;

    auto port = args[2].As<v8::Number>()->Value();
    auto& platform = JsRuntime::getPlatform();
    auto isolate = v8::Isolate::GetCurrent();
    
    platform.CallOnBackgroundThread(new JsAsyncTask(Multi, [=](JsPlatform& innerPlatform) {
        auto result = httpRequest(Poco::Net::HTTPRequest::HTTP_GET, domain, route, port);
        innerPlatform.CallOnForegroundThread(isolate, new JsAsyncTask([=]() {
            auto value = v8::String::NewFromUtf8(isolate, result.c_str());
            auto function = callback.Get(isolate);
            v8::TryCatch trycatch(isolate);
            function->Call(function, 0, nullptr);
            CatchExceptions(trycatch);
        }));
    }), v8::Platform::ExpectedRuntime::kLongRunningTask);
}

void raster::registerHttp(v8::Local<v8::Object>& object)
{
    const auto isolate = v8::Isolate::GetCurrent();

    object->Set(v8::String::NewFromUtf8(isolate, "post"), v8::Function::New(isolate, http::httpPost));
    object->Set(v8::String::NewFromUtf8(isolate, "get"), v8::Function::New(isolate, http::httpGet));
}
