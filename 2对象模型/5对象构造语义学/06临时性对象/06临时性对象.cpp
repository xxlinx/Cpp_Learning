#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class A {
public:
	A(){
		cout << "A::A()构造函数执行" << endl;
	}
	A(const A& tmpobj){
		m_i = tmpobj.m_i;
		cout << "A::A()拷贝构造函数执行" << endl;
	}
	~A(){
		cout << "A::~A()析构函数执行" << endl;
	}

public:
	A& operator=(const A& tmpaobj)
	{
		cout << "A::operaotor=()拷贝赋值运算符执行" << endl;
		printf("tmpaobj的地址为%p\n", &tmpaobj);
		return *this; //返回一个该对象的引用
	}
public:
	int m_i;
};
A operator+(const A& obj1, const A& obj2){
	A tmpobj; //调用一次构造函数
	//	printf("tmpobj的地址为%p\n", &tmpobj);

		//这里可以做一些加法计算
		//......
	//	printf("---------\n");
	tmpobj.m_i = obj1.m_i + obj2.m_i;
	return  tmpobj; //执行后调用了一次拷贝构造函数，一次析构函数,说明有临时对象生成
}


int main() {

	/****** 拷贝构造函数相关的临时性对象 *****/
	/*
	A myobj1; //调用一次构造函数			
	A myobj2; //调用一次构造函数 					
	A resultobj = myobj1 + myobj2;
	*/

	/****** 拷贝赋值运算符相关的临时性对象 *****/
	/*
	A myobj1; //调用一次构造函数			
	A myobj2; //调用一次构造函数 					
	A resultobj;
	resultobj = myobj1 + myobj2;
	*/
	/*
	A myobj1; //调用一次构造函数
	printf("myobj1的地址为%p\n", &myobj1);
	A myobj2; //调用一次构造函数 
	printf("myobj2的地址为%p\n", &myobj2);

	//A resultobj = myobj1 + myobj2;
	A resultobj;
	resultobj = myobj1 + myobj2;
	printf("resultobj的地址为%p\n", &resultobj);
	*/

	/****** 直接运算产生的临时性对象 *****/
	/**/
	A myobj1; //调用一次构造函数			
	A myobj2; //调用一次构造函数 					
	myobj1 + myobj2;
	
	//if ((myobj1 + myobj1).m_i > 3 || (myobj1 + myobj2).m_i > 5)
	if ((myobj1 + myobj1).m_i > 1 || (myobj1 + myobj2).m_i > 5){
		cout << "条件成立" << endl;
	}



	return 0;
}