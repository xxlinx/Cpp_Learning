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

using namespace std;
//01里提到了可调用对象： 函数，  重载的 ( )  运算符的类对象

void myfunc(int tv) {
	cout << "myfunc()函数执行了,tv=" << tv << endl;
}
class TC {
public:
	void operator()(int tv) {
		cout << " TC::operator()执行了,tv=" << tv << endl;
	}
public:
	void ptfunc(int tv) {
		cout << "TC::ptfunc()执行了,tv=" << tv << endl;
	};
	int m_a;

public:
	static int stcfunc(int tv) {
		cout << "TC::stcfunc()静态函数执行了,tv=" << tv << endl;
		return tv;
	}
public:
	TC() { //构造函数
		m_a = 1;
	}
};
class TC2 {
public:
	using tfpoint = void(*)(int);
	static void mysfunc(int tv){ //静态成员函数
		cout << "TC2::mysfunc()静态成员函数执行了,tv=" << tv << endl;
	}
	operator tfpoint() { return mysfunc; } //类型转换运算符/类型转换函数
};

class CB {
	std::function<void()> fcallback;
public:
	CB(const std::function<void()>& f) :fcallback(f){
		int i;
		i = 1;
	}

	void runcallback(void){
		fcallback();
	}
};
class CT {
public:
	CT(){//构造函数
		cout << "CT::CT()执行" << endl;
	}
	CT(const CT&){//拷贝构造函数
		cout << "CT::CT(const CT&)执行" << endl;
	}
	~CT(){
		cout << "CT::~CT()执行" << endl;
	}
	void operator()(void){
		cout << "CT::opertor()执行" << endl;
	}
};
void mycallback(int cs, const std::function<void(int)>& f)
{
	f(cs);
}
void runfunc(int x)
{
	cout << x << endl;
}
void myfunc1(int x, int y, int z)
{
	cout << "x=" << x << ",y=" << y << ",z=" << z << endl;
}
void myfunc2(int& x, int& y)
{
	x++;
	y++;
}
class CQ{
public:
	CQ(){
		printf("CQ::CQ()构造函数执行，this=%p\n", this);
	}
	CQ(const CQ&){
		printf("CQ::CQ(const CQ&)拷贝构造函数执行，this=%p\n", this);
	}
	~CQ(){
		printf("CQ::~CQ()析构函数执行，this=%p\n", this);
	}
public:
	void myfunpt(int x, int y){
		cout << "x=" << x << ",y=" << y << endl;
		m_a = x;
	}
	int m_a = 0; //成员变量
};

int main() {

	//1.函数指针
	/*
	void(*pmf)(int) = myfunc;//定义函数指针并给初值，myfunc也可以写成&myfunc，是一样的效果
	pmf(15);//调用函数，这就是个可调用对象
	*/
	//2.operator()成员函数的类对象（仿函数/函数对象）
	/*
	TC tc;
	tc(20);//调用的是()操作符，这就是个可调用对象。等价于tc.operator()(20)
	*/
	//3.可被转换为函数指针的类对象
	/*
	TC2 tc2;
	tc2(50);//先调用tfpoint，再调用mysfunc；
	//等价于 tc2.operator TC2::tfpoint(50);
	*/
	//4.类成员函数指针
	/*
	TC tc3;
	void(TC:: * myfpointpt)(int) = &TC::ptfunc;//类成员函数指针变量myfpoint定义并被给初值
	(tc3.*myfpointpt)(68); // 要调用成员函数，就必须用到对象tc3
	*/

	//std::function 可调用对象包装器
	/*
	//1.绑定普通函数
	std::function<void(int)> f1 = myfunc;//绑定一个普通函数，注意<>中的格式
	f1(100);//调用普通函数
	//2.绑定类的静态成员函数
	std::function<void(int)> fs2 = TC::stcfunc;//绑定一个类的静态成员函数
	fs2(100);//调用静态成员函数
	//3.绑定仿函数
	TC tc3;
	function<void(int)> f3 = tc3;
	//提示使用了未初始化的局部变量“tc3”，因为类TC里有成员变量没被初始化，需要增加一个构造函数，
	//还应该初始化一下成员变量才好
	f3(100);//TC::operator()执行了, tv = 100
	TC2 tc4;
	std::function<void(int)> f4 = tc4;
	f4(150); //TC2::mysfunc()静态成员函数执行了, tv = 150
	//4.范例演示
	CT ct;
	CB cb(ct);
	cb.runcallback();

	for (int i = 0; i < 10; i++) {
		mycallback(i, runfunc);
	}
	*/

	//std::bind 绑定器
	auto bf1 = std::bind(myfunc1, 10, 20, 30);
	bf1();//执行myfunc1函数，结果：x=10,y=20,z=30
	auto bf2 = std::bind(myfunc1, placeholders::_1, placeholders::_2, 30);
	bf2(5, 15); //这里实际就等于指定myfunc1的第一个和第二个参数，结果：x=5,y=15,z=30
	//直接调用也可以
	std::bind(myfunc1, placeholders::_1, placeholders::_2, 30)(10, 20);
	//可以更换参数的位置
	auto bf3 = std::bind(myfunc1, placeholders::_2, placeholders::_1, 30);
	bf3(5, 15);//x = 15, y = 5, z =30

	int a = 2;
	int b = 3;
	auto bf4 = std::bind(myfunc2, a, placeholders::_1);
	bf4(b);  //a = 2  b =4
	//bind对于预先绑定的函数参数是通过值传递的，所以这个a实际上是值传递的。
	//bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的，所以这个b实际上是引用传递的

	CQ cq;
	auto bf5 = std::bind(&CQ::myfunpt, cq, placeholders::_1, placeholders::_2);
	//类函数有绝对地址，和对象无关，但要被调用必须有类对象参数
	bf5(10, 20);  //x = 10, y=20
	//第二个参数cq前可以加&，加了后不生成临时对象，
	//后续的myfunpt调用修改的是ct对象的m_a值。
	//这说明此时bind返回的这个对象其实就是cq对象（仿函数类型对象）

	//bind和function配合使用
	std::function<void(int, int)> bfc6 = std::bind(&CQ::myfunpt, cq, std::placeholders::_1, std::placeholders::_2);
	bfc6(10, 20);
	
	std::function<int& (void)> bf7 = std::bind(&CQ::m_a, &cq);
	bf7() = 60; //执行后cq对象的m_a成员变量值变为60了

	auto rt = std::bind(CT());
	rt();//调用operator();结果显示：CT::opertor()执行


	auto bf = std::bind(runfunc, placeholders::_1); //第一个参数由调用时的第一个参数指定
	for (int i = 0; i < 10; i++)
	{
		mycallback(i, bf); //bf是bind返回的结果，直接传递给了const std::function<void(int)>& f
	}



	return 0;
}