#include <iostream>
#include <time.h>

using namespace std;

class Base {
public:
	int ba;
	int bb;
	Base(int tmpa, int tmpb) {//构造函数
	}
};

class CSub {
public:
	CSub(int tmpvalue){

	}
};

class A :public Base
{
public:
	int m_x;
	int m_y;
	int& m_yy;
	const int m_myc;
	CSub cmysub;
	//A() :m_x(0), m_y(0)
	//{
	//}
	//A(int &tmpvalue):m_yy(tmpvalue), m_myc(tmpvalue)

	A(int& tmpvalue) :m_yy(tmpvalue), m_myc(tmpvalue), Base(tmpvalue, tmpvalue), cmysub(tmpvalue)
	{
		//m_yy = tmpvalue; //错误，不可以，必须在初始化列表中进行绑定
		m_x = 0;
		m_y = 0;
		m_yy = 160;	//就等于修改外界的abc变量值
	}

};

class X
{
public:
	int m_i;
	X(int value = 0) :m_i(value) //类型转换构造函数
	{
		printf("this = %p", this);
		cout << "X类的X(int)构造函数被调用" << endl;
	}
	X(const X& tmpv)
	{
		printf("this = %p", this);
		cout << "X类的拷贝构造函数被调用" << endl;
	}
	X& operator=(const X& tmpTime)
	{
		printf("this = %p", this);
		cout << "X类的拷贝赋值运算符被调用" << endl;
		return *this; //返回一个该对象的引用
	}
	~X()
	{
		printf("this = %p", this);
		cout << "X类的析构函数被调用" << endl;
	}
};

class XA
{
public:
	X  xobj;
	int m_test;
	int m_test2;  //定义在后面，则后得到值
	//XA(int tmpvalue)
	//XA(int tmpvalue) : xobj(1000)
	XA(int tmpvalue) :xobj(1000), m_test2(500), m_test(m_test2)
	{
		//xobj = 1000;
		m_test = 500;
	}
};

int main()
{

	XA myaobj(1000);

	return 0;
}