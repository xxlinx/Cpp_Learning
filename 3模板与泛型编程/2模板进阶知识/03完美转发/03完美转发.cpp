#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

//完美转发的概念
namespace _nmsp1 {
	//void funcLast(int v1, int v2)
	void funcLast(int v1, int& v2){
		++v2; //改变v2值，让其自增1
		cout << v1 + v2 << endl;
	}

	void funcLast2(int&& v1, int& v2){
		cout << v1 << endl;
		cout << v2 << endl;
	}

	//跳板函数 模板
	template <typename F, typename T1, typename T2>
	//void funcMiddle_Temp(F f, T1 t1, T2 t2) //f：函数指针类型void (*)(int,int)，而funcLast是函数类型void (int,int)
	/******    std::forward    *******/
	void funcMiddle_Temp(F f, T1&& t1, T2&& t2){
		//f(t1, t2);
		f(std::forward<T1>(t1), std::forward<T2>(t2));
	}
}


namespace _nmsp2 {
	void printInfo(int& t) {
		cout << "printInfo()参数类型为左值引用" << endl;
	}
	void printInfo(int&& t) {
		cout << "printInfo()参数类型为右值引用" << endl;
	}
	void printInfo(const int& t) {
		cout << "printInfo()参数类型为const左值引用" << endl;
	}

	template <typename T>
	void TestF(T&& t) {//万能引用
		printInfo(std::forward<T>(t));
	}
}

/******    普通函数的完美转发    *******/
namespace _nmsp3
{
	int getData()
	{
		return 3;
	}
	void funcLast3(int v1)
	{
		cout << "v1=" << v1 << endl;
	}

	void funcMiddle_Temp2()
	{
		auto&& result = getData();
		//getData返回的是右值，所以：auto = int,result = int&&（右值引用）
		
		//......对result做各种运算等等
		funcLast3(std::forward<decltype(result)>(result));
	}
}
/******    在构造函数模板中使用完美转发范例    *******/
namespace _nmsp4 {
	class Human {
	public:
		////构造函数
		//Human(const string& tmpname) :m_sname(tmpname)
		//{			
		//	cout << "Human(const string & tmpname)执行" << endl;
		//}

		////Human(string&& tmpname) :m_sname(tmpname)
		//Human(string&& tmpname) :m_sname(std::move(tmpname))
		//{
		//	cout << "Human(string && tmpname)执行" << endl;
		//}

		template<typename T>
		Human(T&& tmpname) :m_sname(std::forward<T>(tmpname)){
			cout << "Human(T&& tmpname)执行" << endl;
		}

		Human(const Human& th) : m_sname(th.m_sname){
			cout << "Human(Human const& th)拷贝构造函数执行" << endl;
		}
		Human(Human&& th) : m_sname(std::move(th.m_sname)){
			cout << "Human(Human const& th)移动构造函数执行" << endl;
		}

	private:
		string m_sname;  //姓名	

	};

}

/******    在可变参数模板中使用完美转发范例    *******/
namespace _nmsp5 {
	/*template <typename F, typename... T>
	void funcMiddle_Temp(F f, T&&... t)
	{
		f(std::forward<T>(t)...);
	}*/

	/*template <typename F, typename... T>
	auto funcMiddle_Temp(F f, T&&... t)->decltype(f(std::forward<T>(t)...))
	{
		return f(std::forward<T>(t)...);
	}*/

	template <typename F, typename... T>
	decltype(auto) funcMiddle_Temp(F f, T&&... t){
		return f(std::forward<T>(t)...);
	}


	//void funcLast(int v1, int& v2)
	//{
	//	++v2; //改变v2值，让其自增1
	//	cout << v1 + v2 << endl;
	//}
	int funcLast(int v1, int& v2){
		++v2;
		cout << v1 + v2 << endl;
		return v1 + v2;
	}

}
namespace _nmsp6 {
	template <typename F, typename... T>
	decltype(auto) funcMiddle_Temp(F f, T&&... t) {
		return f(std::forward<T>(t)...);
	}

	void funcLast4(char* p) {
		//if (p != NULL)
		if (p != nullptr)
			strncpy(p, "abc", 3);  //为保证这行编译通过，请在.cpp开头位置增加：#pragma warning(disable : 4996) 
	}
}
int main() {

	/*
	int i = 50;
	_nmsp1::funcLast(41, i); //正常显示结果92
	*/
	/*
	int j = 70;
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast, 20, j); //正常显示结果91，跟踪调试间接调用了funcLast，但并没修改这里j值，这是对的
	*/
	/*
	int i = 50;
	_nmsp1::funcLast(41, i); //正常显示结果92；执行完这句后i是51，这是对的

	int j = 70;
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast, 20, j); //正常显示结果91，但是执行完这句后，j不是71还是70，这是个问题
	
	_nmsp1::funcLast2(20, j);  //显示20、70，这是没问题的
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast2, 20, j);
	*/
	/*
	_nmsp2::TestF(1);  //1是右值
	int i = 5;
	_nmsp2::TestF(i);  //i是左值
	_nmsp2::TestF(std::move(i)); //move:将左值转成右值
	const int j = 8;
	_nmsp2::TestF(j);  //j是const左值
	_nmsp2::TestF(int(12)); //int(3)是临时对象所以是右值
	int&& tmpvalue = 16;
	_nmsp2::TestF(tmpvalue); //tmpvalue是左值
	*/
	/*
	_nmsp3::funcLast3(_nmsp3::getData());  //直接调用
	_nmsp3::funcMiddle_Temp2();   //函数内做完美转发
	*/

	/*
	string sname = "ZhangSan";
	_nmsp4::Human myhuman1(sname);
	_nmsp4::Human myhuman2(string("LiSi")); //"LiSi"是char const [5]类型，而string("LiSi")是string类型
	//_nmsp4::Human myhuman3(myhuman1);
	//为什么编译器这里报错呢？
	//myhuman1是左值，而且没有const修饰，编译器认为构造函数比拷贝构造更匹配，就出错了
	//如果去掉拷贝构造的 const 就不报错了

	_nmsp4::Human myhuman4(std::move(myhuman1));

	const _nmsp4::Human myhuman5(string("WangWu"));
	_nmsp4::Human myhuman6(myhuman5);    //用 myhuman5 来拷贝构造 myhuman6
	//如果去掉拷贝构造的 const 编译器认为构造函数比拷贝构造更匹配，就出错了

	//解决办法  std::enable_if
	*/

	/*
	int j = 70;
	_nmsp5::funcMiddle_Temp(_nmsp5::funcLast, 20, j);
	cout << "j = " << j << endl;
	*/
	/*
	int j = 70;
	int k = _nmsp5::funcMiddle_Temp(_nmsp5::funcLast, 20, j);
	cout << "j = " << j << endl;
	cout << "k = " << k << endl;
	*/

	//完美转发失败的情况 之一
	char* p = new char[100];
	memset(p, 0, 100);
	//_nmsp6::funcMiddle_Temp(_nmsp6::funcLast4, p);
	//_nmsp6::funcMiddle_Temp(_nmsp6::funcLast4, NULL);   // NULL不行 ，但 nullptr 行

	_nmsp6::funcMiddle_Temp(_nmsp6::funcLast4, nullptr);

	delete[]p;


	return 0;
}