﻿#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

namespace _nmsp1 {

	template<typename T> //名字为T的模板参数，表示myvector这个容器所保存的元素类型
	class myvector {
	
	public:
		typedef  T* myiterator;    //迭代器

	public:
		myvector();               //构造函数
		myvector& operator=(const myvector&);   //赋值运算符重载,在类模板内部使用模板名myvector并不需要提供模板参数,当然提供也行,可以写成myvector<T>

	public:
		void myfunc(){
		
			cout << "myfunc()被调用" << endl;
		}
	public:
		//迭代器接口
		myiterator mybegin();     //迭代器起始位置
		myiterator myend();       //迭代器结束位置

	public:
		static void mystaticfunc(){
		
			cout << "mystaticfunc()被调用" << endl;
		}

	public:
		myvector(T tmpt){  //构造函数
		
		}
	};
	template<typename T>
	myvector<T>::myvector() {//类外构造函数的实现
	
	}
}

namespace _nmsp3 {
	template <typename T, typename U>
	struct TC {
		TC() {
			cout << "TC泛化版本构造函数" << endl;
		}
		void functest1(){
			cout << "functest1泛化版本" << endl;
		}
		static int m_stc; //声明一个静态成员变量
	};
	template<>  //普通成员函数的全特化需要以本行开始
	void TC<double, int>::functest1(){
		cout << "普通成员函数TC<double, int>::functest1的全特化" << endl;
	}
	template <typename T, typename U>
	int TC<T, U>::m_stc = 50;

	template<>  //静态成员变量的全特化需要以本行开始
	int TC<double, int>::m_stc = 100;

	//template<>
	//struct TC<double, int> //无法针对<double,int>类型对TC类模板进行全特化
	//{
	//	
	//};

	//--------------------------------------------------------------------
	template<>  //全特化所有类型模板参数都用具体类型代表，所以<>里就空了
	struct TC<int, int> {//上面的T绑定到这里的第一个int，上面的U绑定到这里的第二个int
		TC(){
			cout << "TC<int,int>特化版本构造函数" << endl;
		}
		void functest1();
		/*void functest1()
		{
			cout << "functest1特化版本" << endl;
		}*/

		void functest2();
		/*{
			cout << "functest2特化版本" << endl;
		}*/

	};
	//template<>   //注意不需要使用这行，否则会报语法错
	void TC<int, int>::functest1(){
		cout << "functest1特化版本" << endl;
	}
	void  TC<int, int>::functest2(){
		cout << "functest2特化版本" << endl;
	}

	//----------------------------------------模板参数数量上的偏特化版本
	template<typename U>
	struct TC<float, U>{
		TC(){
			cout << "TC<float,U>偏特化版本构造函数" << endl;
		}
		void functest1();
	};
	template<typename U>
	void TC<float, U>::functest1(){
		cout << "TC<float,U>::functest1偏特化版本" << endl;
	}

	//----------------------------------------模板参数范围上的偏特化版本
	template <typename T, typename U>
	struct TC<const T, U*>{
		TC(){
			cout << "const T, U*偏特化版本构造函数" << endl;
		}
		void functest1();
	};
	template <typename T, typename U>
	void TC<const T, U*>::functest1(){
		cout << "TC<const T, U*>::functest1偏特化版本" << endl;
	}
}
namespace _nmsp4{
	//template <typename T = char, typename U = int>
	//struct TC{
	//	TC(){
	//		cout << "TC泛化版本构造函数" << endl;
	//	}
	//	void functest1(){
	//		cout << "functest1泛化版本" << endl;
	//	}
	//	static int m_stc; //声明一个静态成员变量
	//};

	/*template <typename T = char>
	struct TC<T, int>{
	
	};*/
	//template <typename T, typename U = T*>
	//struct TC{
	//	//......
	//};

	/*
	//声明1
	template <typename T, typename U, typename V = int, typename W = char>
	struct TC;

	//声明2
	template <typename T, typename U = char, typename V, typename W> //前面的TC声明中的V,W有缺省参数，也就相当于这里的V，W有了缺省参数
	struct TC;

	//定义时就不要指定缺省参数了
	template <typename T, typename U, typename V, typename W>
	struct TC{
		//......
	};*/

	//template <typename T, typename U, size_t arrsize = 8>
	template <typename T, typename U, auto arrsize = 8>
	struct TC{
		T m_arr[arrsize];
		void functest2();
		//......
	};

