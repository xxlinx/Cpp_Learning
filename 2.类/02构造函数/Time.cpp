#include "Time.h"


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
	:Hour(tmphour), Minute(tmpmin) //��ͽй��캯����ʼ���б�

{
	Hour = tmphour;
	Minute = tmpmin;
	Second = tmpsec;
	initMillTime(0);
}
//���캯��
Time::Time()
{
	Hour = 12;
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