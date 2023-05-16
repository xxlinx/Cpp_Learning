#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;
//可变参函数模板
template <typename...T>
void myfunct1(T...args) {
	cout << sizeof...(args) << endl;
	//sizeof...属于固定语法，用在可变参模板内部，用来表示收到的模板参数个数，只能针对这种...的可变参
	cout << sizeof...(T) << endl;    //类型名也行，效果一样
}
void test01() {
	myfunct1(); //0
	myfunct1(10, 20); //2
	myfunct1(10, 25.8, "abc", 68); //4，注意参数类型不同
}

template <typename T, typename...U>
void myfunct11(const T& firstarg, const U& ...otherargs) {
	//cout << sizeof...(firstarg) << endl; 
	//编译会出错，说明sizeof…只能用在一包类型或者一包形参上
	cout << sizeof...(otherargs) << endl;
}
void test02() {
	//myfunct11();    //语法错，必须要有一个firstarg
	myfunct11(10);  
	//firstarg对应第一个参数，因为没有其他参数，所以sizeof...(otherargs) = 0
	myfunct11(10, "abc", 12.7); 
	//firstarg对应这第一个参数，剩余两个参数，所以sizeof...(otherargs) = 2
}

//参数包的展开

//因为参数是被一个一个剥离，剥离到最后，参数个数就为0个了，
// 所以，此时就会调用到这个版本的myfunct2()
//递归终止函数
void myfunct2() //这是个普通函数，而不是函数模板
{
	cout << "参数包展开时执行了递归终止函数myfunc2()" << endl;
}
template <typename T, typename...U>
void myfunct2(const T& firstarg, const U& ...otherargs) {
	cout << "收到的参数值为:" << firstarg << endl;
	myfunct2(otherargs...);//递归调用，注意塞进来的是一包形参，这里...不能省略
}
void test03() {
	myfunct2(10, "abc", 12.7);
}

//可变参类模板

//通过递归继承的方式展开
//主模板定义（泛化版本的类模板）
template<typename ...Args>
class myclasst
{
//public:
//	myclasst()
//	{
//		printf("myclasst::myclasst()泛化版本执行了,this = %p\n", this);
//	}
};
template<>
class myclasst<>  //一个特殊的特化版本
{
public:
	myclasst()
	{
		printf("myclasst<>::myclasst()特殊的特化版本执行了,this = %p\n", this);
	}
};
template<typename First, typename... Others>
class myclasst<First, Others...> : private myclasst<Others...> //偏特化
{
public:
	myclasst() :m_i(0)
	{
		printf("myclasst::myclasst()偏特化版本执行了,this = %p,sizeof...(Others)=%d\n", this, sizeof...(Others));
	}
	//注意这第二个参数，这一包东西的写法
	myclasst(First parf, Others... paro) :m_i(parf), m_o(paro...)//, myclasst<Others...>(paro...)
	{
		cout << "-----------------begin------------------" << endl;
		printf("myclasst::myclasst(parf,...paro)执行了,this = %p\n", this);
		cout << "m_i = " << m_i << endl;
		cout << "-----------------end------------------" << endl;
	}

	First m_i;
	myclasst<Others...> m_o;
	
};
void test04() {
	myclasst<int, float, double>myc;
}

void test05() {
	myclasst<int, float, double> myc;
}

void test06() {
	myclasst<int, float, double> myc(12, 13.5, 23);
}

//通过递归组合方式展开参数包



int main() {

	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	test06();


	return 0;
}