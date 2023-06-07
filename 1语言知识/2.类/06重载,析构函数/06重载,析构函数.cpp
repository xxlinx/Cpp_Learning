#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;

//重载 == 比较两个对象是非相等
void test01() {
	Time myTime;
	Time myTime2;
	if (myTime == myTime2)
	{
		//......
		cout << "相等" << endl;
	}
}

//
void test02() {
	Time myTime;             //这个会调用默认构造函数（不带参数）
	Time myTime2 = myTime;   //调用了拷贝构造函数	
	Time myTime5 = { myTime }; //调用了拷贝构造函数

	Time myTime6;        //这个会调用默认构造函数（不带参数）；
	myTime6 = myTime5;  //这是个赋值运算符,并不调用拷贝构造函数

}

//析构函数
void test03() {

}

int main() {

	test01();
	test02();
	return 0;
}