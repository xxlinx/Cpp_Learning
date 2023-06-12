#include <iostream>
#include <time.h>

using namespace std;

/*****************x86平台************************/
 
 
 
//父类1
class Base1
{
public:
	virtual void f() {
		cout << "base1::f()" << endl;
	}

	virtual void g() {
		cout << "base1::g()" << endl;
	}
};

//父类2
class Base2
{
public:
	virtual void h() {
		cout << "base2::h()" << endl;
	}
	virtual void i() {
		cout << "base2::i()" << endl;
	}
};

//子类
class Derived : public Base1, public Base2
{
public:
	virtual void f() {
		cout << "derived::f()" << endl;  //只覆盖base1的f
	}

	virtual void i() {
		cout << "derived::i()" << endl;  //只覆盖base2的i
	}

	//如下三个是本类自己的虚函数
	virtual void mh() {
		cout << "derived::mh()" << endl;
	}
	virtual void mi() {
		cout << "derived::mi()" << endl;
	}
	virtual void mj() {
		cout << "derived::mj()" << endl;
	}
};


int main() {

	cout << sizeof(Base1) << endl;    //4
	cout << sizeof(Base2) << endl;    //4
	cout << sizeof(Derived) << endl;  //8字节，这说明Derived里有两个虚函数表指针（2个vptr）

	Derived ins;    //定义一个子类对象
	Base1& b1 = ins;
	Base2& b2 = ins;
	Derived& d = ins;

	typedef void(*Func)(void);

	long* pderived1 = (long*)(&ins);
	long* vptr1 = (long*)(*pderived1); //第一个虚函数表指针，根据public中的继承顺序，应该是和base1对应

	long* pderived2 = pderived1 + 1;   //往后走4个字节
	long* vptr2 = (long*)(*pderived2); //第二个虚函数表指针

	//这些条目有规律，先从第一个继承的父类里找函数，如果自己覆盖的，就弄成自己的，如果自己没覆盖的，就弄成父亲的
	//然后接着是自己的虚函数首地址
	Func f1 = (Func)vptr1[0];   //0x00f31550 {project100.exe!Derived::f(void)} 
	Func f2 = (Func)vptr1[1];   //0x00f31596 {project100.exe!Base1::g(void)}
	Func f3 = (Func)vptr1[2];   //0x00f31578 {project100.exe!Derived::mh(void)}
	Func f4 = (Func)vptr1[3];   //0x00f31582 {project100.exe!Derived::mi(void)}
	Func f5 = (Func)vptr1[4];   //0x00f3157d {project100.exe!Derived::mj(void)}
	Func f6 = (Func)vptr1[5];   //0x0029aa64 {project100.exe!const Derived::`RTTI Complete Object Locator'{for `Base2'}}
	Func f7 = (Func)vptr1[6];   //后面先不管
	Func f8 = (Func)vptr1[7];   //后面先不管

	//这里找继承的另外一个父类，如果自己覆盖的，就弄成自己的，如果自己没覆盖的，就弄成父亲的
	Func f11 = (Func)vptr2[0];  //0x00291587 {project100.exe!Base2::h(void)}
	Func f22 = (Func)vptr2[1];  //0x00291591 {project100.exe!Derived::i(void)}
	Func f33 = (Func)vptr2[2];  //非法
	Func f44 = (Func)vptr2[3];  //非法

	b1.f();  //derived::f()，父类引用，但引用的是子类，所以这里执行子类所覆盖的父类的虚函数
	b2.i();  //dervied::i()，父类引用，但引用的是子类，所以这里执行子类所覆盖的父类的虚函数
	d.f();   //derived::f()
	d.i();   //derived::i()   
	d.mh();  //derived::mh()

	cout << "-------------------" << endl;
	f1();    //derived::f()
	f2();    //base1::g()
	f3();    //derived::mh()
	f4();    //derived::mi()
	f5();    //derived::mj()
	//f6();    //异常，报错
	cout << "-------------------" << endl;
	f11();   //base2::h()
	f22();   //derived::i()
	cout << "-------------------" << endl;


	return 0;
}