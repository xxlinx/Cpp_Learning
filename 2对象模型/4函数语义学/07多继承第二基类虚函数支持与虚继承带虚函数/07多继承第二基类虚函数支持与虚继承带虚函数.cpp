#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

/*
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }

	virtual ~Base() {
		cout << "Base::~Base()" << endl;
	}

public:
	virtual Base* clone() const {
		return new Base();
	}

};

class Base2 {
public:
	virtual void hBase2() { cout << "Base2::hBase2()" << endl; }

	//~Base2()
	//{
	//	cout << "Base2::Base2()" << endl;
	//}

	virtual ~Base2() {
		cout << "Base2::~Base2()" << endl;
	}

public:
	virtual Base2* clone() const {
		return new Base2();
	}

};

class Derive : public Base, public Base2 {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Derive::g()" << endl; }
	void myselffunc() {} //只属于Derive的函数

	virtual ~Derive() {
		cout << "Derive::~Derive()" << endl;
	}

public:
	virtual Derive* clone() const {
		return new Derive();
	}
};
*/

class Base {
public:
	virtual void f() {};
	virtual ~Base() {};

	int m_basei;
};
class Derive :public virtual Base {
public:
	virtual ~Derive() {}
	int m_derivei;
};
int main() {
	/*
	Base2* pb1 = new Derive();
	Base2* pb2 = pb1->clone();   //执行的是 Derive::clone()
	*/
	
	//虚继承下的虚函数
	//x86
	cout << sizeof(Derive) << endl;  //16
	//一个虚基类表指针 一个虚函数表指针， 两个int类型的成员变量
	Derive dobj;
	dobj.m_basei = 2;   //13-16字节
	dobj.m_derivei = 5; //5-8字节
	Derive* pdobj = new Derive();
	pdobj->f();

	return 0;
}