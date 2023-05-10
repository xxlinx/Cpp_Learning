#include "Time.h"


//其中这两个冒号叫：作用域运算符，表示initTime函数属于Time类。可能有多个不同的类，其他类中也可能有叫initTime()的成员函数，所以这里必须用Time::来表明该函数属于Time类
void Time::initTime(int tmphour, int tmpmin, int tmpsec)
{
	Hour = tmphour;  //注意到，成员函数中可以直接使用成员变量名
	//哪个对象调用的该成员函数，那么这些成员变量就属于哪个对象。可以理解成类成员函数知道哪个对象调用的自己
	Minute = tmpmin;
	Second = tmpsec;

	initMillTime(0);
}
void Time::initMillTime(int mls)
{
	Millisecond = mls;
}
