#pragma once
class Time {
public:
	//Time(int tmphour, int tmpmin, int tmpsec=12);	
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	explicit Time();
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);

public:
	void addhour(int tmphour)
	{
		Hour += tmphour;
	}
	void noone() const
	{
		//Hour += 10; //错误，常量成员函数不可以修改成员变量值
		myHour += 3; //已经正确了
	}
	void noone2() const;
public:
	Time& rtnhour(int tmphour); //返回自身的引用
	Time& rtnminute(int tmpminute); //返回自身的引用

public:
	int Hour;
	int Minute;
	//int Second;
	//类内初始值
	int Second{ 0 };  //或者int Second = 0; 两种写法都可以

	void initTime(int tmphour, int tmpmin, int tmpsec);
	mutable int myHour;  //小时
	const int testvalue = 19; //当然这里可以给初值比如：const int testvalue=19;

public:
	static int mystatic;   //声明但没有定义
	static void mstafunc(int testvalue);


private:
	int Millisecond;
private:
	void initMillTime(int mls);


};

void WriteTime(Time& mytime); //函数声明，形参是引用，避免了对象拷贝产生的效率损耗


