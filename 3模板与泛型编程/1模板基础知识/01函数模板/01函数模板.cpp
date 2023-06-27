#include <iostream>
using namespace std;


//使用命名空间便于组织
namespace _nmsp1
{
	/*int Sub(int tv1, int tv2){
		return tv1 - tv2;
	}

	float Sub(float tv1, float tv2){
		return tv1 - tv2;
	}*/

	template <typename T>
	T Sub(T tv1, T tv2){
		return tv1 + tv2;
	}
}
/*
template <typename V, typename T, typename U>
V Add(T tv1, U tv2) {
	return tv1 + tv2;
}
template <typename T, typename U>
auto Add2(T tv1, U tv2) -> decltype(tv1+tv2) {
	return tv1 + tv2;
}
template <typename T>
T mydouble(T tmpvalue) {
	return tmpvalue * 2;
}

double mydouble(double tmpvalue) {
	return tmpvalue * 2;
}

template<typename T>
void myfunc(T tmpvalue) {
	cout << "myfunc(T tmpvalue) 执行了" << endl;
}

template<typename T>
void myfunc(T* tmpvalue) {
	cout << "myfunc(T *tmpvalue)执行了" << endl;
}

void myfunc(int tmpvalue)
{
	cout << " myfunc(int tmpvalue)执行了" << endl;
}

template <typename T, typename U>
void tfunc(T& tmprv, U& tmprv2) {
	cout << "tfunc泛化版本" << endl;
	cout << tmprv << endl;
	cout << tmprv2 << endl;
}
template<> //全特化<>里就是空的
void tfunc(int& tmprv, double& tmprv2) {
	//替换原来的T,U，这格式要与泛化版本一一对应不然编译就报错，比如第二个参数写成double tmprv2就会报错
	cout << "-------------begin-------------" << endl;
	cout << "tfunc<int,double>特化版本" << endl;
	cout << tmprv << endl;
	cout << tmprv2 << endl;
	cout << "-------------end---------------" << endl;
}
//普通函数
void tfunc(int& tmprv, double& tmprv2) {
	cout << "-------------begin-------------" << endl;
	cout << "tfunc普通函数" << endl;
	cout << "-------------end---------------" << endl;
}*/


//偏特化
 /*
//从模板参数数量上的偏特化
template<typename U>
void tfunc<double, U>(double& tmprv, U& tmprv2) {
	cout << "-------------begin-------------" << endl;
	cout << "tfunc<double,U>偏特化版本" << endl;
	cout << tmprv << endl;
	cout << tmprv2 << endl;
	cout << "-------------end---------------" << endl;
}
//从模板参数范围上的偏特化
template <typename T, typename U>
void tfunc(const T& tmprv, U& tmprv2) {
	cout << "tfunc(const T& tmprv, U& tmprv2)重载版本" << endl;
}
//重载实现模板参数数量上的偏特化
template <typename U>
void tfunc(double& tmprv, U& tmprv2) {
	cout << "-------------begin-------------" << endl;
	cout << "类似于tfunc<double,U>偏特化的tfunc重载版本" << endl;
	cout << tmprv << endl;
	cout << tmprv2 << endl;
	cout << "-------------end---------------" << endl;
}*/

//普通函数
int mf(int tmp1, int tmp2) {
	return 1;
}
typedef int(*FunType)(int, int); //函数指针类型定义
template <typename T, typename F = FunType>
void testfunc(T i, T j, F funcpoint = mf) {
	cout << funcpoint(i, j) << endl;
}
template <typename T = int, typename U>
void testfunc2(U m){
	T tmpvalue = m;
	cout << tmpvalue << endl;
}

//template <typename T, typename U, int val = 100>
template <typename T, typename U, auto val = 100>
//template <typename T, typename U, double val = 100>
auto Add(T tv1, U tv2){
	return tv1 + tv2 + val;
}

template <double* p>
void mft() {
	cout << "mft()执行了" << endl;

}
double g_d = 1.3; //全局量

//template <typename T, int value>
//template <typename, int>
template <typename, typename int>
auto Add2() {
	return 100;
}


int main() {
	/******  基本范例   *******/
	int subv = _nmsp1::Sub(3, 5);
	cout << "subv = " << subv << endl;
	double subv2 = _nmsp1::Sub(4.7, 2.1);
	cout << "subv2 = " << subv2 << endl;

	/******  实例化   *******/
	//_nmsp1::Sub(3, 5.0);  这样不行，模板要求 类型精确匹配
	_nmsp1::Sub<double> (3, 5.0);
	_nmsp1::Sub(double(3), 5.0);

	/******  模板参数推断   *******/
	/*
	cout << Add<double>(15, 17.8) << endl;
	cout << Add2(15, 17.8) << endl; //用auto自动推断
	//自动推断
	int result = mydouble(15);
	//指定类型模板参数
	int result2 = mydouble<int>(16.9);
	//指定空模板参数列表
	auto result3 = mydouble<>(16.9);    //33.8  调用的是模板函数
	auto result4 = mydouble(16.9);    // 调用的是普通函数
	*/

	/******  重载   *******/
	/*
	myfunc(12);   //myfunc(int tmpvalue) 执行了
	char* p = nullptr;
	myfunc(p);    //myfunc(T *tmpvalue)执行了
	myfunc(12.1); //myfunc(T tmpvalue) 执行了
	*/
	/******  特化  *******/
	/*
	const char* p = "I Love China!";
	int i = 12;
	tfunc(p, i);
	//特化版本 往往代表从泛化版本中抽出来的一组子集
	int k = 12;
	double db = 15.8;
	tfunc(k, db);   // 没有普通函数时，执行的是全特化版本
	//有普通函数时，执行的是普通函数

	//偏特化 （局部特化）
	const int k2 = 12;
	tfunc(k2, db);   //tfunc(const T& tmprv, U& tmprv2)重载版本
	double j = 18.5;
	tfunc(j, i); //类似于tfunc<double,U>偏特化的tfunc重载版本
	*/

	/******  默认参数  *******/
	testfunc(15, 16);
	testfunc2(12);

	/******  非类型模板参数  *******/
	//cout << Add<float, float>(22.3f, 11.8f) << endl;
	//cout << Add<float, float, 800>(22.3f, 11.8f) << endl;
	mft<&g_d>();  // mft()执行了

	cout << Add2<int, 1>() << endl;


	return 0;
}
