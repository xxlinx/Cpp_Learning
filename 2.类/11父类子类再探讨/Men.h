
#ifndef __MEN__
#define __MEN__

#include "Human.h"

//class AA final {  }; //AA不可以做基类
//class BB : public AA {  }; //编译报错，因为AA不能做基类

//class AA {};
//class BB final : public AA {}; //如果BB不想做基类
//class CC :public BB {}; //编译错误，BB不能做基类


class A  //定义类A
{
public:
	A(int i) :m_valuea(i) {}; //构造函数带一个参数
	virtual ~A() {}
	void myinfoA()
	{
		std::cout << m_valuea << std::endl;
	}
private:
	int m_valuea;
};
class B :public A
{
public:
	B(int i, int j, int k) :A(i), m_valuec(k) {}; //注意因为父类A的构造函授要求参数，所以在子类的构造函数初始化列表里要提供参数。这里格式是：类名加上圆括号，圆括号内部是实参列表，以这样的形式为类A的构造函数提供初始值
	virtual ~B() {}
	void myinfoB()
	{
		std::cout << m_valuec << std::endl;
	}
private:
	int m_valuec;
};



class Men : public Human
{
	friend  void func(const Men& tmpmen);    //一个声明，表明该函数是本类的友元函数

public:
	using Human::samenamefunc; //using声明让父类函数在子类可见

public:
	Men();
	virtual ~Men();
public:
	void samenamefunc(int); 
	void funcmen() {};	
	virtual void eat() override;
	virtual CSuiBian_Sub* ovr() {return NULL;}

	void testfunc()
	{
		std::cout << "testfunc" << std::endl;
	}

	
//public:
private:
	void funcmen2() const
	{
		std::cout << "Men:funcmen2" << std::endl;
	};

};
#endif
