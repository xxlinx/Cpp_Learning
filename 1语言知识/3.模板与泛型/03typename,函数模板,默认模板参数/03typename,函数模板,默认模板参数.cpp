#include <iostream>
#include <vector>
#include "myvector.h"
#include "myarray.h"

using namespace std;

template <typename T>
typename T::size_type getlength(const T& c) {
	if (c.empty()) //这些诸如empty,size等成员函数，
					//在函数模板未被实例化之前，谁也不知道这些成员函数到底写的对还是不对，
					//但一旦被实例化，自然可知
		return 0;

	return c.size();
}
//1 typename 用法
void test01() {
	string mytest = "I Love China!";
	//size_type类似unsigned int类型。定义于string类中，一般和string配套使用，考虑到各种机器中数据类型的差异，所以引入这个类型，保证程序与实际的机器匹配的目的
	//string::size_type size = mytest.size();   这样就直接能求出来
	string::size_type size2 = getlength(mytest);
	cout << size2 << endl;  //13
}

//2函数指针作为其他函数的参数
int mf(int tmp1, int tmp2) {

	return 1;
}
typedef int(*FunType)(int, int);  //定义一个函数指针类型，以及函数本身的参数
void testfunc(int i, int j, FunType funcpoint) {//最后一个参数为函数指针
	//可以通过函数指针调用函数
	int result = funcpoint(i, j);//这个就是通过函数指针调用函数
	cout << result << endl;
}

void test02() {
	testfunc(3, 4, mf); //1   调用
}

//3函数模板趣味用法举例
template <typename T, typename F>
void testfunc1(const T& i, const T& j, F funcpoint) {
	cout << funcpoint(i, j) << endl;
}
void test03() {
	testfunc1(3, 4, mf);  //1    函数名是参数，那传递的就是函数地址
}
//可调用对象 callable object   必须要重载（）
class tc {
public:
	tc() { cout << "构造函数执行" << endl; }
	tc(const  tc& t) { cout << "拷贝构造函数执行" << endl; }
	//重载圆括号
	int operator()(int v1, int v2) const
	{
		return v1 + v2;
	}
};
void test04() {
	tc tcobj;   //构造函数执行
	testfunc1(3, 4, tcobj);//拷贝构造函数执行
		//原因是 生成 funcpoint 对象的时候  发生了拷贝构造
		//7
}
void test05() {
	testfunc1(3, 4, tc());    
	//少一次拷贝构造，相应少一次析构函数
}

//4默认模板参数
template <typename T, typename F = tc>
void testfunc2(const T& i, const T& j, F funcpoint = F()) {
	cout << funcpoint(i, j) << endl;
}
void test06() {
	testfunc2(3, 4);
}
int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	test06();
	return 0;
}