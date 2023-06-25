#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}
};

class Derive : public Base {
public:
	virtual void g() { cout << "Derive::g()" << endl; }
	void myselffunc() {} //只属于Derive的函数
	virtual ~Derive() {}
};

int main() {

	/****************简单回顾******************/
	/*
	Base* pb = new Derive();   //基类指针指向一个子类对象
	pb->g();   //Derive::g()
	Derive myderive;
	Base& yb = myderive;    //基类引用 引用的是一个子类对象
	yb.g();  //Derive::g()

	cout << typeid(*pb).name() << endl;   //class Derive
	cout << typeid(yb).name() << endl;    //class Derive

	Derive* pderive = dynamic_cast<Derive*>(pb);
	if (pderive != NULL)
	{
		cout << "pb指向的实际是一个Derive类型" << endl;
		pderive->myselffunc(); //调用属于子类自己的函数
	}
	//pb指向的实际是一个Derive类型
	*/

	/**************       RTTI实现原理   **********/
	/*
	const std::type_info& tp = typeid(*pb);
	Base* pb2 = new Derive();
	const std::type_info& tp2 = typeid(*pb2);
	if (tp == tp2) //条件成立
	{
		cout << "很好，类型相同" << endl; 
	}*/
	
	//这些是静态类型
	cout << typeid(int).name() << endl;              //int
	cout << typeid(Base).name() << endl;            //class Base
	cout << typeid(Derive).name() << endl;          //class Derive
	Derive* pa3 = new Derive();
	cout << typeid(pa3).name() << endl;            //class Derive *
	
	//看看多态类型
	Base* pb = new Derive();
	Derive myderive;
	Base& yb = myderive;
	cout << typeid(*pb).name() << endl;      //class Derive
	cout << typeid(yb).name() << endl;       //class Derive
	Base* pb2 = new Derive();
	const std::type_info& tp2 = typeid(*pb2);
	cout << tp2.name() << endl;              //class Derive

	/*********  vptr vtbl 与 RTTI的type_info信息创建时机  *******/
	//实际上type_info 信息是编译期间就创建好的
	//这个信息是基于类的 


	return 0;
}