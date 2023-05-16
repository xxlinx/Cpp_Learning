#include <iostream>
#include <vector>
#include "ca.h"
using namespace std;

//显式实例化手段的 实例化声明
extern template A<float>; //其他所有.cpp文件都这样写
extern template void myfunc(int& v1, int& v2);

/*
class A //普通类
{
public:

	//成员函数模板
	template <typename T>
	void myft(T tmpt)
	{
		cout << tmpt << endl;
	}
};
//普通类的成员函数模板
void test01() {
	A a;
	a.myft(3);   //3
	a.myft("linx");  //linx
}
*/


void test02() {
	A<float> a(1, 2);   //实例化了一个A<float>这样一个类，并用int型来实例化构造函数
	A<float> a2(1.1, 2.2); //A<float>已经被上面代码行实例化过了，这里用float来实例化构造函数
}


//模板显式实例化与声明

int main() {

	//test01();
	test02();
	return 0;
}