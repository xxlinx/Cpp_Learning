#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <forward_list>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <queue>
#include <boost/type_index.hpp>

using namespace std;

void testFunc() {}

//引用折叠
//函数模板
/*
template <typename T>
void myfunc(T&& tmprv)
{
	cout << "---------------------begin------------------------" << endl;;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}
*/
//转发： 
template <typename F, typename T1, typename T2>
//void myFuncTemp(F f, T1 t1, T2 t2)
void myFuncTemp(F f, T1&& t1, T2&& t2)   //改成万能引用
{
	//针对myFuncTemp(myfunc2, 20, j);调用：
	//T1 = int,t1 = int &&，但t1本身是左值
	//T2 = int &, t2 = int &

	//f(t1, t2);
	//完美转发
	f(std::forward<T1>(t1), std::forward<T2>(t2));
}

//void myfunc(int v1, int v2)
void myfunc(int v1, int& v2)
{
	++v2; //改变v2值，让其自增1
	cout << v1 + v2 << endl;
}

void myfunc2(int&& v1, int& v2)
{
	cout << v1 << endl;
	cout << v2 << endl;
}
void printInfo(int& t)
{
	cout << "PrintT()参数类型为左值引用" << endl;
}
void printInfo(int&& t)
{
	cout << "PrintT()参数类型为右值引用" << endl;
}

template <typename T>
void TestF(T&& t) //万能引用
{
	//可以显示一些编译器推断的类型信息辅助理解
	cout << "---------------------begin------------------------" << endl;;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "t=" << type_id_with_cvr<decltype(t)>().pretty_name() << endl; //显示t类型
	cout << "----------------------end-------------------------" << endl;


	printInfo(t);                  //左值 ，形参都是左值      
	printInfo(std::forward<T>(t)); //按照参数t原来的左值或右值性进行转发，原来左值就不变，原来右值就转成右值
	printInfo(std::move(t));       //左值转右值
}


int main() {

	//int j = 70;
	//myFuncTemp(myfunc, 20, j);

	/*
	int j = 10;
	myfunc2(20, j);
	*/

	TestF(1); //是右值，看实际执行结果：T=int，t=int &&
	int i = 1;
	TestF(i); //i是左值：看实际执行结果：T=int&，t=int &，发生引用折叠

	return 0;
}
