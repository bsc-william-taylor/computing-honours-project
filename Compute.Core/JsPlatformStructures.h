
#pragma once

#include "ComputeCore.h"

using Concurrency::concurrent_vector;
using Concurrency::concurrent_queue;

class JsTaskQueue
{
    concurrent_queue<v8::Task*> elements;
    std::atomic<int> size;
public:
    JsTaskQueue();
    ~JsTaskQueue();
   
    void push(v8::Task* task);
    void pop();

    int length();
};

class JsTaskBuffer
{
    std::vector<v8::Task*> buffer;
    std::mutex mutex;
public:
    JsTaskBuffer();
    ~JsTaskBuffer();

    int length();

    std::vector<v8::Task*> acquire();
    void push(v8::Task* task);
};

class JsBackgroundThread
{
    std::function<void()> threadMain;
    std::atomic<bool> dispose;
    std::thread thread;
public:
    JsBackgroundThread();
    ~JsBackgroundThread();

    void start(std::function<void()> start);
    void join();
};
