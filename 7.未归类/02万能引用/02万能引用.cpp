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

//void myfunc(int&& tmprv) //参数tmprv是个右值引用类型
//{
//	cout << tmprv << endl;
//	return;
//}

template <typename T>
void myfunc(T&& tmprv) //万能引用，注意 &&是属于tmprv类型的一部分，不是T类型的一部分（&&和T类型没有关系）
{
	tmprv = 12;  //不管tmprv的类型是左值引用还是右值引用，都可以给tmprv赋值
	cout << tmprv << endl;
	return;
}


//有const修饰，因此万能引用资格被剥夺，因为是&&所以只能是个右值引用
//template <typename T>
//void myfunc(const T&& tmprv) 
//{
//	cout << tmprv << endl;
//	return;
//}

template <typename T>
class mytestc
{
public:
	void testfunc(T&& x) {}; //这个不是万能引用，这个是右值引用

	template <typename T2>
	void testfunc2(T2&& x) {} //T2类型是独立的，和T没任何关系，而且x是函数模板形参，类型是推导来的，所以这是个万能 引用

};


int main() {

	myfunc(10);
	int i = 100;
	myfunc(i);  

	mytestc<int> myoc;
	int i2 = 10;
	myoc.testfunc2(i2); //左值可以，给个数字3表示右值也可以
	return 0;
}