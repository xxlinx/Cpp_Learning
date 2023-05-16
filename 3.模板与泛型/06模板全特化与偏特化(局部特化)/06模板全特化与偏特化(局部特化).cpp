#include <iostream>
#include <vector>
#include <map>

using namespace std;

//类模板特化
//常规全特化
template <typename T, typename U>//泛化的类模板
struct TC 
{
	TC()
	{
		cout << "TC泛化版本构造函数" << endl;
	}
	void functest() {
		cout << "TC泛化版本" << endl;
	}
};

template<>  // 全特化所有类型模板参数都用具体类型代表，所以<>里就空了
struct TC<int, int> {//上面的T绑定到这里的第一个int，上面的U绑定到这里的第二个int
	TC() {
		cout << "TC<int,int>特化版本构造函数" << endl;
	}
	//在这里可以对该特化版本做单独处理
	void functest() {
		cout << "TC<int,int>特化版本" << endl;
	}

};

template<>
struct TC<double, int> //上面的T绑定到这里的double，上面的U绑定到这里的int
{
	TC()
	{
		cout << "TC<double,int>特化版本构造函数" << endl;
	}
	//在这里可以对该特化版本做单独处理。
	void functest() {
		cout << "TC<double,int>特化版本" << endl;
	}
};

void test01() {
	TC<char, int> tcchar; //TC泛化版本构造函数
	tcchar.functest(); //TC泛化版本

	TC<int, int> tcint; //TC<int,int>特化版本构造函数
	tcint.functest();  //TC<int,int>特化版本

	TC<double, int> tcdouble; //TC<double,int>特化版本构造函数
	tcdouble.functest(); //TC<double,int>特化版本
}

//特化类版本的成员函数
template<> //全特化
void TC<double, double>::functest()
{
	cout << "TC<double,double>的functest()特化版本" << endl;
}
void test02() {
	TC<double, double> tdbldbl;//TC泛化版本构造函数
	tdbldbl.functest(); //TC<double,double>的functest()特化版本
}


//类模板偏特化（局部特化）
template <typename T, typename U, typename W>
struct TCP
{
	TCP()
	{
		cout << "TCP泛化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCP泛化版本" << endl;
	}
};
//从模板参数数量上的偏特化
template <typename U>   //另外2个模板参数被绑定了，所以这里只剩一个模板参数U了，当然必须写出来
struct TCP<int, U, double> //注意，这里绑了第一个和第三个模板参数，留下了第二个模板参数
{
	TCP()
	{
		cout << "TCP<int,U,double>偏特化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCP<int,U,double>偏特化版本" << endl;
	}
};
void test03() {
	TCP<double, int, double> tcpdi; //TCP泛化版本构造函数
	tcpdi.functest(); //TCP泛化版本

	TCP<int, int, double> tcpii; //TCP<int,U,double>偏特化版本构造函数
	tcpii.functest(); //TCP<int,U,double>偏特化版本
}


template <typename T>
struct TCF
{
	TCF()
	{
		cout << "TCF泛化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCF泛化版本" << endl;
	}
};
//从模板参数范围上的偏特化
template <typename T>
struct TCF<const T>  //const特化版本
{
	TCF()
	{
		cout << "TCF<const T>特化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCF<const T>特化版本" << endl;
	}
};
template <typename T>
struct TCF<T*>  //T* 特化版本，告诉编译器，如果使用者用指针，则调用这个版本
{
	TCF()
	{
		cout << "TCF<T *>特化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCF<T*>特化版本" << endl;
	}
};
//左值引用
template <typename T>
struct TCF<T&>  //左值 引用特化版本
{
	TCF()
	{
		cout << "TCF<T &>特化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCF<T &>左值引用特化版本" << endl;
	}
};
//右值引用
template <typename T>
struct TCF<T&& >  //右值 引用特化版本
{
	TCF()
	{
		cout << "TCF<T &&>特化版本构造函数" << endl;
	}
	void functest() {
		cout << "TCF<T &&>右值引用特化版本" << endl;
	}
};
void test04() {
	TCF<double> td;  //TCF泛化版本构造函数
	td.functest();   //TCF泛化版本

	TCF<double*> tcfd; //TCF<T *>特化版本构造函数
	tcfd.functest();  //TCF<T*>特化版本

	TCF<const int> tcfi; //TCF<const T>特化版本构造函数
	tcfi.functest();   //TCF<const T>特化版本

	TCF<int&> tcfyi;   //TCF<T &>特化版本构造函数
	tcfyi.functest();  //TCF<T &>左值引用特化版本

	TCF<int&&> tcfyii; //TCF<T &&>特化版本构造函数
	tcfyii.functest(); //TCF<T&&>右值引用特化版本
}

//函数模板特化   不可以偏特化
template <typename T, typename U>
void tfunc(T& tmprv, U& tmprv2)
{
	//T = const char *;  tmprv = const char * &	
	cout << "tfunc泛化版本" << endl;
	cout << tmprv << endl; //I Love China!
	cout << tmprv2 << endl; //12
}
//函数模板全特化
template<> //全特化<>里就是空的
void tfunc(int& tmprv, double& tmprv2) //替换原来的T,U，这格式要与泛化版本一一对应不然编译就报错，比如第二个参数写成double tmprv2就会报错
{
	cout << "-------------begin-------------" << endl;
	cout << "tfunc<int,double>特化版本" << endl;
	cout << tmprv << endl; 
	cout << tmprv2 << endl; 
	cout << "-------------end---------------" << endl;
}
void test05() {
	int k = 12;
	double db = 15.8f;
	tfunc(k, db);  //这里调用的就是特化版本
}



int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	test05();
	return 0;
}
