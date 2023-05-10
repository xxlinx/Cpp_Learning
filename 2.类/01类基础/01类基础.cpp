#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;

struct student
{
	int number;
	char name[100];
	void func() {};
};

void test01() {

	student student1;  //定义结构变量。这里可以省略struct，直接用结构名student
	student1.number = 1001;
	strcpy_s(student1.name, sizeof(student1.name), "zhangsan");
	student1.func(); //调用成员函数
	student* pstudent1 = &student1;
	pstudent1->number = 1005;
	cout << student1.number << endl; //1005
}


void test02() {
	Time myTime;
	myTime.initTime(11, 14, 5);  //这就是调用成员函数（使用成员函数）
	cout << myTime.Hour << endl;  //11
	cout << myTime.Minute << endl; //14
	cout << myTime.Second << endl; //5

	Time myTime2 = myTime;
	Time myTime3(myTime);
	Time myTime4{ myTime };
	Time myTime5 = { myTime };
	myTime5.Hour = 8;

	Time myTime6;
	myTime6 = myTime5;  //通过赋值操作来拷贝对象
}


int main() {
	test01();
    return 0;
}