	//template <typename T, typename U, size_t arrsize>
	template <typename T, typename U, auto arrsize>
	void TC<T, U, arrsize>::functest2(){
		cout << "functest2泛化版本" << endl;
	}

	//----------------------
	template <const char* p>
	struct TC2{
		TC2(){
			printf("TC2::TC2执行了，p = %s\n", p);
		}
	};
	//const char* g_s = "hello"; //全局指针
	const char g_s[] = "hello";
}
//成员函数模板
namespace _nmsp5
{
	template <typename T1>
	class A{
	public:
		template <typename T2>
		A(T2 v1, T2 v2); //构造函数也引入自己的模板参数T2，和整个类的类型模板参数T没有关系

		//template <typename T3>
		//void myft(T3 tmpt) //普通成员函数模板
		//{
		//	cout << tmpt << endl;
		//}

		template <typename T3, typename T4>
		void myft(T3 tmpt, T4 tmpt2) {//普通成员函数模板
			cout << "myft()泛化版本" << endl;
			cout << tmpt << endl;
			cout << tmpt2 << endl;
		}

		template <typename T4> 	//偏特化
		void myft(int tmpt, T4 tmpt2);
		/*{
			cout << "myft(int,T4)偏特化版本" << endl;
			cout << tmpt << endl;
			cout << tmpt2 << endl;
		}*/

		template <>   //全特化
		void myft(int tmpt, float tmpt2){
			cout << "myft(int,float)全特化版本" << endl;
			cout << tmpt << endl;
			cout << tmpt2 << endl;
		}


		T1 m_ic;
		static constexpr int m_stcvalue = 200;

	public:
		A(double v1, double v2){
			cout << "A::A(double,double)执行了!" << endl;
		}
		A(T1 v1, T1 v2){
			cout << "A::A(T1,T1)执行了!" << endl;
		}

		//拷贝构造函数模板
		template <typename U>
		A(const A<U>& other){
			cout << "A::A(const A<U>& other)拷贝构造函数模板执行了!" << endl;
		}
		//拷贝赋值运算符模板
		template <typename U>
		A<T1>& operator=(A<U>& other){
			cout << "operator=(A<U>& other)拷贝赋值运算符模板执行了!" << endl;
			return *this;
		}

		//拷贝赋值运算符
		A<T1>& operator=(A<T1>& other){
			cout << "operator=(A<T1>& other)拷贝赋值运算符执行了!" << endl;
			return *this;
		}
	};

	//在类外实现类模板的构造函数模板
	template <typename T1>   //先跟类模板的模板参数列表，要排在上面（如果排在下面会报错）
	template <typename T2>   //再跟构造函数模板自己的模板参数列表
	A<T1>::A(T2 v1, T2 v2){
		cout << "A::A(T2,T2)执行了!" << endl;
	}

	//在类外实现类模板的A的myft成员函数模板的偏特化版本
	template <typename T1>
	template <typename T4>
	void A<T1>::myft(int tmpt, T4 tmpt2){
		cout << "myft(int,T4)偏特化版本" << endl;
		cout << tmpt << endl;
		cout << tmpt2 << endl;
	}

	//在类外实现类模板的A的myft成员函数模板的全特化版本，无法编译通过
	/*template <typename T1>
	template <>
	void A<T1>::myft(int tmpt, float tmpt2){
		cout << "myft(int,float)全特化版本" << endl;
		cout << tmpt << endl;
		cout << tmpt2 << endl;
	}*/


	template <>
	class A<float>{
	public:
		template <typename T3, typename T4>
		void myft(T3 tmpt, T4 tmpt2) {//普通成员函数模板
			cout << "类A特化版本的myft()泛化版本" << endl;
			cout << tmpt << endl;
			cout << tmpt2 << endl;
		}
		//template <>   //全特化
		//void myft(int tmpt, float tmpt2);

	public:
		template <typename U>
		class OtherC{
		public:
			void myfOC();
			/*{
				cout << "myfOC执行了" << endl;
			}*/
		};

	};
	template <>
	void A<float>::myft(int tmpt, float tmpt2){
		cout << "类A特化版本的myft(int,float)全特化版本" << endl;
		cout << tmpt << endl;
		cout << tmpt2 << endl;
	}
	//将myfOC实现在类外面
	//template < >   不需要这行了，因为此时把 A<float> 当成一个正常的类看待
	template <typename U>
	void A<float>::OtherC<U>::myfOC(){
		cout << "myfOC执行了" << endl;
	}
}

namespace _nmsp6 {
	//变量模板
	//template<typename T>
	template<typename T = int>
	T g_myvar{}; //写成T g_myvar = 0;也不会出现语法错误

	template<>
	char g_myvar<double>{};

	template<typename T>
	T g_myvar<T*>{120};
	//初始值赋的是120
	//前面是T类型 （变量模板的类型）
	//后面是 T* 类型，代表的是正在特化的类型
	//要求 正在特化的类型必须依赖于变量模板的类型


	//----------------------------
	template <typename T>
	class C {  //类模板C
	public:
		static constexpr int m_stcvalue = 200;
		//....
	};
	template <typename U>
	int g_myvar2 = C<U>::m_stcvalue;


	template<typename T, int value>
	T g_myvar3[value];

	//----------------------------
	template<typename T>
	struct B {
		const static T value = { 160 };
	};
	template<typename T>
	int g_myvar4 = B<T>::value;    //注意g_myvar4是个变量模板

	//-----------------------------
	template <typename T>
	class D {
	public:
		template <typename W>
		static W m_tpi;  //静态成员变量模板声明
	};

	template <typename T>
	template <typename W>
	W D<T>::m_tpi = 5;

}

namespace _nmsp7
{
	template<typename T>
	using str_map_t = std::map<std::string, T>;

	template <typename T>
	class E {
		template<typename T>
		using str_map_t = std::map<std::string, T>;
	public:
		str_map_t<int> map1;
	};
}

namespace _nmsp8 {
	//template<typename T, typename Container = std::vector >
	template<
		typename T,      //类型模板参数
		//template<class> class Container = std::vector //这就是一个模板模板参数，写法比较固定。这里的名字叫Container，实际上叫U也可以，因为模板模板参数一般是做容器用，所以这里取名Container，std::vector是缺省值
		//template<typename W,W *point> typename Container
		template<typename W> typename Container = std::vector  //也要理解这种写法
	>

	class myclass {
	public:
		Container<T> myc;

	public:
		void func();
		myclass() {//构造函数
			for (int i = 0; i < 10; ++i) {
				myc.push_back(i); //这行代码是否正确取决于实例化该类模板时所提供的模板参数类型
			}
		}
	};
	//类外实现func成员函数	
	template<
		typename T,
		template<class> class  Container //本行写成template<typename > typename  Container也可以	
	>
	void myclass<T, Container>::func() {
		cout << "good!" << endl;
	}

}
namespace _nmsp9 {
	template<typename T, typename U>
	union myuni {
		T  carnum;  //轿车的编号，4个字节
		U cartype; //轿车的类型，比如 微型车、小型车、中型车、中大型车，1个字节够了
		U cname[60]; //轿车名，60字节
	};
}

