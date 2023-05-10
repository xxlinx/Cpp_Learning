#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;   //后面再使用诸如std::cout时就可以简写成cout了；

int Time::mystatic = 5; //可以不给初值，那么系统默认会给0，定义时这里不需要用static了

void func(Time tmptime)
{
	return;
}
Time func()
{
	Time linshitime;  //本身是一个临时对象
	return linshitime;  //产生另外一个临时对象用来返回过去
}

void test01() {

	Time myTime;  //这个会调用默认构造函数（不带参的）
	Time myTime2 = myTime; //调用了拷贝构造函数
	Time myTime3(myTime); //调用了拷贝构造函数
	Time myTime4{ myTime };//调用了拷贝构造函数
	Time myTime5 = { myTime };//调用了拷贝构造函数
	Time myTime6; //这个会调用默认构造函数（不带参的）
	myTime6 = myTime5;  //没有调用拷贝构造函数

}

void test02() {
	Time myTime;
	func(myTime);
		//调用了Tmpclass::Tmpclass()构造函数
		//调用了Tmpclass::Tmpclass(const Tmpclass & tmpclass)拷贝构造函数
		//调用了Time::Time(const Time & tmptime)拷贝构造函数
}

void test03() {
	Time mytime = func();
	//调用了Tmpclass::Tmpclass()构造函数
}

int main() {

	//test01();
	//test02();
	test03();
	return 0;
}