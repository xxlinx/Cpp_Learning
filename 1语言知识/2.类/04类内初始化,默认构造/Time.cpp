#include <iostream>
#include "Time.h"

//注意这是普通函数，不是成员函数
void WriteTime(Time& mytime)
{
	std::cout << mytime.Hour << std::endl;
}

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

//构造函数的实现
//Time::Time(int tmphour, int tmpmin, int tmpsec)
Time::Time(int tmphour, int tmpmin, int tmpsec)
	:Hour(tmphour), Minute(tmpmin), //这就叫构造函数初始化列表
	testvalue(18)

{
	//testvalue = 6;  //不可以在这初始化常量
	Hour = tmphour;
	Minute = tmpmin;
	Second = tmpsec;
	initMillTime(0);
}
//构造函数
Time::Time()
{
	this->Hour = 12; //前面加this是可以的，但没必要
	Minute = 59;
	Second = 59;
	initMillTime(59);
}
//构造函数
Time::Time(int tmphour, int tmpmin)
{
	Hour = tmphour;
	Minute = tmpmin;
	Second = 59;
	initMillTime(59);
}
//带一个参数的构造函数
Time::Time(int tmphour)
{
	Hour = tmphour;
	Minute = 59;
	Second = 59;
	initMillTime(0);
}

Time& Time::rtnhour(int tmphour)
{
	Hour += tmphour;
	return *this; //把对象自身返回了
}

Time& Time::rtnminute(int tmpminute)
{
	Minute += tmpminute; //如果传递进来的形参也叫Minute，那么成员变量Minute可以写成this.Minute以和形参做区别，代码就变成：this.Minute += Minute
	return *this;        //把对象自身返回了
}

void Time::mstafunc(int testvalue)
{
	//Minute = testvalue;  //错误，和对象相关的成员变量，不能出现在静态成员函数中
	mystatic = testvalue; //这个可以
}

void Time::noone2() const
{
}