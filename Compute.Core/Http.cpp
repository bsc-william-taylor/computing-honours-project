
#include "Http.h"
#include "JsExtensions.h"
#include "JsRuntime.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPRequest;

const auto Callback = [](v8::PersistentCopyable callback, std::string response)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto function = callback.Get(isolate);

    v8::Local<v8::Value> args[1];
    args[0] = v8::NewString(response);
    function->Call(function, 1, args);
};

const auto Send = [](auto callback, auto domain, auto route, auto port)
{
    HTTPClientSession session(domain);
    HTTPRequest request(HTTPRequest::HTTP_GET, route);
    HTTPResponse response;

    session.setPort(port);
    session.sendRequest(request);

    std::stringstream ss;
    Poco::StreamCopier::copyStream(session.receiveResponse(response), ss);
    v8::OnForeground<JsAsyncTask>(Callback, callback, ss.str());
};

void httpPost(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    // TODO: Implement post method
}

void httpGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto function = GetFunction(args[3]);
    auto domain = GetString(args[0]);
    auto route = GetString(args[1]);
    auto port = GetNumber(args[2]);
   
    v8::PersistentCopyable callback;
    callback.Reset(v8::Isolate::GetCurrent(), function);
    v8::OnBackground<JsAsyncTask>(Send, callback, domain, route, port);
}

void compute::registerHttp(v8::Local<v8::Object>& object)
{
    AttachFunction(object, "post", httpPost);
    AttachFunction(object, "get", httpGet);
}
