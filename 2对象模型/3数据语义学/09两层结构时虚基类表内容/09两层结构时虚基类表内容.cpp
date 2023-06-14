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

class Grand {//爷爷类
public:
	int m_grand;
};

class Grand2{
public:
	int m_grand2;
};

//class A1 : virtual public  Grand //注意这里用了virtual
//class A1 : virtual public  Grand, public Grand2
//class A1 : public  Grand, virtual public Grand2
class A1 : virtual public  Grand, virtual public Grand2
{
public:
	int m_a1;
};
class A2 : virtual  public  Grand//注意这里用了virtual
{
public:
	int m_a2;
};
class C1 :public A1, public A2 //这里不需要virtual
{
public:
	int m_c1;
};

int main()
{

	/*
	cout << sizeof(Grand) << endl;
	cout << sizeof(A1) << endl;
	cout << sizeof(A2) << endl;
	cout << sizeof(C1) << endl;
	}*

	//
	//	C1 c1;
	//	//c1.m_grand = 12; //这句编译时会报错  语义不确定
	//	c1.A1::m_grand = 5;
	//	c1.A2::m_grand = 8;


	//
	//C1 c1;
	//c1.m_grand = 12; //这句编译时不会再报错
	//

	/*
	cout << sizeof(Grand) << endl;
	cout << sizeof(A1) << endl;
	cout << sizeof(A2) << endl;
	cout << sizeof(C1) << endl;

	A1 a1;
	A2 a2;
	cout << "设置断点" << endl;
	*/

	/*
	A1 a1obj;
	a1obj.m_grand = 2;
	a1obj.m_a1 = 5;
	cout << "设置断点" << endl;
	*/

	
	A1 a1obj;            //a1obj的地址是0x00EFFD48，该地址的第5~8字节内容为0x00179b30，因此虚基类表地址是0x00179b30
	A1 a2obj;
	a1obj.m_grand = 2;
	a1obj.m_grand2 = 6;
	a1obj.m_a1 = 5;
	cout << "设置断点" << endl;
	
	return 0;
}