
#ifndef __HUMAN__
#define __HUMAN__
#include <iostream>
class CSuiBian
{

};
class CSuiBian_Sub :public CSuiBian
{

};

class Human2
{
public:
	virtual void eat() = 0; //����һ�����麯��
};
class Human2_sub : public Human2
{
public:
	virtual void eat() //�������ʵ�ָ���Ĵ��麯���������ø����ഴ������
	{
		std::cout << "Human2_sub::eat()" << std::endl;
	}
};

class Human
{
public:
	Human();
	Human(int);
	virtual ~Human();

public:
	void samenamefunc();
	void samenamefunc(int);

	void funchuman() {};

	//����Ϊ�麯��
	virtual void eat();
	//virtual void eat() final;

	virtual CSuiBian* ovr() { return NULL; }

public:
	int m_Age;
	char m_Name[100];
	void funcpub() {};

protected:
	int m_pro1;
	void funcpor() {};

private:
	int m_priv1;
	void funcpriv() {};
};

#endif
