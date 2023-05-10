#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;

void test01() {
	Time myTime = Time(12, 13, 52);
	Time myTime2(12, 13, 52);
	Time myTime3 = Time{ 12, 13, 52 };
	Time myTime4{ 12, 13, 52 };
	//	Time myTime5 = { 12, 13, 52 };


	//这些是拷贝构造
	//没有调用构造函数，调用的是拷贝构造函数
	Time myTime2_l = myTime;
	Time myTime3_l(myTime);
	Time myTime4_l{ myTime };
	Time myTime5_l = { myTime };

	Time myTime10 = Time(); //执行此行时调用无参的构造函数
	Time myTime12;//执行此行时调用无参的构造函数
	Time myTime13 = Time{};//执行此行时调用无参的构造函数
	Time myTime14{};//执行此行时调用无参的构造函数
	//	Time myTime15 = {};//执行此行时调用无参的构造函数

}


//隐式转换 和 explicit(要求构造函数不可做隐式转换)
void test02() {
	//在使用了explicit（显示）
	//Time myTime23 = 14;  //现在语法错
	//Time myTime24 = (12, 13, 14, 15, 16); //现在语法错，不管()中有几个数字

	//Time myTime100 = { 16 }; //这种写法认为正常，带一个参数12，可以让系统明确调用带一个参数的构造函数
	//Time myTime101 = 16;     //这代码比较含糊不清，这就存在临时对象或者隐式转换的问题了

}

//初始化列表

void test03() {


}

int main() {

	test01();
	test02();
	//test03();
	return 0;
}