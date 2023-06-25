#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;


class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }

	virtual ~Base()
	{
		cout << "Base::~Base()" << endl;
	}
};

class Base2 {
public:
	virtual void hBase2() { cout << "Base2::hBase2()" << endl; }

	/*~Base2()
	{
		cout << "Base2::Base2()" << endl;
	}*/

	virtual ~Base2() {
		cout << "Base2::~Base2()" << endl;
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
};

class ParentClass {//一个父类
public:
	//virtual void f() {};
	ParentClass() //构造函数
	{
		cout << "ParentClass::ParentClass()" << endl;
	}
	virtual ~ParentClass()
	{
		cout << "ParentClass::~ParentClass()" << endl;
	}
};
class SonClass : public ParentClass //一个子类
{
public:
	char* m_p = NULL;
	SonClass()//构造函数
	{
		cout << "SonClass::SonClass()" << endl;
		m_p = new char[100];//这里分配了内存
	}
	~SonClass()
	{
		cout << "SonClass::~SonClass()" << endl;
		delete m_p;//这里要释放内存，否则会导致内存泄漏
	}
};

int main(){

	/*{
		Base2* pb2 = new Derive();
		delete pb2;
	}*/
	/*{
		Derive* temp = new Derive();
		Base2* pb2 = (Base2*)((char*)(temp)+sizeof(Base));
	}
*/
//{
//	Base* pbm = new Base();
//	Base2* pb222 = new Base2();

//	Derive* p11212 = new Derive();
//	p11212->g(); //Derive::g()
//	p11212->i(); //Derive::i()，走虚函数表，查询虚函数表得到虚函数地址并调用虚函数 

//	Derive dddd;
//	dddd.i();   //Derive::i()，不走虚函数表，直接调用虚函数


//	cout << "断点设置在这里" << endl;
//}

	{
		//SonClass sonobj;
		ParentClass* parobj = new SonClass; //创建SonClass对象
		delete parobj;  //删除SonClass对象
	}

	return 0;
}