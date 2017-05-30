
#include "JsPlatformStructures.h"
#include "JsExtensions.h"

JsTaskBuffer::JsTaskBuffer()
{
}

JsTaskBuffer::~JsTaskBuffer()
{
}

std::vector<v8::Task*> JsTaskBuffer::acquire()
{
    mutex.lock();
    auto elements = move(buffer);
    mutex.unlock();
    return move(elements);
}

int JsTaskBuffer::length()
{
    return buffer.size();
}

void JsTaskBuffer::push(v8::Task* task)
{
    mutex.lock();
    buffer.push_back(task);
    mutex.unlock();
}

JsBackgroundThread::JsBackgroundThread()
    : dispose(false)
{
}

JsBackgroundThread::~JsBackgroundThread()
{
}

void JsBackgroundThread::start(std::function<void()> start)
{
    threadMain = start;
    thread = std::thread([&]() 
    {
        while(!dispose)
        {
            threadMain();
        }
    });
}

void JsBackgroundThread::join()
{
    dispose = true;
    thread.join();
}

JsTaskQueue::JsTaskQueue()
: size(0)
{
}

JsTaskQueue::~JsTaskQueue()
{
}

void JsTaskQueue::pop()
{
    v8::Task* task;
    if(elements.try_pop(task))
    {
        Run(task);
        size -= 1;
    }
}

void JsTaskQueue::push(v8::Task* task)
{
    size += 1;
    elements.push(task);
}

int JsTaskQueue::length()
{
    return size;
}