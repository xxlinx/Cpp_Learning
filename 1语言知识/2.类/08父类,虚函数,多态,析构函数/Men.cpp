

#include "Men.h"
#include <iostream>
Men::Men()
{
	std::cout << "ִ����Men::Men()���캯��" << std::endl;
}

void Men::samenamefunc(int)
{
	Human::samenamefunc();    //���Ե��ø�����޲ε�samenamefunc����
	Human::samenamefunc(120); //���Ե��ø���Ĵ�һ��������samenamefunc����
	std::cout << "ִ����void Men::samenamefunc(int)" << std::endl;
	samenamefunc(); //ִ�и�����޲ε�samenamefunc����
}

void Men::eat()
{
	std::cout << "����ϲ�����׷�" << std::endl;
};

Men::~Men()
{
	std::cout << "ִ����Men::~Men()��������" << std::endl;
}