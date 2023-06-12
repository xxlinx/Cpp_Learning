#include <iostream>

using namespace std;

//拷贝构造语义
class ASon
{
public:
	int m_testson;
};

//class A
//{
//public:
//	int m_test;
//};



//class CTB
//{
//public:
//	CTB(const CTB&) //拷贝构造函数
//	{
//		cout << "CTB类的拷贝构造函数执行了" << endl;
//	}	
//	CTB() //缺省构造函数
//	{
//	}
//};
//class CTBSon :public CTB
//{
//public:
//};
class CTB
{
public:
	virtual void mvirfunc() {}
};

//
//class CTBSon //:public CTB
//{
//public:
//	virtual void mvirfunc() {}; //定义一个虚函数
//};
class CTBSon :public CTB
{
public:
	//virtual void mvirfunc() {}
};


//class A
//{
//public:
//	int m_test;
//	ASon asubobj;
//	CTB m_ctb;
//};

class Grand //爷爷类
{
public:
};
class A : virtual public  Grand
{
public:
};
class A2 : virtual  public  Grand
{
public:
};
class C :public A, public A2
{
public:
};


//移动构造语义
struct TC
{
	int i;          //内置类型可以移动
	std::string s;  //string类型定义了自己的移动操作
	//~TC() {}
};


int main()
{
	//{
	//	A mya1;
	//	mya1.m_test = 15;
	//	A mya2 = mya1;  //这属于拷贝构造动作，但编译器没有合成拷贝构造函数
	//	cout << "断点设置在这里" << endl;
	//}
	/*{
		A mya1;
		mya1.m_test = 15;
		mya1.asubobj.m_testson = 120;
		A mya2 = mya1;
		cout << "断点设置在这里" << endl;
	}*/
	/*{
		CTBSon myctbson1;
		CTBSon myctbson2 = myctbson1;

	}*/

	//{
	//	C cc;
	//	C cc2 = cc;

	//}
	TC a;
	a.i = 100;
	a.s = "I Love China!";
	const char* p = a.s.c_str();
	TC b = std::move(a);  //导致结构/类TC移动构造函数的执行,数据移动不是std::move所为，而是string的移动构造函数所为
	const char* q = b.s.c_str();


	return 0;

}
