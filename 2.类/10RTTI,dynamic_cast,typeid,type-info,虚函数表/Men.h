
#ifndef __MEN__
#define __MEN__

#include "Human.h"

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

	void testfunc()  //普通的成员函数
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
