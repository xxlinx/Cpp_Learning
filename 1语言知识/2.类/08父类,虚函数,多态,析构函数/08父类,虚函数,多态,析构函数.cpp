#include <iostream>
#include <vector>

#include "Men.h"
#include "Women.h"
using namespace std;


//父类指针与 子类指针
void test01() {

	Human* phuman = new Human();    //完全没问题
	Men* pmen = new Men;            //完全没问题

	//父类指针可以 new 一个子类对象
	Human* phuman2 = new Men; //这个可以

	//Men* pmen2 = new Human;  //这个报错，子类指针指向父类对象不可以
	//无法从 Human* 转换成 Men* 

	phuman2->funchuman();//可以，父类类型，可以调用父类的成员函数

	//phuman2->funcmen();//不可以，虽然new子类对象，但是父类指针，无法调用子类成员函数

}

//虚函数
void test02() {

	Men* pmen = new Men;
	pmen->eat();  //调用了Men类的eat函数
		/*执行了Human::Human()构造函数
		执行了Men::Men()构造函数
		男人喜欢吃米饭*/
	Women* pwomen = new Women;
	pwomen->eat(); //调用了Women类的eat函数
		/*执行了Human::Human()构造函数
		执行了Women::Women()构造函数
		女人喜欢吃面食*/
	Human* phuman = new Human;
	phuman->eat();//调用了Human类的eat函数
		/*执行了Human::Human()构造函数
		人类吃各种粮食*/



	Human* phuman2 = new Men;//父类指针指向子类对象
	//执行了Human::Human()构造函数
	//执行了Men::Men()构造函数

	//在父类改成员函数前 加 virtual 
	phuman2->eat();//调用了Human类的eat函数    男人喜欢吃米饭

}

void test03() {

	Human* phuman = new Men;  //父类Human指针指向子类Men对象
	phuman->eat();            //男人喜欢吃米饭，调用的是Men类的eat函数
	delete phuman;

	phuman = new Women;       //父类Human指针指向子类Women对象
	phuman->eat();            //女人喜欢吃面食，调用的是Women类的eat函数
	delete phuman;

	phuman = new Human;       //父类Human指针指向父类(本身)对象
	phuman->eat();            //人类吃各种粮食，调用的是Human类的eat函数
	delete phuman;

	Human* phuman2 = new Men;  //父类Human指针指向子类Men对象
	phuman2->eat();            //男人喜欢吃米饭，调用的是Men类的eat函数
	phuman2->ovr();
	phuman2->Human::eat();     //人类吃各种粮食，调用的是Human类的eat函数，注意调用格式
	delete phuman2;
}

//多态性
//只是针对虚函数提出的  ，面向对象编程思想里的一个概念  多态



//纯虚函数
void test04() {
	//Human2* phuman2 = new Human2; //不合法，含纯虚函数的类不允许创建对象
	//Human2 human2;                //不合法，含纯虚函数的类不允许创建对象
	Human2_sub* psubhuman2 = new Human2_sub; //没问题
	Human2_sub subhuman;  //没问题

}

//父类的析构函数一般写为虚函数
void test05() {
	Men men;
		/*执行了Human::Human()构造函数
		执行了Men::Men()构造函数
		执行了Men::~Men()析构函数
		执行了Human::~Human()析构函数*/
}

void test06() {

	Men* pmen = new Men;
	delete pmen; //先调用子类的析构函数，再调用父类的析构函数

	cout << "-----------------" << endl;
	Human* phuman = new Men; //先调用父类构造函数，再调用子类构造函数
	cout << "-----------------" << endl;
	delete phuman; //只调用了父类析构函数，这就坏了，没有调用子类的析构函数

}
int main() {

	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	test06();
	return 0;
}