﻿#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>

using namespace std;
/******  可变参函数模板  *****/
namespace _nmsp1 {

	//template <typename... T>
	//void myvtfunct(T... args) { //T : 一包类型，  args: 一包形参
	//	cout << "---------begin------------" << endl;
	//	cout << sizeof...(args) << endl; //收到的参数数量
	//	cout << sizeof...(T) << endl;    //收到的类型数量
	//	cout << "---------end------------" << endl;
	//}
	
	//void myvtfunct()//这是个普通函数，而不是函数模板
	//{
	//	cout << "参数包展开时执行了递归终止函数myvtfunct()" << endl;
	//}

	template <typename T, typename...U>
	void myvtfunct(T firstarg, U ...otherargs)
	{
		cout << "收到的参数值为:" << firstarg << endl;
		//myvtfunct(otherargs...); //递归调用，注意塞进来的是一包形参，这里...不能省略		
		if constexpr (sizeof...(otherargs) > 0) {//constexpr必须有否则无法成功编译，圆括号中是常量表达式
			myvtfunct(otherargs...); //递归调用，塞进来的是一包形参，这里...不能省略
		}
		else {

		}
	}

}
/******  折叠表达式  *****/
namespace _nmsp2 {
	template<typename... T>
	void myfunc(T... arg) {
		cout << "myfunc(T... arg)执行了!" << endl;
	}

	template<typename... T>
	void myfunc(T*... args) {
		cout << "myfunc(T*... args)执行了!" << endl;
	}

	void myfunc(int arg) {
		cout << "myfunc(int arg)执行了!" << endl;
	}
}

namespace _nmsp3 {
	template<typename... T>
	auto add_val(T ... args) {
		//return (... + args);
		return (args + ...);
	}

	template<typename... T>
	auto sub_val_left(T... args) {
		return (... - args); //形式1
	}
	template<typename... T>
	auto sub_val_right(T... args) {
		return (args - ...);  //形式2
	}

	template<typename... T>
	auto sub_val_left_b(T ... args) {
		return (220 - ... - args);
	}

	template<typename... T>
	void print_val_left_b(T ... args){
		(cout << ... << args);
	}

	template<typename... T>
	auto sub_val_right_b(T ... args){
		return (args - ... - 220);
	}

}
/******  可变参表达式  *****/
namespace _nmsp4 {
	template<typename... T>
	auto print_result(T const& ... args) {
		(cout << ... << args) << " 结束" << endl;
		return (... + args); //计算一下参数的和值
	}

	template<typename... T>
	void print_calc(T const& ... args) {
		//print_result(2 * args...);
		//print_result((args * 2) ...); //成功
		//print_result(args * 2 ...); //成功，数字和...之间要用空格分隔
		//print_result(args... * 2);
		print_result(args + args...);
	}
}
/******  可变参类模板  *****/
namespace _nmsp5 {
	//主模板定义（泛化版本的类模板）
	template<typename ...Args>
	class myclasst{
	public:
		myclasst() {
			printf("myclasst::myclasst()泛化版本执行了,this = %p\n", this);
		}
	};

	template<> class myclasst<> { //一个特殊的特化版本
	public:
		myclasst() {
			printf("myclasst<>::myclasst()特殊的特化版本执行了,this = %p\n", this);
		}
	};

	template<typename First, typename... Others>
	class myclasst<First, Others...> : private myclasst<Others...> {//偏特化
	public:
		myclasst() :m_i(0) {
			printf("myclasst::myclasst()偏特化版本执行了,this = %p,sizeof...(Others)=%d\n", this, sizeof...(Others));
		}

		//注意这第二个参数，这一包东西的写法
		myclasst(First parf, Others... paro) :m_i(parf), myclasst<Others...>(paro...)
		{
			cout << "-----------------begin------------------" << endl;
			printf("myclasst::myclasst(parf,...paro)执行了,this = %p\n", this);
			cout << "m_i = " << m_i << endl;
			cout << "-----------------end------------------" << endl;
		}
		First m_i;
	};

	//几种错的写法  ... 在什么位置要关注
	/*template<typename ...Args1, typename ... Args2 >
	class myclasst_2
	{
	};*/
	/*template<typename ...Args, typename U>
	class myclasst_3
	{
	};*/
}
namespace _nmsp6 {
	//主模板定义（泛化版本的类模板）
	template<int... FTArgs> //int替换为auto也没问题
	class myclasst2 {
	public:
		myclasst2() {
			printf("myclasst2::myclasst2()泛化版本执行了,this = %p\n", this);
		}
	};

