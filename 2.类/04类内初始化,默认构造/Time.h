#pragma once
class Time {
public:
	//Time(int tmphour, int tmpmin, int tmpsec=12);	
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	explicit Time();
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);

public:
	void addhour(int tmphour)
	{
		Hour += tmphour;
	}
	void noone() const
	{
		//Hour += 10; //���󣬳�����Ա�����������޸ĳ�Ա����ֵ
		myHour += 3; //�Ѿ���ȷ��
	}
	void noone2() const;
public:
	Time& rtnhour(int tmphour); //�������������
	Time& rtnminute(int tmpminute); //�������������

public:
	int Hour;
	int Minute;
	//int Second;
	//���ڳ�ʼֵ
	int Second{ 0 };  //����int Second = 0; ����д��������

	void initTime(int tmphour, int tmpmin, int tmpsec);
	mutable int myHour;  //Сʱ
	const int testvalue = 19; //��Ȼ������Ը���ֵ���磺const int testvalue=19;

public:
	static int mystatic;   //������û�ж���
	static void mstafunc(int testvalue);


private:
	int Millisecond;
private:
	void initMillTime(int mls);


};

void WriteTime(Time& mytime); //�����������β������ã������˶��󿽱�������Ч�����


