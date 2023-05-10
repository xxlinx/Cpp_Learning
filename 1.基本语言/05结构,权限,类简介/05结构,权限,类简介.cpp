#include <iostream>

using namespace std;

//结构体

struct student     //定义一个结构体类型student（学生）
{
	int number;
	char name[100];

	void func() {
		number++;
	}
};
//void func(student tmpstu) //形参为结构变量  这里肯定做了参数值拷贝，效率低。
void func(student& tmpstu)
{
	tmpstu.number = 2000;
	strcpy_s(tmpstu.name, sizeof(tmpstu.name), "who");
	return;
}
void func1(student* ptmpstu)
{
	ptmpstu->number = 4000;
	strcpy_s(ptmpstu->name, sizeof(ptmpstu->name), "xlin");
	return;
}
void test01() {
	student student1; //这里可以省略struct，直接用student
	student1.number = 1001;
	strcpy_s(student1.name, sizeof(student1.name), "zhangsan");
	cout << student1.number << endl; //1001
	cout << student1.name << endl;   //zhangsan
	cout << "-----------------------" << endl;
	func(student1);
	cout << student1.number << endl; //2000
	cout << student1.name << endl;   //who
	cout << "-----------------------" << endl;
	func1(&student1);
	cout << student1.number << endl; //4000
	cout << student1.name << endl;   //xlin
	cout << "-----------------------" << endl;
	student1.func();
	cout << student1.number << endl; //4001
}

//class 类简介
class Student {
public:
	int number;      //成员变量
	char name[100];  //成员变量
	void func()      //成员函数
	{
		number++;
		return;
	}
};




int main()
{
	test01();

    return 0;
}

