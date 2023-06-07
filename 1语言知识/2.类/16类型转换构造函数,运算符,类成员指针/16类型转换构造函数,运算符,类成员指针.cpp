#include <iostream>
#include <vector>

using namespace std;


//一个类，里边保存0-100之间的数字
class TestInt {

public:
	TestInt(int x = 0) : m_i(x)  //类型转换构造函数，本构造函数可以将数字转换成类类型对象
	{
		if (m_i < 0)	m_i = 0; //限制一下范围
		if (m_i > 100)	m_i = 100;//限制一下范围
	}

	//类型转换运算符，可以从本类类型转换成其他类型
	operator int() const
	//explicit operator int() const
	{
		return m_i;
	}
	//operator double() const {}
	

	//typedef void(*tfpoint)(int) ; //类型定义【函数指针类型】，这个*后的tfpoint是类型名
	using tfpoint = void(*)(int);  //类型定义【函数指针类型】，这个using后的tfpoint是类型名，*后不能有tfpoint，本行等价于上面typedef行，以后会详细讲using的格式，这里只需要记住是类型定义
	//一个静态成员函数
	static void mysfunc(int v1) //静态成员函数
	{
		//随便写几句测试代码
		int test;
		test = 1;
	}

	//类型转换运算符，能把 本类类型对象 转换成一个 函数指针类型
	operator tfpoint() //const不是必加的
	{
		//那就必须要返回一个函数指针
		return mysfunc; //函数地址作为函数指针类型返回了
	}

public:
	int m_i;
};
//其他类型转换成类类型
void test01() {
	//TestInt ti = 12; //隐式类型转换，将数字转换成TestInt对象(调用类型转换构造函数)
	TestInt ti = TestInt(12); //这也是调用类型转换构造函数的
	TestInt ti2(22); //调用类型转换构造函数，但这个不是隐式类型转换

}
//类型转换运算符
void test02() {
	TestInt ti2;
	ti2 = 6;//隐式转换把6转成一个临时的TestInt对象，然后调用赋值运算符把临时对象给ti2
	//隐式调用
	int k = ti2 + 5;//k=11,这里调用operator int()将ti2转成int，结果为6，再和5做加法运算，结果给k
	//显示调用
	k = ti2.operator int() + 5;//11,调用operator int()将ti2转成int，结果为6，再和5做加法运算，结果给k
	
	k = static_cast<int>(ti2) + 5; //11,调用operator int()将ti2转成int，结果为6，再和5做加法运算，结果给k

	int k2 = ti2.operator int() + 5; //也可以显式的调用。注意写法，没有形参所以括号内为空
}
//类对象转换成函数指针
void test03() {
	TestInt myi(12);
	//myi(123); //执行operator tfpoint() ,然后会执行mysfunc成员函数  相当于调用了两个函数
	myi.operator TestInt::tfpoint()(123);
	//
}



//类型转换二义性
class CT1
{
public:
	CT1(int ct) {}; //类型转换构造函数
};
class CT2
{
public:
	CT2(int ct) {}; //类型转换构造函数
};
void testfunc(const CT1& C) {};
void testfunc(const CT2& C) {};

class CT
{
public:
	void ptfunc(int tmpvalue) { cout << "ptfunc普通成员函数被调用,value="<<tmpvalue << endl; }
	virtual void virtualfunc(int tmpvalue) { cout << "virtualfunc虚成员函数被调用,value=" << tmpvalue << endl; }
	static void staticfunc(int tmpvalue) { cout << "staticfunc静态成员函数被调用,value=" << tmpvalue << endl; }

public:
	int m_a;
public:
	static int m_stca; //声明静态成员变量
};
void test04() {
	//testfunc(101);   // //会报二义性，int可转换成CT1对象，也可以转换成CT2对象
	testfunc(CT1(101));
	//能明确调用void testfunc(const CT1 &C) {}; ,但是这种手段表明代码设计的不好
}


//类成员函数指针
//1.对于普通成员函数
void test05() {
	//有一说一 长得很怪异
	void (CT:: * myfpointpt)(int); //一个类成员函数指针变量的定义,变量名字为myfpoint
	myfpointpt = &CT::ptfunc;      //类成员函数指针变量myfpoint被赋值

	CT ct, * pct;
	pct = &ct;
	(ct.*myfpointpt)(100);
	//对象ct,调用成员函数指针变量myfpointpt所指向的成员函数
	(pct->*myfpointpt)(200);      
	//对pct所指的对象，调用成员函数指针变量myfpointpt所指向的成员函数
}
//2.对于虚成员函数
void test06() {
	//定义一个虚函数指针并赋值
	void (CT:: * myfpointvirtual)(int) = &CT::virtualfunc;
	CT ct, * pct;
	pct = &ct;
	(ct.*myfpointvirtual)(100);        //对象ct,调用指针变量myfpointvirtual所指向的虚成员函数
	(pct->*myfpointvirtual)(200);      //对pct所指的对象，调用指针变量myfpointvirtual所指向的虚成员函数		
}
//3.对于静态成员函数
void test07() {
	void(*myfpointstatic)(int) = &CT::staticfunc;
	//定义一个静态的类成员函数指针并给初值
	myfpointstatic(100);	
	//
	//直接使用静态成员函数指针名即可调用静态成员函数

}



//类成员变量指针
//1.普通成员变量
void test08() {
	int CT::* mp = &CT::m_a; //定义一个类成员变量指针，注意这种写法
	CT ct;
	ct.*mp = 189;  //通过类成员变量指针来修改成员变量值，等价于ct.m_a = 189
	cout << ct.*mp << endl; //189
	cout << ct.m_a << endl; //189
}
//2.静态成员变量
int CT::m_stca = 1; //定义一下类CT的静态成员变量
void test09() {
	int* stcp = &CT::m_stca; //定义一个静态成员变量指针
	*stcp = 796;  //等价于 CT::m_stca = 796
	cout << *stcp << endl; //796
}

int main() {

	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	test08();
	test09();
	return 0;
}