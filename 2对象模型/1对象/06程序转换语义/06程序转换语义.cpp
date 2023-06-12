#include <iostream>

using namespace std;

class X {
public:
	int m_i;
	X(const X& tmpx){
		m_i = tmpx.m_i;
		cout << "X类的拷贝构造函数被调用" << endl;
	}
	X(){
		m_i = 0;
		cout << "X类的构造函数被调用" << endl;
	}
	~X(){
		cout << "X类的析构函数被调用" << endl;
	}

public:
	void functest(){
		cout << "functest()成员函数被调用" << endl;
	}

};

//void func(X tmpx)
//void func(X &tmpx)
//{
//	return;
//}

X func() {
	X x0;
	//......
	return x0;
}

void func(X& extra) { //1：安插一个引用参数
	X x0;  //这个在我们看来之所以能调用构造函数，是因为编译器内部有诸如x0.X::X()这种代码
	//..
	extra.X::X(x0);  //2：return之前安插一个对拷贝构造函数的调用
	//return x0;
	return;
}


int main(){
	//{
	//	X x0;
	//	x0.m_i = 15;
	//	X x1 = x0;
	//	X x2(x0);
	//	X x3 = x0;


	//	//步骤一：定义一个对象，为对象分配内存，但这里编译器内部并没有调用构造函数。如果以编译器的眼光看X x3_2，则不会调用构造函数。除非编译器主动增加这种x3_2.X::X();这种代码行到现有的代码中
	//	X x3_2;
	//	//步骤二：直接调用对象的拷贝构造函数去了
	//	x3_2.X::X(x0);

	//}

	//{
	//	X x0;
	//	//func(x0); //程序员视角（现代编译器视角）

	//	//X x0;
	//	//X tmpx = x0;  

	//	//老编译器视角
	//	X tmpobj;  //编译器产生出来一个临时对象
	//	tmpobj.X::X(x0); //调用拷贝构造函数
	//	func(tmpobj); //用临时对象调用func
	//	tmpobj.X::~X(); //func()被调用完成后，析构函数被调用	
	//}
	{
		X my = func();
		cout << "断点设置在这里" << endl;
	}
	{
		//编译器视角
		X my; //从编译器的视角看，这里是不调用构造函数的,除非编译器主动增加代码my.X::X();
		func(my);
	}

	{
		func().functest();
	}
	{
		X my;
		(func(my), my).functest(); //逗号表达式，先求解表达式1，再求解表达式2，整个表达式的值是表达式2的值
	}

	{
		X(*pf)();   //定义函数指针
		pf = func;
		pf().functest();
	}
	{
		X my;
		void (*pf)(X&);
		pf = func;
		pf(my);
		my.functest();

	}
	return 0;
}