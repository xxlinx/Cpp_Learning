#include <iostream>
#include <time.h>
#include <cstdio>

#include "mytemplate.h"


using namespace std;

//template<class T>
//class ATPL {
//public:
//	enum ECURRSTATUS {
//		E_CS_Busy,
//		E_CS_Free,
//	};
//
//public:
//	T m_i, m_j;
//	ATPL(T tmpi = 0, T tmpj = 0) {//构造函数
//		m_i = tmpi;
//		m_j = tmpj;
//	}
//
//public:
//	static int m_sti;
//	static T m_sti2;
//
//public:
//	void func1() const { cout << "ATPL::func1()" << endl; }
//	void func2() const { cout << "ATPL::func2()" << endl; }
//
//};
//
//template <class T> 	int ATPL<T>::m_sti = 10;
//template <class T> 	T ATPL<T>::m_sti2 = 10;


void myfunc()
{
	ATPL<int> myobj;
	myobj.m_sti2 = 18;
	cout << myobj.m_sti2 << endl;
}

int main() {

	/******* 类模板的实例化分析 *****/
	/*
	ATPL<int>::m_sti = 18;
	cout << ATPL<int>::m_sti << endl;

	ATPL<float>::m_sti = 21;
	cout << ATPL<float>::m_sti << endl;

	ATPL<int>::m_sti2 = 132;
	ATPL<float>::m_sti2 = 1050;
	cout << ATPL<int>::m_sti2 << endl;
	cout << ATPL<float>::m_sti2 << endl;
	

	//ATPL<int>* pobj = NULL;
	//这个不会产生任何ATPL相关的内容,没有实例化出来任何类
	const ATPL<int>& yobj = 0; //因为构造函数允许缺省参数，这里有隐式类型转换
	//这个模板实例化出来了
	//但不会去实例化成员函数
	yobj.func1();
	//这个时候才实例化成员函数
	*/

	/******* 多个源文件中使用类模板 *****/


	return 0;
}