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
