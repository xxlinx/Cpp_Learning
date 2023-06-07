#include <iostream>
#include <list>
#include <stdarg.h>
#include <initializer_list>
#include <vector>
using namespace std;

//void printvalue(initializer_list<string> tmpstr)
//{
//	//遍历每个元素：begin指向数组首元素的指针。end指向数组尾元素之后
//	for (auto beg = tmpstr.begin(); beg != tmpstr.end(); ++beg)
//	{
//		cout << (*beg).c_str() << endl;
//	}
//	cout << tmpstr.size() << endl; //有size方法可以打印列表中元素数量
//}
void printvalue(initializer_list<string> tmpstr)
{
	for (auto& tmpitem : tmpstr) //用 引用，节省性能
	{
		cout << tmpitem.c_str() << endl;
	}
	cout << tmpstr.size() << endl;
}
//含有initializer_list  可以包含其他形参
void printvalue2(initializer_list<string> tmpstr, int tmpvalue) {}

class CT
{
public:
	explicit  CT(const std::initializer_list<int>& tmpvalue) {//单参数构造函数
	}
};


int main() {
	// 1. initializer_list 初始化列表
	/*
	printvalue({ "aa", "bb", "cc" });
	printvalue2({ "aa", "bb", "cc" }, 6);
	*/
	//2.初始化列表作为构造函数参数
	/*
	//没有explicit
	CT ct1  { 10,20,30,40 }; //隐式类型转换
	//有explicit
	CT ct2 = CT({ 10,20,30,40 });
	*/
	
	//3。统一初始化
	int myarray[] = { 1,5,6,9 };   //定义并初始化
	int myarray2[]{ 12,25,37,89 }; //定义并初始化
	vector<int> myvec = { 15,45,78,76 }; //定义并初始化


	return 0;
}