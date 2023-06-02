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

using namespace std;

int max(int x, int y) {    //求最大值函数
	if (x > y)
		return x;
	return y;
}
//void func(int i) {
//	cout << "这是函数func()" << i << endl;
//	return;
//}

class biggerthanzero {
public:
public:
	//biggerthanzero(int i)
	//{
	//	cout << "biggerthanzero::biggerthanzero(int i)构造函数执行了" << endl;
	//}
	//重载函数调用运算符()
	int operator()(int value) const //如果值<0就返回0，否则返回实际的值
	{
		if (value < 0) 
			return 0;
		return value;
	}
};
int max(int x, int y) //求最大值函数
{
	if (x > y)
		return x;
	return y;
}
int echovalue(int value)
{
	cout << value << endl;
	return value;
}


int main() {
	/*
	int i = 200;
	biggerthanzero obj;
	int result = obj(i);//调用类中重载的函数调用运算符()，本行代码等价于：int result = obj.operator()(i);
	//int result = obj.operator()(i)
	
	//biggerthanzero obj(1); //这是对象定义并初始化，所以调用的是biggerthanzero构造函数
	//	obj(i); //这个才是调用类中重载的函数调用运算符()
	*/

	/*
	int(*p)(int x, int y);//定义一个函数指针
	p = max; //将函数max的入口地址赋给指针变量
	int c = (*p)(5, 19); // 调用
	*/

	//map<string, int(*)(int)> myoper;

	//myoper.insert({ "ev", echovalue });  //

	/*
	biggerthanzero obj;
	//myoper.insert({ "bt", obj });

	//标准库function函数
	function<int(int)> f1 = echovalue;
	function<int(int )> f2 = obj;
	function<int(int) > f3 = biggerthanzero();

	//调用
	f1(5);
	cout << f2(3) << endl;
	cout << f3(-5) << endl;
	*/

	biggerthanzero obj;
	map<string, function<int(int)> > myoper = {
			{ "ev",echovalue},
			{ "bt",obj },
			{ "bt2",biggerthanzero() }
	};
	myoper["ev"](12);  //"ev"是键，那myoper["ev"]就代表值，其实也就是这个echovalue函数，现在就调用这个函数了
	cout << myoper["bt"](3) << endl; //调用obj对象的函数调用运算符()
	cout << myoper["bt2"](-5) << endl; //调用biggerthanzero类对象的函数调用运算符()

	int(*fp)(int) = echovalue;  //定义个函数指针，不会产生二义性，因为函数指针里有对应的参数类型和返回类型
	function<int(int)> f123 = fp; //直接塞进去函数指针而不是函数名


	return 0;
}