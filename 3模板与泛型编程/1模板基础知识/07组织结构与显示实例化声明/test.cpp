#include <iostream>
#include <vector>
#include "ca.h"
using namespace std;

//��ʾʵ����
template  A<float>;  //���"ʵ��������"��ֻ��һ��.cpp�ļ�������д��������Ϊ�����ɴ���
template void myfunc(int& v1, int& v2); //����ģ��ʵ�������壬��������Ϊ������ʵ��������

void mfunc()
{
	A<float> a(1, 2);
	//a.myft(3);
}