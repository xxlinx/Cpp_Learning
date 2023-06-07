

#include "Men.h"
#include <iostream>
Men::Men()
{
	std::cout << "执行了Men::Men()构造函数" << std::endl;
}

void Men::samenamefunc(int)
{
	Human::samenamefunc();    //可以调用父类的无参的samenamefunc函数
	Human::samenamefunc(120); //可以调用父类的带一个参数的samenamefunc函数
	std::cout << "执行了void Men::samenamefunc(int)" << std::endl;
	samenamefunc(); //执行父类的无参的samenamefunc函数
}

void Men::eat() 
{
	std::cout << "男人喜欢吃米饭" << std::endl;
};

Men::~Men()
{
	std::cout << "执行了Men::~Men()析构函数" << std::endl;
}