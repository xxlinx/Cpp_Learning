#ifndef __MYTIME__
#define __MYTIME__

class Time {
public:
	//Time(int tmphour, int tmpmin, int tmpsec=12);	
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	explicit Time();
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);

public:
	//���ֱ����ͷ�ļ��ﶨ��ĺ����� ����inline ������������ 
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
	int Second;
	void initTime(int tmphour, int tmpmin, int tmpsec);

	mutable int myHour;  //Сʱ  
	// ��ʾ�����Ա���������޸ģ���const��Ա������Ҳ�����޸�

public:
	static int mystatic;   //������̬��Ա ��û�ж��� ��û�з����ڴ棬 ���������ʼ��
	static void mstafunc(int testvalue);


private:
	int Millisecond;
private:
	void initMillTime(int mls);

};




#endif