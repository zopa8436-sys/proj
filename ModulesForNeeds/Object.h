#pragma once
#include "pch.h"


// базовый класс
class Object
{
public:
	virtual string toString() = 0;
	virtual bool equals(const Object &other) = 0;
};
