#ifndef __B__
#define __B__

#include <iostream>

class A;//��������������������A����һ�����ͣ���Ϊ������A�Ķ�������B֮�󣬶��ڱ�.h�ļ�����B�Ķ������õ�����A��������������������������������Ͳ��ᱨ��

class B
{
public:
	void callBAF(int x, A& a);
};

#endif

