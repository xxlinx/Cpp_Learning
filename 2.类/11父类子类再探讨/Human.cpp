#include "Human.h"
#include <iostream>

Human::Human()
{
	std::cout << "执行了Human::Human()构造函数" << std::endl;
}

Human::Human(int age)
{
	std::cout << "执行了Human::Human(int age)构造函数" << std::endl;
}

Human::Human(const Human& tmphuman)
{
	std::cout << "执行了Human::Human(const Human& tmphuman)拷贝构造函数" << std::endl;
};

Human& Human::operator=(const Human& tmphuman)
{
	std::cout << "执行了operator=(const Human& tmphuman)" << std::endl;
	return *this;
}


void Human::samenamefunc()
{
	std::cout << "执行了Human::samenamefunc()" << std::endl;
}
void Human::samenamefunc(int)
{
	std::cout << "执行了Human::samenamefunc(int)" << std::endl;
}

void Human::eat()
{
	std::cout << "人类吃各种粮食" << std::endl;
};

Human::~Human()
{
	std::cout << "执行了Human::~Human()析构函数" << std::endl;
}