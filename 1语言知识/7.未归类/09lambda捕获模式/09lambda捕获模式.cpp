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
#include <ctime>
using namespace std;


//全局量，每个元素都是个function,每个function给进去个int，返回个bool
std::vector<std::function<bool(int)>> gv; 
void myfunc()
{
	// 要包含<ctime>头
	srand((unsigned)time(NULL)); //根据当前时间设置个随机数种子，方便后面用rand产生随机数，否则每次程序运行随机数都一样
	int tmpvalue = rand() % 6; //0-5之间随机值	
	//gv.push_back( //塞一个可调用对象（lambda表达式）到gv容器中来
	//	[&](int tv) {

	//		//本lambda的生存依赖于tmpvalue的生命期，这是很麻烦的事
	//		if (tv % tmpvalue == 0) //如果tv是tmpvalue的倍数 
	//			return true;
	//		return false;
	//	}
	//);
	//gv.push_back(
	//	[&](auto tv) {   //c++14   形参列表可以用 auto
	//		if (tv % tmpvalue == 0) //如果tv是tmpvalue的倍数
	//			return true;
	//		return false;
	//	}
	//);
	gv.push_back(
		[=](auto tv) {
			if (tv % tmpvalue == 0) //如果tv是tmpvalue的倍数
				return true;
			return false;
		}
	);

}


class AT
{
public:
	//void addItem()
	//{
	//	gv.push_back(
	//		[=](auto tv) {  //捕获方式中有= 就等价于有this
	//			cout << m_tmpvalue << endl;
	//			if (tv % m_tmpvalue == 0)
	//				return true;
	//			return false;
	//		}
	//	);
	//}
	//void addItem()
	//{
	//	gv.push_back(
	//		[this](auto tv) {
	//			cout << m_tmpvalue << endl;  // m_tmpvalue相当于this->m_tmpvalue
	//			if (tv % m_tmpvalue == 0)  // m_tmpvalue相当于this->m_tmpvalue
	//				return true;
	//			return false;
	//		}
	//	);
	//}
	//void addItem()
	//{
	//	gv.push_back(
	//		[this](auto tv) {
	//			cout << m_tmpvalue << endl;  // m_tmpvalue相当于this->m_tmpvalue
	//			if (tv % m_tmpvalue == 0)  // m_tmpvalue相当于this->m_tmpvalue
	//				return true;
	//			return false;
	//		}
	//	);
	//}

	//void addItem()
	//{
	//	auto  tmpvalueCopy = m_tmpvalue;
	//	gv.push_back(
	//		[tmpvalueCopy](auto tv) {
	//			cout << tmpvalueCopy << endl;
	//			if (tv % tmpvalueCopy == 0)
	//				return true;
	//			return false;
	//		}
	//	);
	//}

	//广义的捕获
	void addItem()
	{
		gv.push_back(
			[tmpvalue = m_tmpvalue](auto tv) { //将m_tmpvalue复制到闭包里来
				cout << tmpvalue << endl;  //使用的是副本
				if (tv % tmpvalue == 0)
					return true;
				return false;
			}
		);
	}


	int m_tmpvalue = 7;
};

void myfunc2()
{
	// 要包含<ctime>头
	srand((unsigned)time(NULL)); //根据当前时间设置个随机数种子，方便后边用rand产生随机数，否则每次程序运行随机数都一样
	//static int tmpvalue = rand() % 6; //0-5之间随机值
	static int tmpvalue = 4;
	gv.push_back(
		[](auto tv) {
			cout << tmpvalue << endl;
			if (tv % tmpvalue == 0) //如果tv是tmpvalue的倍数
				return true;
			return false;
		}
	);
	tmpvalue++; //递增
}


int main() {

	//1.引用捕获方式会导致lamnda 包含绑定到局部变量的引用
	/*
	myfunc();
	// //使用这个的时候gv.push_back( [&](int tv) {...}
	cout << gv[0](10) << endl; //跟踪调试，这个调用导致问题，因为此时lambda里tmpvalue已被销毁，所以会产生未定义行为
	*/

	//2.成员变量的捕获
	/*
	AT* pat = new AT();
	pat->addItem();
	cout << gv[0](10) << endl;  //7，0   这里的正常执行依赖与pat对象 的存在
	delete pat;
	*/
	//3.静态局部变量
	myfunc2();
	gv[0](10); //5
	myfunc2();
	gv[0](10); //6
	gv[1](10); //6


	return 0;
}