int main() {

	/*********  类模板范例  *********/
	/*
	_nmsp1::myvector<int>  tmpvec;   //T被替换成了int
	tmpvec.myfunc(); 		           //调用类模板中一个普通的成员函数

	_nmsp1::myvector<string>::mystaticfunc();

	_nmsp1::myvector  tmpvec2(12);     //无需指定模板参数
	tmpvec2.myfunc();
	*/
	/*********  类模板特化  *********/
	/*
	_nmsp3::TC<int, float> mytc;  //TC泛化版本构造函数
	mytc.functest1();   //functest1 泛化版本

	_nmsp3::TC<int, int> mytc2;  //TC<int, int> 特化版本构造函数
	mytc2.functest1();   //functest1 特化版本
	mytc2.functest2();    //functest2 特化版本

	_nmsp3::TC<double, int> mytc3;    //TC泛化版本构造函数
	mytc3.functest1();     //普通成员函数TC<double, int>::functest1的全特化
	cout << "mytc3.m_stc = " << mytc3.m_stc << endl;

	_nmsp3::TC<float, int> mytc4;   //TC<float, int> 偏特化版本构造函数
	mytc4.functest1();     //TC<float, int>::functest1的偏特化版本

	_nmsp3::TC<const float, int*> mytc5;//const T, U*偏特化版本构造函数
	mytc5.functest1();   //TC<const T, U*>::functest1偏特化版本
	*/
	/*********  默认参数  *********/
	/*
	_nmsp4::TC<> mytc5;   //都使用默认参数
	_nmsp4::TC<double> mytc6;  // 第一个不用默认参数，第二个为默认参数

	//类型别名
	typedef _nmsp4::TC<int, float> IF_TC;
	IF_TC mytc10;  //等价于 TC<int, float> mytc10

	using IF_TCU = _nmsp4::TC<int, float>;
	IF_TCU mytc11; //等价于 TC<int, float> mytc11
	*/

	/*********  成员函数模板  *********/
	/*
	_nmsp5::A<float> a(1, 2); //实例化了一个A<float>这样一个类，并用int型来实例化构造函数
	a.myft(3); //3
	_nmsp5::A<float> a2(1.1, 2.2); //A<float>已经被上面代码行实例化过了，这里用double来实例化构造函数，因为1.1和2.2都是double类型
	_nmsp5::A<float> a3(11.1f, 12.2f); //这里用float来实例化构造函数，因为以f结尾的数字是float类型

	a3.m_ic = 16.2f;
	A<float> a4(a3);  //这里不会执行拷贝构造函数模板
	//类型不同的两个对象，用一个拷贝另一个时才会执行  拷贝构造函数模板
	A<int> a5(a3);  //拷贝构造函数模板执行  

	a3 = a4;   //不会执行 拷贝赋值运算符模板
	a3 = a5;  //会执行 拷贝赋值运算符模板

	_nmsp5::A<float> a2(1, 2);
	a2.myft(3.1, 2); // 类A泛化版本 的myft()泛化版本
	a2.myft(3, 2);    //类A泛化版本 的myft() 偏特化 版本
	a2.myft(3, 2.5f);  //类A泛化版本 的myft(int,float)全特化版本

	A<float> a3;
	a3.myft(3, 2.5f);  //类A特化版本 的myft(int,float)全特化版本
	a3.myft(3.1, 2);   //类A特化版本 的myft()泛化版本
	*/

	/*******  类模板的嵌套  *******/
	/*
	_nmsp5::A<float>::OtherC<float> myobjc;
	myobjc.myfOC();    //myfOC() 执行
	*/
	/*******  变量模板与成员变量模板  *******/
	//variable templates    c++14标准引入的
	/*
	_nmsp6::g_myvar<float> = 15.6f;
	_nmsp6::g_myvar<int> = 13;
	cout << _nmsp6::g_myvar<float> << endl;	  //15.6
	cout << _nmsp6::g_myvar<int> << endl;    //13

	char* p{};  //NULL  等价  char*  p = {};
	int q{};    //0     等价  int q = {}; 

	_nmsp6::g_myvar<double> = '2';// 当作一个char 来使用

	cout << _nmsp6::g_myvar<int*> << endl;  //120
	cout << _nmsp6::g_myvar<int> << endl;  //0

	_nmsp6::g_myvar<int> = 13;
	_nmsp6::g_myvar<> = 26;  
	//这里  g_myvar<> 与 g_myvar<int>  是同一个变量
	cout << _nmsp6::g_myvar<int> << endl;    //26
	cout << _nmsp6::g_myvar<> << endl;       //26

	cout << _nmsp6::g_myvar2<float> << endl; //200

	for (int i = 0; i < 15; ++i) {
		_nmsp6::g_myvar3<int, 15>[i] = i; 
		//g_myvar3<int, 15>的写法一出现就表示定义了int g_myvar3<int, 15>[15]这个大小为15个元素的int类型数组
	}

	cout << _nmsp6::g_myvar4<int> << endl; //160
	_nmsp6::g_myvar4<int> = 152;
	cout << _nmsp6::g_myvar4<int> << endl; //152
	cout << B<int>::value << endl; //160   B<int>::value 的值不发生变化

	cout << D<float>::m_tpi<int> << endl;   //5
	D<float>::m_tpi<int> = 150;
	cout << D<float>::m_tpi<int> << endl;  //150
	*/

	/*******  别名模板与成员别名模板  ******/
	/*
	_nmsp7::str_map_t<int> map1;
	map1.insert({ "first",1 });
	map1.insert({ "second",2 });

	_nmsp7::E<float> obja;
	obja.map1.insert({ "first",1 });
	obja.map1.insert({ "second",2 });
	*/
	/*******  模板模板参数  ******/
	//template template parameters
	_nmsp8::myclass<int, vector> myvecobj;  //int是容器中的元素类型，vector是容器类型
	_nmsp8::myclass<double, list> mylistobj;  //double是容器中的元素类型，list是容器类型

	_nmsp8::myclass<double, list> mylistobj2;  //double是容器中的元素类型，list是容器类型
	mylistobj2.func();

	/*******  共用体模板  ******/
	_nmsp9::myuni<int, char> myu;
	myu.carnum = 156;
	cout << myu.carnum << endl; //156


	return 0;
}