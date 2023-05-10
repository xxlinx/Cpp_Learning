#include <iostream>
#include <vector>

#include "Time.h"

using namespace std;

//声明的时候加static  定义的时候不用
int Time::mystatic = 5; //可以不给初值，那么系统默认会给0，定义时这里不需要用static了


//const 
void test01() {

	const Time abc; //定义const对象，这种对象有限制
	//abc.addhour(12); //不可以，addhour成员函数是非const的，只能被非const对象调用
	abc.noone(); //可以，因为noone成员函数是const的

	Time def;
	def.noone(); //const成员函数，则不管const对象，还是非const对象都可以调用const成员函数（万人迷，性格好）
	//而非const成员函数呢？不能被const对象调用，只能被非const对象调用。

}

//mutable  突破const 的限制


//this 返回自身对象的引用
void test02() {
	Time mytime;
	mytime.rtnhour(3);
	//因为返回的是对象自身
	//还可以这样写
	mytime.rtnhour(3).rtnminute(5);

}

//static成员变量   静态成员变量   属于整个类
void test03() {
	Time mytime1; //调用的是无参构造函数
	mytime1.Minute = 15;

	Time mytime2;
	mytime2.Minute = 30;   //这两个对象的Minute 是不同的，彼此互不影响

	cout << Time::mystatic << endl; //5

	mytime1.mystatic = 12;  //可以用对象名.引用静态成员变量

	cout << Time::mystatic << endl;  //12
	cout << mytime1.mystatic << endl; //12
	cout << mytime2.mystatic << endl; //12

	Time::mstafunc(1288);
	cout << Time::mystatic << endl;  //1288

	mytime1.mstafunc(2000);
	cout << Time::mystatic << endl;  //2000

}

int main() {

	test01();
	test02();
	test03();
	return 0;
}