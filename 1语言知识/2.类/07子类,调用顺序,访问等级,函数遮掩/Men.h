#pragma once

#include "Human.h"
class Men : public Human
{
public:
	using Human::samenamefunc; //using声明让父类函数在子类可见

public:
	Men();
public:
	void samenamefunc(int);

};

