#pragma once

class Time {
public:
	//Time(int tmphour, int tmpmin, int tmpsec=12);	
	explicit Time(int tmphour, int tmpmin, int tmpsec);   //3�������Ĺ���
	explicit Time();   //�޲�������
	Time(int tmphour, int tmpmin);   //2�������Ĺ���
	explicit Time(int tmphour);   //����������
public:
	int Hour;
	int Minute;
	int Second;
	void initTime(int tmphour, int tmpmin, int tmpsec);

private:
	int Millisecond;
private:
	void initMillTime(int mls);

};

class A
{
public:
	void mufunc() //��Ա����������
	{
		//ʵ�ִ���д������
		//.....
	}
};

