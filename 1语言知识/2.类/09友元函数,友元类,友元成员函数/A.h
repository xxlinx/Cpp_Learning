#ifndef __A__
#define __A__

#include <iostream>

#include "B.h"

class A
{
	friend void B::callBAF(int x, A& a); //������B��callBAF��Ա�����Ǳ��ࣨA�ࣩ����Ԫ��Ա����

private:
	int data;
};

#endif

