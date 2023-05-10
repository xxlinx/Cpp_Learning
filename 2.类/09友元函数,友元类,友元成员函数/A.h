#ifndef __A__
#define __A__

#include <iostream>

#include "B.h"

class A
{
	friend void B::callBAF(int x, A& a); //声明类B的callBAF成员函数是本类（A类）的友元成员函数

private:
	int data;
};

#endif

