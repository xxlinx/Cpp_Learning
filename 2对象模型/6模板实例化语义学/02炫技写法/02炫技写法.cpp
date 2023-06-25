#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

//
//class A
//{
//private:
//	A() {}
//	friend class B; //B可以调用A的私有构造函数
//};
////class B : public  A
//class B : virtual public A //虚继承A
//{
//public:
//	int m_b;
//};
//class C :public B
//{
//public:
//	int m_c;
//};

class A {
private:
	virtual void virfunc(){
		myfunc();
	}
	void myfunc(){
		cout << "A::myfunc()运行了" << endl;
	}
};


int main() {

	/*
	B myobjb;
	myobjb.m_b = 15;

	C myobjc;
	myobjc.m_c = 20;
	*/


	A aobj;
	(reinterpret_cast<void(*)()>(**(int**)(&aobj)))();//调用私有的虚函数
	//是通过虚函数表来调用虚函数

	return 0;
}