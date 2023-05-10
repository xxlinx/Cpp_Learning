#pragma once
//演示默认构造函数
class Time2 {
public:
	//explicit Time2();  //explicit禁止隐式类型转换
	//Time2()=default;
	Time2();  //不带参数 ，就是默认构造
	//Time2(int itmpvalue)=delete;	
	//Time2()=delete;

public:
	int Hour;
	int Minute;
	int Second{ 0 };		
	
};  

