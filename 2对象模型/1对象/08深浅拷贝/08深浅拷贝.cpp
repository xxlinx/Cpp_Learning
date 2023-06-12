#include <iostream>
#include <time.h>

using namespace std;

class X
{
public:
	int m_i;
	int* p_mi; //整型指针，其他类型指针都可以，道理相同

	X(const X& tmpx)
	{
		p_mi = new int(100); //为指针类型成员变量单独分配内存
		memcpy(p_mi, tmpx.p_mi, sizeof(int));
		m_i = tmpx.m_i;
		cout << "X类的拷贝构造函数被调用" << endl;
	}

	X()
	{
		m_i = 0;
		p_mi = new int(100);
		cout << "X类的构造函数被调用" << endl;
	}
	~X()
	{
		delete p_mi;
		cout << "X类的析构函数被调用" << endl;
	}
	//explicit X(int value) :m_i(value) //类型转换构造函数（带有一个形参的拷贝构造函数）
	X(int value) :m_i(value) //类型转换构造函数（带有一个形参的拷贝构造函数）
	{
		p_mi = new int(100);
		cout << "X类的X(int)构造函数被调用" << endl;
	}



};


int main() {

	X x0;
	x0.m_i = 150;
	X x1(x0);
	cout << x1.m_i << endl;

	return 0;
}