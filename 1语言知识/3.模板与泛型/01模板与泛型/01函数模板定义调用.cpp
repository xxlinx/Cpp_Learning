#include <iostream>
#include <vector>
#include<string>
using namespace std;

//int funadd(int i1, int i2) //求和函数
//{
//	int addhe = i1 + i2;
//	return addhe;
//}
//
//float funadd(float d1, float d2)
//{
//	float addhe = d1 + d2;
//	return addhe;
//}


//函数模板的定义

template<typename T> //定义函数模板
T funadd(T a, T b)
{
	T addhe = a + b;
	return addhe;
}
//函数模板调用   模板参数有时候是推断出来的，有时候主动提供模板参数
void test01() {
	int he = funadd(1, 2);
	cout << he << endl;    //3
	float he2 = funadd(3.1f, 1.2f);
	cout << he2 << endl;   //4.3

	//float he = funadd(3, 1.2f);  未找到匹配参数
}

//非类型模板参数
template<int a, int b> //定义函数模板
int funcaddv2()
{
	int addhe = a + b;
	return addhe;
}
//调用   用< > 来传参  显示的指定模板参数，在<>中提供额外的信息  参入的必须是常量表达式
void test02() {
	int result = funcaddv2<12, 13>(); //要通过<>来传递参数，就得看模板函数的<>里有几个参数。这种<>写法就是显式指定模板参数,在尖括号中提供额外信息
	cout << result << endl; //25

	int a = 12;
	//int result = funcaddv2<a, 14>();  //这里是运行的时候才确定
	//这不可以，非类型模板参数必须是常量表达式
	//值必须是在编译的时候就能确定，因为实例化模板是在编译的时候做的事
}


template<typename T, int a, int b>
int funcaddv3(T c)
{
	int addhe = (int)c + a + b;
	return addhe;
}
void test03() {
	int result = funcaddv3<int, 11, 12>(13);
	cout << result << endl; //36
	
	//把int 换成 double
	int result2 = funcaddv3<double, 11, 12>(13);
	//此时系统以<>传进去的类型为准，而不是以13推断出来的类型为准
	cout << result2 << endl; //36
}


template<unsigned L1, unsigned L2> //本例依旧没有类型参数， 只有非类型模板参数
int charscomp(const char(&p1)[L1], const char(&p2)[L2])
{
	return strcmp(p1, p2);
}
//模板函数可以是内联函数 
//template<unsigned L1, unsigned L2>
//inline int charscomp(const char(&p1)[L1], const char(&p2)[L2])
//{
//	return strcmp(p1, p2);
//}
void test04() {
	int result = charscomp("test2", "test"); 
	//根据test2能推断出大小是6个(算末尾的\0)取代L1，
	//L2同理，推断出大小是5个	不用手动提供<6, 5>	
	cout << result << endl; //1
}
//实例化出来就是这样的
//int charscomp(const char(&p1)[6], const char(&p2)[5]) { }

int main() {
	//test01();
	//test02();
	//test03();
	test04();
	return 0;
}

//模板定义并不会导致编译器生成代码。
//只有在我们调用这个函数模板时
//编译器为我们实例化了一个特定版本的函数之后，编译器才会生成代码

//通常函数模板放在 .h 头文件中  函数模板定义就可以在头文件中  不存在重定义的情况