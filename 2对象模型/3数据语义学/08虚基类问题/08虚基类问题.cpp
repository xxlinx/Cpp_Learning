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
class A1 : virtual public  Grand {//注意这里用了virtual
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

int main() {

	cout << sizeof(Grand) << endl;
	cout << sizeof(A1) << endl;
	cout << sizeof(A2) << endl;
	cout << sizeof(C1) << endl;

	A1 a1;
	A2 a2;
	cout << "设置断点" << endl;

	return 0;
}