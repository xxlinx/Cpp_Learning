#include <iostream>
#include <vector>

#include "Time.h"
#include "Time2.h"

using namespace std;

//类相关非成员函数
void test01() {

	Time mytime(12, 15, 17);
	WriteTime(mytime);

}

//const成员变量的初始化  只能使用初始化列表来初始化，不能在构造函数里进行赋值操作

//没有参数的构造函数 成为 默认构造函数
void test02() {
	//Time2 mytime2(1); //生成对象会调用构造函数				
						   //因为构造函数带一个形参，这里必须提供一个实参
	Time2 mytime2;  //调用默认构造函数
	

}

int main() {
	test01();
	test02();

	return 0;
}