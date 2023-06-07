#pragma once

class Time {
public:
	//Time(int tmphour, int tmpmin, int tmpsec=12);	
	explicit Time(int tmphour, int tmpmin, int tmpsec);   //3个参数的构造
	explicit Time();   //无参数构造
	Time(int tmphour, int tmpmin);   //2个参数的构造
	explicit Time(int tmphour);   //单参数构造
public:
	int Hour;
	int Minute;
	int Second;
	void initTime(int tmphour, int tmpmin, int tmpsec);

private:
	int Millisecond;
private:
	void initMillTime(int mls);

};

class A
{
public:
	void mufunc() //成员函数的声明
	{
		//实现代码写在这里
		//.....
	}
};

