#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <forward_list>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <queue>
#include <boost/type_index.hpp>
#include <functional>
#include <algorithm>

using namespace std;  

class CT
{
public:
	int m_i = 5;
	void myfuncpt(int x, int y)
	{

		//auto mylambda1 = [this] //无论是用this,还是用&、=都可以读取成员变量值
		//auto mylambda1 = [this,x,y]	//不能在lambda表达式中修改x,y值
		auto mylambda1 = [this, &x, &y]  //只可以使用和修改x值
			//auto mylambda1 = [this, &x, y]  //写成auto mylambda1 = [=,&x]也可以
			//auto mylambda1 = [&, &x]
			//auto mylambda1 = [&]
		{
			/*x;
			y;*/
			//y = 5;
			x = 8;
			y = 9;
			mf();
			return m_i; //有this，这个访问才合法,有&、=也可以
		};
		cout << mylambda1() << endl;
	}
	void mf() {}
};


int main()
{
	{
		//auto f = [](int a) -> int {
		auto f = [](int a) {
			return a + 1;
		};
		cout << f(1) << std::endl; //2
	}
	{
		auto f = [](int a = 8) -> int {
			return a + 1;
		};
		cout << f() << std::endl; //9
	}

	{
		auto f1 = []() {return 1; };
		auto f2 = [] {return 2; };
		cout << f1() << std::endl; //1
		cout << f2() << std::endl; //2
	}

	//{
	//	int i = 9;
	//	//static int i = 9;
	//	auto f1 = []
	//	{
	//		return i;  //报错（无法捕获外部变量），不认识这个i在哪里定义，看来lambda表达式毕竟是一个匿名函数，按常规理解方式不行
	//	};

	//}

	{
		int i = 9;
		auto f1 = [&]
		{
			i = 5; //因为&的存在，允许给i赋值，从而也就改变了i的值
			return i;
		};
		cout << f1() << endl; //5，调用了lambda表达式，所以i值发生改变
		cout << i << endl; //5，i值发生改变现在i=5
		cout << "设置断点" << endl;
	}
	{
		int i = 9;
		auto f1 = [=]
		{
			//i = 5; //这就非法了，不可以给它赋值，因为是以值方式捕获
			return i;   //使用该值（返回改值），这可以
		};
		cout << f1() << endl; //9，调用了lambda表达式
	}
	{
		CT ct;
		ct.myfuncpt(3, 4); //5
	}

	{
		int x = 5;
		//auto f = [=]
		auto f = [&]
		{
			return x;
		};
		x = 10;
		cout << f() << endl; //5，return的x是5而不是10
	}

	{
		int x = 5;
		auto f = [=]() mutable
		{
			x = 6; //没有mutable这个x是不允许修改的
			return x;
		};
		x = 10;
		cout << f() << endl; //6，return的x是6而不是10

	}
	{
		auto aa = []() {};
		auto bb = []() {};
		using boost::typeindex::type_id_with_cvr;
		cout << "aa=" << type_id_with_cvr<decltype(aa)>().pretty_name() << endl;
		cout << "bb=" << type_id_with_cvr<decltype(bb)>().pretty_name() << endl;
	}

	{
		std::function<int(int)> fc1 = [](int tv) {return tv; };
		cout << fc1(15) << endl; //15

		std::function<int(int)> fc2 = std::bind([](int tv) {return tv; }, 16); //bind第一个参数是函数指针，第二个参数开始就是真正的函数参数
		cout << fc2(15) << endl; //16，因为上面bind绑死了16，所以这里参数给啥都不起作用，除非bind中用placeholders::_1

	}
	{
		using functype = int (*)(int);//定义一个函数指针类型
		functype fp = [](int tv) {return tv;  };
		cout << fp(17) << endl; //17

	}
	{
		int a[5];
		a[0] = 1;//这就是语法糖
		*(a + 1) = 3; //*(a + 1)等价于a[1]，但谁也不会写成 *(a + 1)这种形式
		cout << "设置断点" << endl;
	}
	{
		vector<int> myvector = { 10,20,30,40,50 };
		int isum = 0;
		for_each(myvector.begin(), myvector.end(), [&isum](int val) {
			isum += val;
			cout << val << endl;
			});
		cout << "sum=" << isum << endl; //sum=150
	}
	{
		//vector<int> myvector = { 10,20,30,40,50 };
		//auto result = find_if(myvector.begin(), myvector.end(), [](int val) {		
		//	cout << val << endl;
		//	return false; //只要返回false，find_if就不停的遍历myvector，一直到返回true停止
		//	});
		vector<int> myvector = { 10,20,30,40,50 };
		auto result = find_if(myvector.begin(), myvector.end(), [](int val) {
			if (val > 15)
				return true; //返回true就停止遍历.
			return false;
			});
		if (result == myvector.end())
		{
			cout << "没找到" << endl;
		}
		else //条件成立
		{
			cout << "找到了，结果为:" << *result << endl; //找到了，结果为:20
		}

		cout << "设置断点" << endl;
	}
	return 0;
}
