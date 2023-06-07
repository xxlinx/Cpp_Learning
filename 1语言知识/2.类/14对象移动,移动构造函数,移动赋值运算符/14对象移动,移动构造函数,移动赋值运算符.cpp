#include <iostream>
#include <vector>

using namespace std;
class B
{
public:
	B() :m_bm(100)
	{
		std::cout << "类B的构造函数执行了" << std::endl;
	}
	B(const B& tmp):m_bm(tmp.m_bm)
	{
		//m_bm = tmp.m_bm;
		std::cout << "类B的拷贝构造函数执行了" << std::endl;
	}
	virtual ~B()
	{
		std::cout << "类B的析构函数执行了" << std::endl;
	}
	int m_bm;
};
class A {

public:
	A() :m_pb(new B()) //这要调用类B的构造函数
	{
		std::cout << "类A的构造函数执行了" << std::endl;
	}
	A(const A& tmpa) : m_pb(new B(*(tmpa.m_pb))) //这要调用类B的拷贝构造函数
	{
		std::cout << "类A的拷贝构造函数执行了" << std::endl;
	}
	A(A&& tmpa) noexcept : m_pb(tmpa.m_pb)
	{
		tmpa.m_pb = nullptr;
		std::cout << "类A的移动构造函数执行了" << std::endl;
	}

	//拷贝赋值运算符
	A& operator=(const A& src)
	{
		if (this == &src)
			return *this;

		delete m_pb; //把自己原来这块内存干掉
		m_pb = new B(*(src.m_pb)); //重新分配一块
		std::cout << "类A的拷贝赋值运算符执行了" << std::endl;
		return *this;
	}

	//移动赋值运算符，末尾也增加noexcept
	A& operator=(A&& src) noexcept
	{
		if (this == &src)
			return *this;

		delete m_pb; //把自己原来这块内存干掉
		m_pb = src.m_pb;   //对方的内存直接拿过来
		src.m_pb = nullptr; //斩断源（也就是对方和该内存的关联）
		std::cout << "类A的移动赋值运算符执行了" << std::endl;
		return *this;
	}

	~A()
	{
		delete m_pb;
		std::cout << "类A的析构函数执行了" << std::endl;
	}
private:
	B* m_pb;
};
static A getA()
{
	A a;
	return a;  
	//在有移动构造函数的时候
	//这里会执行类A的移动构造函数，把对象a的数据移动给要返回的临时对象
}

void test01() {
	B* pb = new B();
	pb->m_bm = 19;
	B* pb2 = new B(*pb); //这种给参数的new系统会调用B类的拷贝构造函数
	delete pb;
	delete pb2;
		//类B的构造函数执行了
		//类B的拷贝构造函数执行了
		//类B的析构函数执行了
		//类B的析构函数执行了
}

void test02() {
	A a = getA();
		//类B的构造函数执行了
		//类A的构造函数执行了
		//类B的析构函数执行了
		//类A的析构函数执行了
}

void test03() {
	A a = getA();
	A a2(std::move(a)); //调用类A的移动构造函数
}

void test04() {
		A a = getA();       //移动构造，临时对象直接构造在a上
		A a2;               //普通构造
		//a2 = a;           //拷贝赋值运算符，换成如下
		a2 = std::move(a);  //移动赋值运算符
}

//合成的移动操作
struct TC
{
	int i;          //内置类型可以移动
	std::string s;  //string类型定义了自己的移动操作
};

void test05() {
	TC a;
	a.i = 100;
	a.s = "I Love China!";
	const char* p = a.s.c_str();

	TC b = std::move(a);  //导致  结构/类  TC移动构造函数的执行,数据移动不是std::move所为，而是string的移动构造函数所为；
	const char* q = b.s.c_str();

	cout << "断点放到这里" << endl;

}

int main() {

	//test01();
	//test02();
	//test03();
	test04();
	return 0;
}