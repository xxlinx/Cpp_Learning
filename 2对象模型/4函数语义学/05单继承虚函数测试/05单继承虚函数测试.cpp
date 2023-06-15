#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class Base{
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};
//class Derive : public Base {
//public:
//	virtual void i() { cout << "Derive::i()" << endl; }
//	virtual void g() { cout << "Derive::g()" << endl; }
//	void myselffunc() {} //只属于Derive的函数
//};
class Derive : public Base {
public:
};
class BCXu {
public:
	virtual void pvfunc() = 0;
};

int main() {
	/*
	Derive myderive;
	Derive* pmyderive = &myderive;
	//注意下列虚函数的调用顺序
	pmyderive->f();
	pmyderive->g();
	pmyderive->h();
	pmyderive->i();
	*/

	/*
	Base* pb = new Derive();  //基类指针指向一个子类对象
	pb->g();  //Derive::g()

	Derive myderive;
	Base& yb = myderive;      //基类引用引用的是 一个子类对象
	yb.g();   //Derive::g()
	*/

	Derive a1;
	Derive a2;
	Derive* pa3 = new Derive();
	//这三个的虚函数表指针 指向的是同一个位置（同一个虚函数表）


	Base b1;
	//若子类不重写任何虚函数，子类仍然有自己的虚函数表，和父类Base的虚函数表不是一个表
	//尽管他们的表项相同

	cout << sizeof(BCXu) << endl;
	//即便是纯虚函数也是在虚函数表中占据一个表项
	cout << "断点设置在这里" << endl;

	return 0;
}