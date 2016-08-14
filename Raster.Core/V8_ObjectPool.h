
#pragma once

#include "Common.h"
#include <functional>

struct V8_BoundObject
{
	std::unique_ptr<void *> boundObject;
	std::function<void()> deleteHandler;
	std::function<void()> createHandler;
};

class V8_ObjectPool
{
public:
	
};