	template<int First, int... Others> //两个int都替换为auto也没问题
	class myclasst2<First, Others...> : private myclasst2<Others...> {//偏特化
	
	public:
		myclasst2(){
			printf("myclasst2::myclasst2()偏特化版本执行了,this = %p,sizeof...(Others)=%d,First=%d\n", this, sizeof...(Others), First);
		}
	};
}
namespace _nmsp7 {
	template<typename T,
		template<typename> typename... Container> //泛化
	class ParentMM {
	public:
		ParentMM() {
			printf("ParentMM::ParentMM()泛化版本执行了,this = %p\n", this);
		}
	};

	template<
		typename T,
		template<typename> typename FirstContainer, template<typename> typename... OtherContainers
	>
	class ParentMM<T, FirstContainer, OtherContainers...> : private ParentMM<T, OtherContainers...> //偏特化
	{
	public:
		ParentMM() {
			printf("ParentMM::ParentMM()偏特化版本执行了,this = %p,sizeof...(OtherContainers)=%d\n", this, sizeof...(OtherContainers));
			m_container.push_back(12);
		}
		FirstContainer<T> m_container;
	};

	template<
		typename T,
		template<typename> typename... Container
	>
	class myclasst3 :private ParentMM<T, Container...>{
	public:
		myclasst3(){
			printf("myclasst3::myclasst3()执行了,this = %p,T的类型是:%s,Container参数个数是%d个\n", this, typeid(T).name(), sizeof...(Container));
		}
	};
}
namespace _nmsp8 {
	//主模板定义（泛化版本的类模板）
	template<typename ...Args>
	class myclasst {
	public:
		myclasst() {
			printf("myclasst::myclasst()泛化版本执行了,this = %p\n", this);
		}
	};

	template<typename First, typename... Others>
	class myclasst<First, Others...> //: private myclasst<Others...> //偏特化
	{
	public:
		myclasst() :m_i(0){
			printf("myclasst::myclasst()偏特化版本执行了,this = %p,sizeof...(Others)=%d\n", this, sizeof...(Others));
		}
		//注意这第二个参数，这一包东西的写法
		myclasst(First parf, Others... paro) :m_i(parf), m_o(paro...){//, myclasst<Others...>(paro...)
			cout << "-----------------begin------------------" << endl;
			printf("myclasst::myclasst(parf,...paro)执行了,this = %p\n", this);
			cout << "m_i = " << m_i << endl;
			cout << "-----------------end------------------" << endl;
		}
		First m_i;
		myclasst<Others...> m_o;
	};
}
namespace _nmsp9 {
	//类模板的泛化版本
	template <int mycount, int mymaxcount, typename ...T> //mycount用于统计，从0开始，mymaxcount表示参数数量，可以用sizeof...取得
	class myclasst4 {
	public:
		//下面的静态函数，借助tuple（类型），借助get（函数），就能够把每个参数提取出来
		static void mysfunc(const tuple<T...>& t) {//静态函数。注意，这个实现套路中参数是tuple
			cout << "value = " << get<mycount>(t) << endl; //可以把每个参数取出来并输出
			myclasst4<mycount + 1, mymaxcount, T...>::mysfunc(t); //计数每次+1，这里是递归调用，调用自己
		}
	};

	//偏特化版本,用于结束递归调用
	template <int mymaxcount, typename ...T>
	class myclasst4<mymaxcount, mymaxcount, T...> {//注意<>中前两个都是mymaxcount
	public:
		static void mysfunc(const tuple<T...>& t) {
			//这里其实不用干啥，因为计数为0,1,2是用泛化版本中的mysfunc处理，到这里时是3，不用做什么处理了
		}
	};

	template <typename...T>
	void myfunctuple(const tuple<T...>& t) {//可变参函数模板
		myclasst4<0, sizeof...(T), T...>::mysfunc(t); //注意第一个参数是0，表示计数从0开始
	}

}
namespace _nmsp10 {
	template<typename... myclasstPList>
	class myclasst5 : public myclasstPList...{
	public:
		myclasst5() : myclasstPList()...{
			cout << "myclasst5::myclasst5,this = " << this << endl;
		}
	};

	class PA1{
	public:
		PA1(){
			cout << "PA1::PA1,this = " << this << endl;
		}
	private:
		char m_s1[100];
	};
	class PA2 {
	public:
		PA2() {
			cout << "PA2::PA2,this = " << this << endl;
		}
	private:
		char m_s1[200];
	};
	class PA3{
	public:
		PA3(){
			cout << "PA3::PA3,this = " << this << endl;
		}
	private:
		char m_s1[300];
	};

}
namespace _nmsp11 {
	template<typename ...Args>//泛化版本
	class myclasst{
	public:
		myclasst(){
			printf("myclasst泛化版本执行了,this = %p,sizeof...(Args)=%d\n", this, sizeof...(Args));
		}
	};

