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

class CT
{
public:
	int i;
	int j;
};
int testf()
{
	return 10;
}
const int&& myfunctest(void)
{
	return 0;
}

template <typename T>
class CTTMP
{
public:
	decltype (T().begin()) iter; //假如T的类型是 const std::vector<int>，那么const std::vector<int>()是临时对象，调用临时对象的 begin()，begin()这东西返回的是iterator还是const_iterator，取决于这个容器对象是否是const对象
	void getbegin(T& tmpc)
	{
		//....
		iter = tmpc.begin();
	}
};



int main() {

	//decltype含义
	/*
	const int i = 0;
	const int& iy = i;

	auto j1 = i;        //传值方式推断，引用属性，const属性等都会被抛弃 ,j1 = int;
	decltype(i) j2 = 15;  //j2 = const int ，如果decltype中是个变量，则变量的const属性会返回而不会被抛弃，这和auto不同
	decltype(iy) j3 = j2;  //j3 = const int &，如果decltype中是个变量，则变量的const属性会返回,引用属性也会被返回,现在j3绑定到j2
	//所以这里看到了，一般引用这种属性都会被舍弃，因为引用会被看做变量的别名，和变量是等同看待，但是decltype这里，引用属性会被保留。（看起来decltype比较循规蹈矩，有啥返回啥）

	using boost::typeindex::type_id_with_cvr;
	cout << "j3=" << type_id_with_cvr<decltype(j3)>().pretty_name() << endl;
	*/
	/*
	decltype(CT::i) a;  //a=int   ,decltype中是类访问表达式
	CT tmpct;
	decltype(tmpct) tmpct2; // tmpct2 = CT类类型
	decltype(tmpct2.i) mv = 5; //mv = int ,decltype中是类访问表达式
	int x = 1, y = 2;
	auto&& z = x;   //这是万能引用，而x是左值，则auto是int&,z也是int& 
	decltype(z) && h = y;     //int& &&h => h的类型应该是int & ，因为这是个引用折叠，折成左值了,最终形式就是：int &h = y;
	*/
	/*
	decltype(8) kkk = 5;//kkk = int
	int i = 0;
	int* pi = &i;
	int& iy = i;
	decltype(iy + 1) j;  //j=int ,因为iy+1就得到一个整型表达式了。
	decltype(pi)   k;    //k=int *   ,pi只是个变量
	*pi = 4;
	decltype(i)  k2;      //k2=int ,i只是个变量。

	decltype(*pi)  k3 = i;  //k3=int&  ,为什么是这个呢？ *p得到的是指针所指向的对象，而且能给这个对象赋值,所以*pi是个左值。	                       
	//大家要这样理解，首先*pi是个表达式不是个变量，因为它有*号，如果表达的结果能够作为赋值语句等号左边的值，
	//那decltype后返回的就是个引用。所以这种情况大家可以专门记一下。（decltype是非变量的表达式，且能作为等号左边的内容）


	using boost::typeindex::type_id_with_cvr;
	cout << "k3=" << type_id_with_cvr<decltype(k3)>().pretty_name() << endl;

	decltype((i)) iy3 = i;   //iy3 = int &， 而i本身是个变量，增加了个()变成了表达式，能做左值(变量能放在等号左边，就叫做能做左值)的表达式会得到引用类型
	using boost::typeindex::type_id_with_cvr;
	cout << "iy3=" << type_id_with_cvr<decltype(iy3)>().pretty_name() << endl;

	decltype(testf()) tmpv = 14;//tmpv的类型就是函数testf()的返回类型int
	decltype(testf) tmpv2; //tmpv2 = int(void)

	//function< decltype(testf)> ftmp  
	//ftmp 表示是一个可调用对象，该对象接收一个int参数，返回一个int类型
	function< decltype(testf)> ftmp = testf;//ftmp绑定到testf
	cout << ftmp() << endl;  //10

	decltype(testf)* tmpv3; //tmpv3 = int(*)(void)
	tmpv3 = testf;
	cout << tmpv3() << endl;  //10

	decltype(myfunctest()) myy = 0;  // myy = const int &&
	*/

	//decltype主要用途
	/*
	using conttype = const std::vector<int>;//定义类型别名
	conttype myarr = { 10, 20, 30 };//定义该类型变量，现在myarr是个容器了
	CTTMP<conttype> ct;
	ct.getbegin(myarr);
	*/
	//auto 与 decltype 结合


	return 0;
}