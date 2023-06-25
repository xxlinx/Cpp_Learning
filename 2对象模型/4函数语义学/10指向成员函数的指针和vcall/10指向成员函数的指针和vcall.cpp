#include <iostream>
#include <time.h>
#include <cstdio>


using namespace std;

//将一个成员函数的地址转换成普通地址
template<typename dst_type, typename src_type>
dst_type pointer_cast(src_type src){
	return *static_cast<dst_type*>(static_cast<void*>(&src));
}
class TDF{
public:
	void myf(int val){
		cout << "myf()成员函数执行了" << endl;
	}
};

class A {
public:
	void myfunc1(int tempvalue1) {
		cout << "tempvalue1 = " << tempvalue1 << endl;
	}
	void myfunc2(int tempvalue2) {
		cout << "tempvalue2 = " << tempvalue2 << endl;
	}
public:
	static void mysfunc(int tempvalue) {
		cout << "A::mysfunc()静态成员函数执行了，tempvalue = " << tempvalue << endl;
	}

public:
	virtual void myvirfuncPrev(int tempvalue) {
		cout << "A::myvirfuncPrev()虚成员函数执行了，tempvalue = " << tempvalue << endl;
	}
	virtual void myvirfunc(int tempvalue) {
		cout << "A::myvirfunc()虚成员函数执行了，tempvalue = " << tempvalue << endl;
	}
public:
	virtual ~A() {

	}
};

class B :public A {
public:
	virtual void myvirfunc(int tempvalue) {
		cout << "B::myvirfunc()虚成员函数执行了，tempvalue = " << tempvalue << endl;
	}
	virtual ~B() {
	}
};

int main() {

	/*********不用类对象能否调用类的虚函数和普通成员函数**********/
	//从本质上将，只要有函数的地址，就可以去直接调用函数
	/*
	printf("TDF::myf的地址是%p\n", &TDF::myf);
	typedef void (*Func)();
	Func fun1 = pointer_cast<Func>(&TDF::myf);
	void* func2 = pointer_cast<void*>(&TDF::myf);
	fun1();  //把成员函数当普通函数调用
	//确实可以直接调用
	*/

	/********指向成员函数的指针*******/
	//这种常规（非静态）成员函数，要想调用，都需要一个对象来调用
	/*
	A mya;

	void (A:: * pmypoint)(int tempvalue) = &A::myfunc1; //定义一个成员函数指针并给初值
	pmypoint = &A::myfunc2; //给成员函数指针赋值

	//通过成员函数指针来调用成员函数
	(mya.*pmypoint)(15); //要使用成员函数指针来调用成员函数，必须要对象介入

	A* pmya = new A();
	(pmya->*pmypoint)(20); //用对象指针介入来使用成员函数指针 来调用成员函数

	//对于静态成员函数
	void (*pmyspoint)(int tempvalue) = &A::mysfunc; //一个普通的函数指针，而不是成员函数指针
	pmyspoint(80); //从编译器角度看也是这个代码，不需要有个所谓的this指针
	*/
	/*********** 指向虚成员函数和指针和vcall *********/
	/*
	void (A:: * pmyvirfunc)(int tempvalue) = &A::myvirfunc;

	A* pvaobj = new A;
	pvaobj->myvirfunc(190);  //调用虚函数表完成
	
	(pvaobj->*pmyvirfunc)(190); //用成员函数指针来调用虚函数
	//依旧是通过虚函数表实现完成的

	printf("%p\n", &A::myvirfunc);
	//&A::myvirfunc; 代表一个地址，这个地址中有一段代码，这段代码记录的是该虚函数在虚函数表的一个偏移值
	//有了偏移值，有了具体对象指针就可以知道调用的是哪个虚函数表的哪个虚函数了。

	//但如是调用普通函数，不存在vcall(virtual call),是直接调用
	pmyvirfunc = &A::myfunc2;
	(pvaobj->*pmyvirfunc)(33);
	*/

	/********  vcall在继承关系中的体现  *******/
	B* pmyb = new B();
	void (B:: * pmyvirfunc)(int tempvalue) = &A::myvirfunc;//成员函数指针
	//void (B:: * pmyvirfunc)(int tempvalue) = &B::myvirfunc;
	(pmyb->*pmyvirfunc)(190);
	//B::myvirfunc()虚成员函数执行了，tempvalue = 190

	printf("%p\n", &A::myvirfunc);//00641361
	printf("%p\n", &B::myvirfunc);//00641221
	//说明这两个vcall thunk 地址值是不一样的

	return 0;
}