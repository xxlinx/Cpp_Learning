#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1 {
	/*template <typename T>
	add_rvalue_reference_t<T> declval() noexcept;*/

	class A {
	public:
		A(int i) {
			printf("A::A()函数执行了,this = %p\n", this);
		}
		double myfunc() {
			printf("A::myfunc()函数执行了,this = %p\n", this);
			return 12.1;
		}

	private:
		~A() {}

	};

	template <typename T>
	//T& mydeclval() noexcept; //这里即便返回的类型是T&也可以
	T&& mydeclval() noexcept; //这里即便返回的类型是T&也可以


	class ALR {
	public:
		void onAnyValue() {
			cout << "ALR:: onAnyValue()函数执行了!" << endl;
		}
		void onLvalue()& {  //只能被类ALR的左值对象调用
			cout << "ALR::onLvalue()函数执行了!" << endl;
		}
		void onRvalue()&& { //只能被类A的右值对象调用
			cout << "ALR::onRvalue()函数执行了!" << endl;
		}
	};

}

/***   推导函数返回值范例   ***/
namespace _nmsp2 {
	//随便写一个函数用于测试目的
	int myfunc(int a, int b) {
		return a + b;
	}
	template<typename T_F, typename... U_Args>
	//decltype(std::declval<T_F>()(std::declval<U_Args>()...)) TestFnRtnImpl(T_F func, U_Args... args) //std::declval<>中的U_Args写成U_Args&&或U_Args&都可以
	auto TestFnRtnImpl(T_F func, U_Args... args) {
		auto rtnvalue = func(args...);
		return rtnvalue;
	}

	template<typename T_F, typename... U_Args>
	auto TestFnRtnImpl2(T_F func, U_Args... args) -> decltype(func(args...))
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}
}

int main() {
	/*
	using YT = decltype(std::declval<_nmsp1::A>()); 
	//千万不要把std::declval<A>后的圆括号丢掉，否则代码的含义就发生变化了，想象函数调用时即便函数没有参数也要带着一对空的圆括号

	//利用boos输出类型名的方式比 typeid(...).name()用法输出类型名更准确
	using boost::typeindex::type_id_with_cvr;
	cout << "YT=" << type_id_with_cvr<YT>().pretty_name() << endl;
	// YT=class _nmsp1::A && __ptr64

	_nmsp1::A myaobj(1); //必须为构造函数提供实参
	//A::A()函数执行了,this = 000000251939F414
	cout << "myaobj.myfunc()的返回类型=" << 
		type_id_with_cvr< decltype(myaobj.myfunc()) >().pretty_name() << endl;
	//myaobj.myfunc()的返回类型=double
	//这里没有调用成员函数就能得到返回类型

	cout << "A::myfunc()的返回类型=" <<
		type_id_with_cvr< decltype(std::declval<_nmsp1::A>().myfunc()) >().pretty_name() << endl;
	//A::myfunc()的返回类型=double
	//这里都没有创建对象一样得到返回值

	_nmsp1::A&& ayinobj();   //看起来是一个函数声明，函数返回值是_nmsp1::A&&
	//可以看作是一个_nmsp1::A&& 类型的对象

	//ayinobj();     //看着是在调用这个函数
	//ayinobj().myfunc();

	decltype(ayinobj().myfunc()) mydblvar; //定义一个double类型的变量mydblvar
	*/
	/*
	using boost::typeindex::type_id_with_cvr;
	cout << "mydeclval<A>()的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A>()) >().pretty_name() << endl;
	cout << "mydeclval<A>().myfunc()的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A>().myfunc()) >().pretty_name() << endl;
	cout << "sizeof(mydeclval<A>())=" << sizeof(_nmsp1::mydeclval<_nmsp1::A>()) << endl;

	cout << "decltype(mydeclval<A>())的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A>()) >().pretty_name() << endl;
	cout << "decltype(mydeclval<A&>())的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A&>()) >().pretty_name() << endl;
	cout << "decltype(mydeclval<A&&>())的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A&&>()) >().pretty_name() << endl;

	//调用引用限定符修饰的成员函数范例
	_nmsp1::ALR alr; //左值对象
	alr.onLvalue();
	//alr.onRvalue(); //编译错误，因为onRvalue只能被类A的右值对象调用
	_nmsp1::ALR().onRvalue(); //临时对象是右值对象
	//_nmsp1::ALR().onLvalue(); //编译错误，因为onLvalue只能被类A的左值对象调用
	*/

	/*
	//---------------------------------------------------------------------
	//mydeclval返回右值 引用时的测试代码
	decltype(_nmsp1::mydeclval<_nmsp1::ALR>().onAnyValue());
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onLvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onRvalue()); //返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onRvalue()没问题
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onRvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onLvalue()); //返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onLvalue()是错误的

	//---------------------------------------------------------------------
	//mydeclval返回左值 引用时的测试代码
	decltype(_nmsp1::mydeclval<_nmsp1::ALR>().onAnyValue());
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onLvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onRvalue()); //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onRvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onLvalue()); //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	*/

	//auto result = _nmsp2::TestFnRtnImpl(_nmsp2::myfunc, 5, 8);
	auto result = _nmsp2::TestFnRtnImpl<int(int, int)>(_nmsp2::myfunc, 5, 8);
	cout << result << endl;

	/*int (*fp_var)(int x, int y); //函数指针类型fp_var= int (*)(int,int)
	int (*&&yy_fp_var)(int x, int y) = std::move(fp_var); //函数指针的右值引用类型yy_fp_var=int (*&&)(int,int),现在yy_fp_var就代表fp_var了
	fp_var = _nmsp2::myfunc;
	cout << fp_var(1, 2) << endl; //3
	cout << yy_fp_var(1, 2) << endl; //3*/

	auto result2 = _nmsp2::TestFnRtnImpl2(_nmsp2::myfunc, 13, 15);
	cout << result2 << endl;

	return 0;
}