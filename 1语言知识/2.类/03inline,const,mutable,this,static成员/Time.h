#ifndef __MYTIME__
#define __MYTIME__

class Time {
public:
	//Time(int tmphour, int tmpmin, int tmpsec=12);	
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	explicit Time();
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);

public:
	//这个直接在头文件里定义的函数， 当作inline 内联函数处理 
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
	int Second;
	void initTime(int tmphour, int tmpmin, int tmpsec);

	mutable int myHour;  //小时  
	// 表示这个成员变量可以修改，在const成员函数里也可以修改

public:
	static int mystatic;   //声明静态成员 但没有定义 还没有分配内存， 不能在这初始化
	static void mstafunc(int testvalue);


private:
	int Millisecond;
private:
	void initMillTime(int mls);

};




#endif