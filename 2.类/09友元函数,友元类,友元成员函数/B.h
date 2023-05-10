#ifndef __B__
#define __B__

#include <iostream>

class A;//类声明，仅仅声明了有A这样一个类型，因为可能类A的定义在类B之后，而在本.h文件中类B的定义又用到了类A，所以这里先做个类声明，这样编译就不会报错

class B
{
public:
	void callBAF(int x, A& a);
};

#endif

