#include <iostream>
#include <vector>
#include <map>

using namespace std;

//using 定义模板别名
typedef unsigned int uint_t; 
//相当于给unsigned int类型起了个别名uint_t
typedef std::map<std::string, int> map_s_i;   
//现在，这么长的类型名，可以换成一个短类型，写起来方便多了
typedef std::map<std::string, std::string> map_s_s;

void test01() {
	map_s_i mymap;
	mymap.insert({ "first",1 }); //插入元素到容器，容器中每个元素都是一个键值对
	mymap.insert({ "second",2 }); //插入元素到容器

	map_s_s mymap2;
	mymap2.insert({ "first","firstone" });  //key是"first",value是"firstone"
}

//c++98时代的解决方案
template<typename wt>
struct map_s {
	typedef std::map<std::string, wt>  type; //定义了一个类型
};
void test02() {
	map_s<int>::type map1;   //等价于 std::map<std::string, int>  map1;
	map1.insert({ "first",1 });
}
//c++11的解决方法
template <typename T>
using str_map_t = std::map<std::string, T>;
void test03() {
	str_map_t<int> map1;
	map1.insert({ "first",1 });
}

//using 定义类型相关的模板
template <typename T>
using myfunc_M = int(*)(T, T);  //函数指针类型
int RealFunc(int i, int j)
{
	return 3;
}
void test04() {
	myfunc_M<int> pointFunc;   //类型模板
	pointFunc = RealFunc;  //函数地址赋给函数指针变量
	cout << pointFunc(2, 3) << endl;

}


//显式指定模板参数
template <typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i + j;
	return result;
}

template <typename T1, typename T2, typename T3>
T3 sum2(T1 i, T2 j)
{
	T3 result = i + j;
	return result;
}

void test05() {
	//auto result = sum<int>(2000000000, 2000000000);
	//cout << result << endl;  //计算结果是不对的

	//auto result = sum<double>(2000000000, 2000000000); 
	//dobule能保存下和值，但结果也不对，为什么
	//两个int 相加后(int相加就是错的)，保存到 double

	//auto result = sum<double, double, double>(2000000000, 2000000000); 
	//手动指定的优先
	//4e+09，指数形式显示，结果正确
	//auto result = sum<double, double >(2000000000, 2000000000);
	//没有问题
	

	//auto result = sum2(12, 13);
	auto result = sum2<double, double, double>(12, 13);//不可以省略

	

}

int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	test05();
	return 0;
}
