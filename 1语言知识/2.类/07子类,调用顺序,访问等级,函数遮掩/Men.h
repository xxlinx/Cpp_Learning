#pragma once

#include "Human.h"
class Men : public Human
{
public:
	using Human::samenamefunc; //using�����ø��ຯ��������ɼ�

public:
	Men();
public:
	void samenamefunc(int);

};

