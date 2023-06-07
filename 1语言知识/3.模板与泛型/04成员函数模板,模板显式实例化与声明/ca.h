#pragma once

//类模板的成员函数模板
template<typename C>
class A {
public:
	template<typename T2>
	A(T2 v1, T2 v2);
	//构造函数也引入自己的模板参数T2，和整个类的模板参数C没有关系

	//成员函数模板
	template <typename T>
	void myft(T tmpt)
	{
		std::cout << tmpt << std::endl;
	}
	//普通成员函数
	void myftpt() {}

	//成员变量
	C m_ic;
};

template<typename C>//先跟类模板的模板参数列表，这个要排在上面
template<typename T2>//再跟构造函数模板自己的模板参数列表
A<C>::A(T2 v1, T2 v2) {
	std::cout << v1 << " " << v2 << std::endl;
}

//函数模板
template <typename T>
void myfunc(T v1, T v2)
{
	std::cout << v1 + v2 << std::endl;
}