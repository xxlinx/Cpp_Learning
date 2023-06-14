#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

//class Grand //爷爷类
//{
//public:
//	int m_grand;
//};
//class A1 : public  Grand 
//{
//public:
//};
//class A2 : public  Grand
//{
//public:
//};
//class C1 :public A1, public A2
//{
//public:
//};

class Grand {
public:
	int m_grand;
};

class A1 : virtual public  Grand{//注意这里用了virtual
public:
	int m_a1;
};
class A2 : virtual  public  Grand{//注意这里用了virtual
public:
	int m_a2;
};
class C1 :public A1, public A2 {//这里不需要virtual
public:
	int m_c1;
};

int main()
{
	{
		cout << sizeof(Grand) << endl;
		cout << sizeof(A1) << endl;
		cout << sizeof(A2) << endl;
		cout << sizeof(C1) << endl;
		C1 c1obj;
		c1obj.m_grand = 2;
		c1obj.m_a1 = 5;
		c1obj.m_a2 = 6;
		c1obj.m_c1 = 8;

		A2& pa2 = c1obj;
		pa2.m_grand = 8;
		pa2.m_a2 = 9;

		/*A2* pa2 = &c1obj;
		pa2->m_grand = 8;
		pa2->m_a2 = 9;
		*/

		cout << "设置断点" << endl;
	}


	A1 a1obj;
	a1obj.m_grand = 2;
	cout << "设置断点" << endl;

	C1 c2obj;
	cout << "设置断点" << endl;




	return 0;
}