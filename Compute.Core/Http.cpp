
#include "Http.h"
#include "JsExtensions.h"
#include "JsRuntime.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPRequest;

const auto Callback = [](auto callback, auto response)
{
    auto isolate = v8::Isolate::GetCurrent();
    auto function = callback.Get(isolate);

    v8::Local<v8::Value> args[1];
    args[0] = v8::NewString(response);
    function->Call(function, 1, args);
};

const auto SendGetRequest = [](auto callback, auto domain, auto route, auto port)
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

const auto SendPostRequest = [](auto callback, auto domain, auto route, auto port, auto body)
{
    HTTPClientSession session(domain);
    HTTPRequest request(HTTPRequest::HTTP_POST, route);
    HTTPResponse response;

    request.setContentType("application/json");   
    request.setContentLength(body.length());

    session.setPort(port);
    session.sendRequest(request) << body;

    std::stringstream ss;
    Poco::StreamCopier::copyStream(session.receiveResponse(response), ss);
    v8::OnForeground<JsAsyncTask>(Callback, callback, ss.str());
};

void httpPost(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto function = GetFunction(args[3]);
    auto domain = GetString(args[0]);
    auto route = GetString(args[1]);
    auto port = GetNumber(args[2]);
    auto body = GetString(args[4]);

    v8::PersistentCopyable callback;
    callback.Reset(v8::Isolate::GetCurrent(), function);
    v8::OnBackground<JsAsyncTask>(SendPostRequest, callback, domain, route, port, body);
}

void httpGet(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto function = GetFunction(args[3]);
    auto domain = GetString(args[0]);
    auto route = GetString(args[1]);
    auto port = GetNumber(args[2]);
   
    v8::PersistentCopyable callback;
    callback.Reset(v8::Isolate::GetCurrent(), function);
    v8::OnBackground<JsAsyncTask>(SendGetRequest, callback, domain, route, port);
}

void compute::registerHttp(v8::Exports exports)
{
    AttachFunction(exports, "post", httpPost);
    AttachFunction(exports, "get", httpGet);
}
