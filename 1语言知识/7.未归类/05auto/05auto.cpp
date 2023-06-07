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
template<typename T>
void tf(const T& tmprv) //这里把auto替换成T,上边auto里面的xy就相当于这里边的tmprv
{
	cout << "---------------------begin------------------------" << endl;;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;;	return;
}

void myfunc3(double, int) {
	cout << "myfunc3被调用" << endl;
}
//可以作为函数的返回类型
auto funca() {
	return 12;
}

class CT
{
public:
	//auto m_i = 12; //普通成员变量不能是auto类型
	static const auto m_si = 15; //这种static const(静态成员) 可以使用auto,使用auto后，其值必须在类内初始化，普通静态成员变量实际是要在.cpp中定义和初始化，这块只是声明，而这里的static const不一样，这里就相当于定义
};

class A
{
public:
	static int testr()
	{
		return 0;
	}
};
class B
{
public:
	static double testr()
	{
		return 10.5f;
	}
};

template <typename T>
auto ftestclass()
{
	auto value = T::testr();
	return value;
}


int main() {

	//1.传值方式
	/*
	auto x = 27;    //估计：x = int,auto = int
	const auto x2 = x;  //估计：x2 = const int,auto =int
	const auto& xy = x; //这个auto并不是传值方式，估计：xy = const int &,auto = int
	
	auto xy2 = xy; //估计：xy2 = int,auto = int。
	//这种应该是属于传值方式，传值方式时：引用类型会被抛弃,const属性会被抛弃，xy2是个新副本，这一点和函数模板类型推断非常类似
	*/

	//2。指针或者引用（不是万能引用）
	/*
	auto x = 27;
	const auto& xy = x;  //估计：xy = const int &,auto = int
	auto& xy3 = xy; //估计：xy3 = const int &,auto = const int，针对auto类型：引用会被丢弃，const属性会被保留
	//new一块内存，内存的初始值给100。
	auto y = new auto (100);//估计：y = int *,auto = int *。auto可以用于new操作符
	const auto* xp = &x; //估计：xp = const int *,auto = int
	auto* xp2 = &x; //估计：xp2 = int *,auto = int
	auto xp3 = &x; //估计：xp3 = int *，auto = int *; xp3不声明为指针，也能推导出指针类型
	*/

	//3.万能引用类型
	/*
	auto&& wnyy0 = 222;  //估计：这是万能引用，222是右值，所以：auto = int,wnyy2 = int&&（右值引用）
	auto&& wnyy1 = x;//估计：这是万能引用，x是左值，所以：auto=int&，wnyy1=int&
	
	auto x = 27;    //估计：x = int,auto = int
	const auto x2 = x;  //估计：x2 = const int,auto =int
	auto&& wnyy2 = x2;   //编译器推断：这是万能引用，x2是左值，则auto是int const & ，wnyy2也是int const &
	*/

	//对于数组和函数的推断
	/*
	const char mystr[] = "I love China!"; //mystr=const char [14]
	auto myarr = mystr;   //编译器推断：myarr = char const *
	auto& myarr2 = mystr; //编译器推断：char const (&)[14]

	int a[2] = { 1, 2 };
	auto aauto = a;   //编译器推断：int *

	auto tmpf = myfunc3;  //编译器推断：tmpf=void (__cdecl*)(double,int);   函数指针
	auto& tmpf2 = myfunc3; //编译器推断：tmpf2 = void (__cdecl&)(double,int); 函数引用
	tmpf(1, 2); //函数调用
	tmpf2(3, 4); //函数调用
	*/

	//std::initializer_list的特殊推断
	/*
	auto x = 10;      //编译器推断：int型，值10
	auto x2(20);      //编译器推断：int型，值20
	auto x3 = { 30 }; //编译器推断：std::initializer_list<int>型
	auto x4{ 40 };    //编译器推断：int型，值40
	//因为是 ={ } 的原因导致
	auto x5 = { 30,21 }; //顺利编译
	//auto x6 = { 30,21,45.3 }; //无法编译；因为有的成员是整型，有的成员是实型，类型不统一，编译报错。因为std::initializer_list<T>也有类型模板参数的，给不同类型会导致推导不出T的类型

	//这种  = { } 的推导只能用于auto 函数模板不能这样用
	*/

	cout << ftestclass<A>() << endl;
	cout << ftestclass<B>() << endl;


	return 0;
}