#include <iostream>
#include "Time.h"

//ע��������ͨ���������ǳ�Ա����
void WriteTime(Time& mytime)
{
	std::cout << mytime.Hour << std::endl;
}

//����������ð�ŽУ����������������ʾinitTime��������Time�ࡣ�����ж����ͬ���࣬��������Ҳ�����н�initTime()�ĳ�Ա�������������������Time::�������ú�������Time��
void Time::initTime(int tmphour, int tmpmin, int tmpsec)
{
	Hour = tmphour;  //ע�⵽����Ա�����п���ֱ��ʹ�ó�Ա������
	//�ĸ�������õĸó�Ա��������ô��Щ��Ա�����������ĸ����󡣿����������Ա����֪���ĸ�������õ��Լ�
	Minute = tmpmin;
	Second = tmpsec;

	initMillTime(0);
}
void Time::initMillTime(int mls)
{
	Millisecond = mls;
}

//���캯����ʵ��
//Time::Time(int tmphour, int tmpmin, int tmpsec)
Time::Time(int tmphour, int tmpmin, int tmpsec)
	:Hour(tmphour), Minute(tmpmin), //��ͽй��캯����ʼ���б�
	testvalue(18)

{
	//testvalue = 6;  //�����������ʼ������
	Hour = tmphour;
	Minute = tmpmin;
	Second = tmpsec;
	initMillTime(0);
}
//���캯��
Time::Time()
{
	this->Hour = 12; //ǰ���this�ǿ��Եģ���û��Ҫ
	Minute = 59;
	Second = 59;
	initMillTime(59);
}
//���캯��
Time::Time(int tmphour, int tmpmin)
{
	Hour = tmphour;
	Minute = tmpmin;
	Second = 59;
	initMillTime(59);
}
//��һ�������Ĺ��캯��
Time::Time(int tmphour)
{
	Hour = tmphour;
	Minute = 59;
	Second = 59;
	initMillTime(0);
}

Time& Time::rtnhour(int tmphour)
{
	Hour += tmphour;
	return *this; //�Ѷ�����������
}

Time& Time::rtnminute(int tmpminute)
{
	Minute += tmpminute; //������ݽ������β�Ҳ��Minute����ô��Ա����Minute����д��this.Minute�Ժ��β������𣬴���ͱ�ɣ�this.Minute += Minute
	return *this;        //�Ѷ�����������
}

void Time::mstafunc(int testvalue)
{
	//Minute = testvalue;  //���󣬺Ͷ�����صĳ�Ա���������ܳ����ھ�̬��Ա������
	mystatic = testvalue; //�������
}

void Time::noone2() const
{
}