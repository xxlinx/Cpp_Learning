#include <iostream>
#include <vector>

using namespace std;

//隐式转换
void test01() {

	int m = 3 + 45.6;   //48
	double n = 3 + 45.6;  //48.6
}

//显式转换
//c风格
void test02() {
	//int k = 5 % 3.2; //语法错，系统要求%两侧必须整型
	int k = 5 % (int)3.2; //没问题
	//int k = 5 % int(3.2);//没问题
}
//c++风格
//1. static_cast 
//相关类型的转换
void test03() {
	double f = 100.34f;
	int i = (int)f;  //C风格的
	int i2 = static_cast<int>(f); //100，C++风格的
}
//子类转换成父类
void test04() {
	class A  //父类
	{
	};
	class B :public A  //子类
	{
	};

	B b;
	A a = static_cast<A>(b);  //把子类转成父类可以，但父类转成子类是不可以的

}
//void* 与其他类型指针的转换  void* 无类型的指针，可以指向任何指针类型（万能指针）
void test05() {
	int i = 10;
	int* p = &i;
	void* q = static_cast<void*>(p);
	int* db = static_cast<int*>(q); //原本就是int指针还要转回int否则，可能转完里面的值就是错的

	double f = 100.0;
	double* pf = &f;
	//int* i = static_cast<int*>(pf); //不可以，无法编译通过
	//float* fd = static_cast<float*>(pf); //不可以，无法编译通过
}

//2. dynamic_cast
//主要用于进行父类转成子类  在类里在详细说

//3. const_cast 去除指针或者引用的const属性
void test06() {
	const int  ai = 90;
	//int ai2 = const_cast<int>(ai); //ai不是指针，不是引用，所以不能转

	const int* pai = &ai;
	int* pai2 = const_cast<int*>(pai);//语法正确
	*pai2 = 120; //通过这个写值是未定义行为，不要这么干,因为这里实际上是const的
	cout << ai << endl; //调试下断点观察是120，打印出来实际是90
	cout << *pai << endl;//调试下断点观察是120，打印出来实际也是120
	//不能改变表达式类型
	int i = 10;
	//double d = const_cast<double>(i); //这不可以，用static_cast才行
}

//4. reinterpret_cast   这个类型转换相当随意
void test07() {
	int i = 10;
	int* pi = &i;
	int* p2 = reinterpret_cast<int*>(&i);
	char* pc = reinterpret_cast<char*>(pi);

	
	void* pvoid = reinterpret_cast<void*>(pi); //可以
	int* pi2 = reinterpret_cast<int*>(pvoid);  //可以

	int iv1 = 100;
	long long lv1 = 8898899400; //8字节的， 88亿多，十六进制为：2,126A,6DC8	
	int* piv1 = (int*)iv1;  //C语言风格  = 0x00000064 {???}
	int* piv2 = reinterpret_cast<int*>(iv1); //= 0x126a6dc8 {???}
	piv2 = reinterpret_cast<int*>(lv1);  //0x126a6dc8 {???} 最前面的2丢了。int *这里是4字节
	long long ne = reinterpret_cast<long long>(piv2); //从指针类型到整型，十进制的308964808 等于十六进制的0x126a6dc8

}


int main() {
	test01();
	test02();
	test03();
	test04();
	test05();
	test06();


	return 0;
}