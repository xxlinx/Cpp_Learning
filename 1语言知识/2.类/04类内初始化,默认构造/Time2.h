#pragma once
//��ʾĬ�Ϲ��캯��
class Time2 {
public:
	//explicit Time2();  //explicit��ֹ��ʽ����ת��
	//Time2()=default;
	Time2();  //�������� ������Ĭ�Ϲ���
	//Time2(int itmpvalue)=delete;	
	//Time2()=delete;

public:
	int Hour;
	int Minute;
	int Second{ 0 };		
	
};  

