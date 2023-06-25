#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class A {
public:
	A() {
		printf("A::A()执行了，this = %p\n", this);
	};
	virtual ~A() {}

public:
	virtual void myvirfunc() {
		myvirfunc2();
		printf("A::myvirfunc()执行了!\n");
	};
	virtual void myvirfunc2() {
		printf("A::myvirfunc2()执行了!\n");
	};
};
class B : public  A
{
public:
	B() {
		myvirfunc();
		printf("B::B()执行了，this = %p\n", this);
	};
	virtual ~B() {}
public:
	virtual void myvirfunc(){
		myvirfunc2();
		printf("B::myvirfunc()执行了!\n");
	};
	virtual void myvirfunc2(){
		printf("B::myvirfunc2()执行了!\n");
	};

};
class C :public B{
public:
	C() :m_c(11){
		myvirfunc(); //调用一个虚函数
		printf("C::C()执行了，this = %p\n", this);
	};
	virtual ~C(){
		myvirfunc();
	}
public:
	int m_c;

public:
	virtual void myvirfunc(){
		myvirfunc2();
		printf("C::myvirfunc()执行了!\n");
	};
	virtual void myvirfunc2(){
		printf("C::myvirfunc2()执行了!\n");
	};

};


int main(){
	/*{
		C c;
	}*/

	//虚函数   在构造函数中调用虚函数	
	C* mycobj = new C();
	mycobj->myvirfunc();
	//这里显然是多态，因为是通过虚函数表查询虚函数并执行

	//在构造函数里调用虚函数，调用的是C类的 虚函数
	delete mycobj;


	return 0;
}