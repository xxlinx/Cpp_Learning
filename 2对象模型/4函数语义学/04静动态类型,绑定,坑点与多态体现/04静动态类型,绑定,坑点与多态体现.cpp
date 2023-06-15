#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class Base{
public:
	void myfunc(){
		cout << "Base::myfunc()" << endl;
	}
	/*virtual void myvirfunc(){
		cout << "Base::myvirfunc()" << endl;
	}*/
	virtual void myvirfunc(int value = 1){
		cout << "Base::myvirfunc(),value=" << value << endl;
	}
};
class Derive : public Base{
public:
	void myfunc(){
		cout << "Derive::myfunc()" << endl;
	}
	//virtual void myvirfunc()
	//{
	//	cout << "Derive::myvirfunc()" << endl;
	//}
	virtual void myvirfunc(int value = 2){
		cout << "Derive::myvirfunc(),value=" << value << endl;
	}


};
class Derive2 : public Base{
public:
};

class A{
public:
	virtual void myvirfunc() {}
};


int main() {
	/*
	Base base;   //静态类型是Base
	Derive derive; //静态类型是Derive
	Base* pbase;  //别管指向啥，反正定义的时候定义的是Base *，所以静态类型是Base *
	Base* pbase2 = new Derive();//静态类型依旧是Base *
	Base* pbase3 = new Derive2();//静态类型依旧是Base *
	*/

	//静态绑定 动态绑定
	/*
	Derive derive;
	Derive* pderive = &derive;
	pderive->myfunc();   //Derive::myfunc()

	Base* pbase = &derive;
	pbase->myfunc();   //Base::myfunc(),这里调用的居然是父类的myfunc，是个陷阱，写程序时一定要注意

	Base base;
	pderive->myvirfunc(); //Derive::myvirfunc()
	pbase->myvirfunc();   //Derive::myvirfunc()
	pbase = &base;
	pbase->myvirfunc();   //Base::myvirfunc()
	return 0;
	*/

	//从代码实现上看多态
	/*
	A* pa = new A();
	pa->myvirfunc(); //这是不是多态，是多态的

	A a;
	a.myvirfunc(); //这个就不是多态的

	A* ya = &a;
	ya->myvirfunc(); //这个也是多态
	*/

	//从表现形式上看多态(最终也是通过代码体现)

	Derive derive2;
	Base& yinbase = derive2;
	yinbase.myvirfunc(); //Derive::myvirfunc()  value = 1

}
