#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;
//int myfunc(int testv)
//inline int myfunc(int testv)
//{
//	//return testv * (5 + 4) * testv;
//	int tempvalue = testv * (5 + 4) * testv;
//	return tempvalue;
//}

inline int myfunc(int testv){
	if (testv > 10){
		testv--;
		myfunc(testv);
	}
	return testv;
}

int rtnvalue(){
	return 5;
}
int main() {

	/******* inline 函数回顾  *****/
	/*
	int i = myfunc(12);
	cout << i << endl;
	*/

	/***** inline 扩展 *****/
	int i = myfunc(12 + 15);
	//编译器会先计算 12+15 再替换掉形参

	int a = 80;
	int i1 = myfunc(a + 15);
	//先计算a 和15 的和，然后再替换掉形参

	int i2 = myfunc(rtnvalue() + 15);
	//先调用rtnvalue 拿到返回值，用该返回值和15做和， 然后再替换掉形参



	return 0;
}
