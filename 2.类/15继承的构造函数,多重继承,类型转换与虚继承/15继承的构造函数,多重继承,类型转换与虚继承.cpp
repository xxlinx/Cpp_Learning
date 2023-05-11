#include <iostream>
#include <vector>

using namespace std;   //后面再使用诸如std::cout时就可以简写成cout了；

/*
class A
{
public:
	A(int i, int j, int k) {};
};
//class B :public A
//{
//public:
//	B(int i, int j, int k) :A(i, j, k) {}
//};
class B :public A
{
public:
	using A::A;  //继承A的构造函数
};
*/
class Grand //爷爷类
{
public:
	Grand(int i) :m_valuegrand(i)
	{
		cout << "Grand类构造函数执行了" << endl;
	};
	virtual ~Grand()
	{
		cout << "Grand类析构函数执行了" << endl;
	}
	void myinfo()
	{
		cout << m_valuegrand << endl;
	}
public:
	int m_valuegrand;

public:
	static int m_static;
};
int Grand::m_static = 5;  //如果在代码中没有用到该静态成员变量，则可以不定义，但用到了必须定义否则链接时会报错
//class A : public Grand //继承自爷爷类
class A : virtual public Grand
{
public:
	A(int i) :Grand(i), m_valuea(i)
	{
		cout << "A类构造函数执行了" << endl;
	} //每个子类的构造函数，负责解决自己父类的初始化问题
	virtual ~A()
	{
		cout << "A类析构函数执行了" << endl;
	}
	void myinfo()
	{
		cout << m_valuea << endl;
	}
public:
	int m_valuea;
	//int m_valuegrand;
};

//class A2 : public  Grand
class A2 : public virtual Grand // public和virtual顺序互换没关系
{
public:
	A2(int i) :Grand(i), m_valuea2(i)
	{
		cout << "A2类构造函数执行了" << endl;
	};
	virtual ~A2()
	{
		cout << "A2类析构函数执行了" << endl;
	}
	void myinfo()
	{
		cout << m_valuea2 << endl;
	}
public:
	int m_valuea2;
	//int m_valuegrand;
};


class B  //该类没继承自任何类
{
public:
	/*B()
	{
		cout << "B类默认构造函数执行了" << endl;
	};*/

	B(int i) :m_valueb(i)
	{
		cout << "B类构造函数执行了" << endl;
	};
	virtual ~B()
	{
		cout << "B类析构函数执行了" << endl;
	}
	void myinfo()
	{
		cout << m_valueb << endl;
	}
public:
	int m_valueb;
};

//类C，公有继承父类A，公有继承父类B，如果这个public不写，默认继承的话，则看C，如果C是class则默认是private继承，如果C是struct，则是public继承
//class C :public A, public B  //C++语言没明确规定父类可以有多少个
class C :public A, public A2, public B
{
public:
	//C(int i, int j, int k) :A(i), B(j), m_valuec(k) {}; //注意因为父类A,B的构造函授都要求参数，所以在子类的构造函数初始化列表里要提供参数。这里格式是类名加上圆括号，内部是实参列表，以这样的形式为A和B的构造函数提供初始值
	//C(int i, int j, int k) :A(i), m_valuec(k) { };
	//C(int i, int j, int k) :A(i), A2(i),B(j), m_valuec(k) {};

	C(int i, int j, int k) :A(i), A2(i), B(j), Grand(i), m_valuec(k) {};

	virtual ~C() {}
	void myinfoC()
	{
		cout << m_valuec << endl;
		A::myinfo(); //调用父类A的myinfo函数
		B::myinfo(); //调用父类B的myinfo函数
		myinfo(); //这不可以，系统会糊涂 

	}
	void myinfo()
	{
		cout << m_valuec << endl;
	}

public:
	int m_valuec;
	//int m_valuegrand;
};


//class AA {
//public:
//	AA(int tv) {};
//};
//class BB {
//public:
//	BB(int tv) {};
//};
//class CC :public AA, public BB {

//public:
//	using AA::AA;  //继承A的构造函数
//				    //等价于 C (int tv):A(tv){}	
//	using BB::BB;  //这行会产生错误
//				   //等价于 C (int tv):B(tv){}	

//	CC(int tv) :AA(tv), BB(tv) {};	//定义自己的版本
//};



int main()
{
	{
		//B ad(3, 4, 5);
	}
	//{
	//	C ctest(10, 20, 50); //跟踪调试，发现 分别调用类A和类B的构造函数
	//	ctest.myinfoC();     //50

	//	ctest.myinfo(); //系统不明白是调用父类A还是B的成员函数，因而编译会报错
	//	ctest.A::myinfo(); //10

	//	Grand::m_static = 1; //可以用类名来引用静态变量，此时用::
	//	A::m_static = 2;
	//	//B::m_static = 3; //不可以,这个静态量不属于B
	//	C::m_static = 4;
	//	ctest.m_static = 5; //可以对象名来引用静态变量，此时用.

	//}
	{
		//C ctest(10, 20, 50);
	}
	/*{
		Grand* pg = new C(1, 2, 3);
		A* pa = new C(1, 2, 3);
		B* pb = new C(4, 5, 6);
		C myc(6, 7, 8);
		Grand mygrand(myc);

	}*/
	{
		C ctest(10, 20, 50);
		ctest.m_valuegrand = 10;
	}
	return 0;
}

