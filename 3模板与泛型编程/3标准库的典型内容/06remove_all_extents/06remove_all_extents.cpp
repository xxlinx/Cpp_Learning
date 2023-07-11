#include <iostream>
#include <vector>
#include <functional>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996)

//移除数组中得数组类型部分，保留元素类型

template<class T>
struct remove_all_extents {
	using type = T;
};

template<class T, std::size_t N>
struct remove_all_extents<T[N]> {
	using type = typename remove_all_extents<T>::type;  //这其实是一种元编程的编程手法
};

template<class T>
struct remove_all_extents<T[]> {    //表示无边界数组
	using type = typename remove_all_extents<T>::type;
};


int main() {

	float a[12];
	int b[5][8];
	int c[2][8][9];

	cout << typeid(std::remove_all_extents<decltype(a)>::type).name() << endl; //float
	cout << typeid(std::remove_all_extents<decltype(b)>::type).name() << endl;  //int
	cout << typeid(std::remove_all_extents<decltype(c)>::type).name() << endl; //int


	return 0;
}