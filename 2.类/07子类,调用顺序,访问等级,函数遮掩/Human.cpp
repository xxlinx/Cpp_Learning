#include "Human.h"
#include <iostream>

Human::Human()
{
	std::cout << "ִ����Human::Human()���캯��" << std::endl;
}

Human::Human(int age)
{
	std::cout << "ִ����Human::Human(int age)���캯��" << std::endl;
}


void Human::samenamefunc()
{
	std::cout << "ִ����Human::samenamefunc()" << std::endl;
}
void Human::samenamefunc(int)
{
	std::cout << "ִ����Human::samenamefunc(int)" << std::endl;
}
