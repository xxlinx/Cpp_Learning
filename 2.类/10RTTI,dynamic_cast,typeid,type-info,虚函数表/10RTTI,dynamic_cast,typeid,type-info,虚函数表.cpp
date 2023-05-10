#include <iostream>
#include <vector>

#include "Men.h"
#include "Women.h"

using namespace std;

void test01() {
	Human* phuman = new Men;
	Men* p = (Men*)(phuman); //用C语言风格的强制类型转换，强制把指针转成Men *型
	p->testfunc(); //正常调用Men类的成员函数
}
//dynamic_cast 运算符
void test02() {

	Human* phuman = new Men;
	Men* pmen = dynamic_cast<Men*>(phuman);
	//指针转换是否失败的判断
	if (pmen != nullptr)
	{
		cout << "phuman实际指向一个Men类型对象" << endl;
		//在这里操作Men类里的成员函数，成员变量等都是安全的
	}
	else
	{
		//转换失败；
		cout << "phuman实际指向的不是一个Men类型对象" << endl;
	}
}

void test03() {
	Men mymen;
	Human& myhuman_y = mymen; //父类引用指向子类对象
	try
	{
		Men& ifment = dynamic_cast<Men&>(myhuman_y);
		//走到这里，表示转换成功
		cout << "myhuman_y实际是一个Men类型" << endl;
		//在这里操作Men类里的成员函数，成员变量等都是安全的
	}
	catch (bad_cast)
	{
		//转换失败
		cout << "myhuman_y不是一个Men类型" << endl;
	}
}

//typeid 运算符
void test04() {

	Human* phuman = new Men;
	Human& q = *phuman;
	cout << typeid(*phuman).name() << endl; //class Men
	cout << typeid(q).name() << endl;       //class Men

	char a[10] = { 5,1 };
	int b = 120;
	cout << typeid(a).name() << endl;     //char [10]
	cout << typeid(b).name() << endl;     //int
	cout << typeid(19.6).name() << endl;  //double
	cout << typeid("asd").name() << endl; //char const [4]
}
//判断两个指针是否指向同一类型
void test05() {
	Human* phuman = new Men;
	Human* phuman2 = new Women;
	if (typeid(phuman) == typeid(phuman2)) //这里是成立的  该例不符合要求
	{
		cout << "phuman和phuman2指针的定义类型相同" << endl;
	}
}
void test06() {

	Human* phuman = new Men;
	Men* phuman2 = new Men;
	Human* phuman3 = phuman2;
	if (typeid(*phuman) == typeid(*phuman2)) //成立，都指向Men  前面这里的 *  不可落下
	{
		cout << "phuman和phuman2指向同一种类型对象【看运行时实际new出来的或者指向的对象】" << endl;
	}
	if (typeid(*phuman2) == typeid(*phuman3))  //成立，都指向Men
	{
		cout << "phuman2和phuman3指向同一种类型对象【看运行时实际new出来的或者指向的对象】" << endl;
	}

	//另一种写法
	if (typeid(*phuman) == typeid(Men)) //成立
	{
		cout << "phuman指向Men【看运行时实际new出来的或者指向的对象】" << endl;
	}
}

//type_info类
void test07() {

	Human* phuman = new Men;
	const std::type_info& tp = typeid(*phuman);
	//.name:返回一个C风格字符串，表示类型名字的可显式形式。类型名的生成方式因系统而异甚至可能与在程序中使用的名字不一致。但不管怎么说，类型不同，返回的字符串肯定不同
	cout << tp.name() << endl; //父类有虚函数，结果就是class Men，没虚函数，结果就是class Human
	// 输出 class Men

	Human* phuman2 = new Men;
	const std::type_info& tp2 = typeid(*phuman2);
	if (tp == tp2)
	{
		cout << "类型相同" << endl; //成立 都是 Men
	}
	Human* phuman3 = new Women;
	const std::type_info& tp3 = typeid(*phuman3);
	if (tp == tp3)
	{
		cout << "tp == tp3 类型相同" << endl; //不成立，因为是Men和Women比较，但同样，如果基类中没有虚函数，则就成立
	}
}

int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	test07();
	return 0;
}