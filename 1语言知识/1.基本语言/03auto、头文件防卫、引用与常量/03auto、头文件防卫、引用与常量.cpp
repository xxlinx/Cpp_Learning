#include <iostream>

#include "head1.h"
#include "head2.h"

using namespace std;   //后面再使用诸如std::cout时就可以简写成cout了；

void func(int &ta, int &tb) {  //注意形参是引用类型
	ta = 4;
	tb = 5;//改这个值直接影响到main()中传入的；

}

int func1() {
	return 5;
}

constexpr int func2(int abc) {
	abc = 16;
	int a3 = 5;
	return abc * a3;
}
int main() {
	//局部变量和初始化
	{
		int abc{ 5 };
	}
	{
		for (int i{ 0 }; i < 100; i++) { //可以这样来给i初值
		}
	}
	{
		int abc = { 5 };
		for (int i = { 0 }; i < 100; i++) {}
	}
	{
		int a[]{ 11,12,34 };
		int b[] = { 11,12,34 };
		cout << a[0] <<" "<< a[2] << endl;
	}
	{
		int abc = 3.5f;  //被系统截断  abc = 3
		//int def{ 3.5f }; //无法编译通过		
	}
	{
		int abc(12);   //通过()初始化
		cout << "掐断点观察" << endl;
	}

	//变量的自动类型推断
	{
		auto bvalue = true;  //bool
		auto ch = 'a';  //char
		auto dv = 1.2;  //double
		auto iv = 5; //int 
	}

	{
		cout << g_globalh1 << endl; //8
		cout << g_globalh2 << endl; //5
	}

	//引用
	{
		int value = 10;
		int& refval = value; //value的别名是refval， &在此不是取地址运算，而是起标识作用
		refval = 13; //就等价于value=13;	
		cout << value << endl;
		cout << refval << endl;

		//int& refval2;   //错误：定义引用类型时必须初始化
		//int& refval3 = 10; //引用必须绑定到变量或对象上，不能绑到常量上
		int bvalue = 89;
		//float& refbvalue = bvalue; //错误，类型要相同
	}
	{
		int a = 3;
		int& b = a;        //引用，注意&符号在=的左边侧
		int* p = &a;       //取地址符 ，注意&符号在=的右侧
	}
	{
		//引用作为函数形参
		int a = 13;
		int b = 14;
		func(a, b);
		cout << a << "    " << b << std::endl;   //4     5
	}

	//常量
	//const
	{
		const int var = 17; //一种承诺，表示这个变量的值不会发生改变（命名常量）
		//var = 18;  //修改其值，导致编译的时候就会报错，编译器会检查这个const承诺
		int& var2 = (int&)var;
		var2 = 5;  //改它的值，在监视窗口里面 会发现var值的确变成了5
		//在编译器里，看到两个占用着同一块内存
		cout << var << endl;   //17
		cout << var2 << endl;  //5，这也从侧面论证引用实际上不是别名这么简单
	}
	{
		int v1 = 12;
		const int v2 = v1 + func1(); //运行的时候求值也是可以的		
	}
	//constexpr c++11引入的  
	{
		constexpr int var1 = 1;
		constexpr int var2 = 11 * func2(12);
	}
	{
		int k = 3;
		//constexpr int var = 11 * func2(k); //不可以用变量k做参数
		int k2 = func2(k); //用变量k调用constexpr函数不会有问题。此时该函数相当于普通函数，结果当然也是在执行期间产生。
	}


	{
		constexpr int var = 3;
		cout << var << endl;
		int& var2 = (int&)var;
		var2 = 5; //这个值也能修改断点调试看是修改了。
		cout << var2 << endl; //5
		cout << var << endl; //3 
		//cout << "掐断点观察" << endl;
		if (var == var2)
		{
			cout << "掐断点观察" << endl;
		}
	}

	return 0;
}

