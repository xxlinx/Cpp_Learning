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


void Human::samenamefunc()
{
	std::cout << "执行了Human::samenamefunc()" << std::endl;
}
void Human::samenamefunc(int)
{
	std::cout << "执行了Human::samenamefunc(int)" << std::endl;
}
