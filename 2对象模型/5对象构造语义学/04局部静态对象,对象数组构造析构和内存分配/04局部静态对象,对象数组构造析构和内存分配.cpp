#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class A {
public:
	//A(){
	//	cout << "A::A()缺省构造函数执行了" << endl;
	//}
	//~A(){
	//	cout << "A::~A()析构函数执行了" << endl;
	//}
	int m_i;
};

//void myfunc(){
//	static A s_aobj1;
//	static A s_aobj2;
//	printf("s_aobj1的地址是%p\n", &s_aobj1);
//	printf("s_aobj2的地址是%p\n", &s_aobj2);
//}
//const A& myfunc(){
//	static A s_aobj1;	
//	printf("s_aobj1的地址是%p\n", &s_aobj1);	
//	return s_aobj1;
//}

void myfunc() {
	//static A s_aobj[5];
	static A s_aobj[1000'0000]; //中间有'的数字是C++14新标准中支持的, '是数字分隔符
	for (int i = 0; i < 1000'0000; i++)
	{
		s_aobj[i].m_i = i; //这对于数组来说，一定算一件有用的事
	}
	printf("s_aobj数组的首地址是%p\n", s_aobj);
}


int main() {

	//myfunc();//调用一次
	//myfunc(); //又调用一次


	myfunc();
	printf("开始进入while循环\n");
	while (1){

	}
	return 0;
}