	template<typename First, typename... Others>
	class myclasst<First, Others...>//特化版本，因为myclasst后面跟了尖括号，注意识别，另外...代表的参数包，必须放在整个参数的最后，比如<Others...，First>是错误的
	{
	public:
		myclasst(){
			printf("myclasst<First, Others...>偏特化版本执行了,this = %p,sizeof...(Others)=%d\n", this, sizeof...(Others));
		}
	};

	template<typename Arg>
	class myclasst<Arg> {
	public:
		myclasst() {
			printf("myclasst<Arg>偏特化版本执行了,this = %p\n", this);
		}
	};

	template<typename Arg1, typename Arg2>
	class myclasst<Arg1, Arg2>{
	public:
		myclasst(){
			printf("myclasst<Arg1,Arg2>偏特化版本执行了,this = %p\n", this);
		}
	};
}


int main() {
	/*
	_nmsp1::myvtfunct();
	_nmsp1::myvtfunct(10, 20);
	_nmsp1::myvtfunct(10, 25.8, "abc", 68);
	_nmsp1::myvtfunct<double, double>(10, 25.8, "abc", 68, 73); //指定部分类型，让编译器推导另一部分类型是允许的

	_nmsp1::myvtfunct(10, "abc", 12.7);
	*/

	/*
	_nmsp2::myfunc(NULL);   //myfunc(int arg)执行了!
	_nmsp2::myfunc(nullptr);    //myfunc(T... arg)执行了!
	_nmsp2::myfunc((int*)nullptr);     //myfunc(T*... args)执行了!
	*/

	/*
	cout<<_nmsp3::add_val(10, 20, 30) << endl;  //60
	cout << _nmsp3::sub_val_left(10, 20, 30, 40) << endl;  //-80   (((10-20)-30)-40)
	cout << _nmsp3::sub_val_right(10, 20, 30, 40) << endl;  //-20   10-(20-(30-40))

	cout << _nmsp3::sub_val_left_b(10, 20, 30, 40) << endl; //120  (((220-10)-20)-30)-40
	_nmsp3::print_val_left_b(10, "abc", 30, "def"); //10abc30def

	cout << _nmsp3::sub_val_right_b(10, 20, 30, 40) << endl; //200  10-(20-(30-(40-220))) = 200 
	*/

	/*
	cout << _nmsp4::print_result(10, 20, 30, 40) << endl;
	_nmsp4::print_calc(10, 20, 30, 40);    //20406080 结束
	*/

	/*
	_nmsp5::myclasst<int, float, double> myc;
	_nmsp5::myclasst<int, float, double> myc_2(12, 13.5, 23);

	_nmsp6::myclasst2<12, 18, 23> myc2;

	_nmsp7::myclasst3<int, vector, list, deque> myc3;

	_nmsp8::myclasst<int, float, double> myc(12, 13.5, 23);
	*/

	/*tuple<float, int, int> mytuple(12.5f, 100, 52);//一个tuple（元组）：一堆各种类型数据的组合
	//元组可以打印，用标准库中的get（函数模板）
	//cout << get<0>(mytuple) << endl;	//12.5
	//cout << get<1>(mytuple) << endl;	//100
	//cout << get<2>(mytuple) << endl;	//52
	_nmsp9::myfunctuple(mytuple); //成功调用myfunctuple*/

	/*_nmsp10::myclasst5<_nmsp10::PA1, _nmsp10::PA2, _nmsp10::PA3> obj;
	cout << "sizeof(obj)=" << sizeof(obj) << endl; //600
	*/

	_nmsp11::myclasst<int> myc1;    //myclasst<Arg>偏特化版本执行了,this = 0000003BFF0FF764
	_nmsp11::myclasst<int, float> myc2;    //myclasst<Arg1,Arg2>偏特化版本执行了,this = 0000003BFF0FF784
	_nmsp11::myclasst<int, float, double> myc3;    //myclasst<First, Others...>偏特化版本执行了,this = 0000003BFF0FF7A4,sizeof...(Others)=2
	_nmsp11::myclasst<int, float, double, char> myc4;    //myclasst<First, Others...>偏特化版本执行了,this = 0000003BFF0FF7C4,sizeof...(Others)=3
	_nmsp11::myclasst<> myc5;   //myclasst泛化版本执行了,this = 0000003BFF0FF7E4,sizeof...(Args)=0




	return 0;
}