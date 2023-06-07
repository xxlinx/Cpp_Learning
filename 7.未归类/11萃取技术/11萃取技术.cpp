#include <iostream>
#include <list>

using namespace std;

//type traits

template <typename T>
void printTraitsInfo(const T& t)  //打印萃取信息
{
	cout << "--------------begin-----------" << endl;

	cout << "我们要萃取的类型名字是：" << typeid(T).name() << endl;

	cout << "is_void = " << is_void<T>::value << endl;                                    //类型是否是void
	cout << "is_class = " << is_class<T>::value << endl;                                  //类型是否是一个class
	cout << "is_object = " << is_object<T>::value << endl;                                //类型是否是 一个对象类型
	cout << "is_pod = " << is_pod<T>::value << endl;                                      //是否是普通类（只包含成员变量，不包含成员函数）-POD(plain old data)
	cout << "is_default_constructible = " << is_default_constructible<T>::value << endl;  //是否有缺省构造函数
	cout << "is_copy_constructible = " << is_copy_constructible<T>::value << endl;        //是否有拷贝构造函数
	cout << "is_move_constructible = " << is_move_constructible<T>::value << endl;        //是否有移动构造函数
	cout << "is_destructible = " << is_destructible<T>::value << endl;                    //是否有析构函数
	cout << "is_polymorphic = " << is_polymorphic<T>::value << endl;                      //是否含有虚函数
	cout << "is_trivially_default_constructible = " << is_trivially_default_constructible<T>::value << endl;      //缺省拷贝构造函数是否是可有可无的（没有也行的）

	cout << "has_virtual_destructor = " << has_virtual_destructor<T>::value << endl;      //是否有虚析构函数

	cout << "--------------end-------------" << endl;

}

class A
{
public:
	A() = default;
	A(A&& ta) = delete;           //移动构造：你要不写delete，系统一般就会认为你有这个成员函数
	A(const A& ta) = delete;      //拷贝构造 
	virtual ~A() {}
};
class B
{
public:
	int m_i;
	int m_j;
};
class C
{
public:
	C(int t) {} //有自己的构造函数，编译器不会给你提供缺省构造函数
};




int main() {

	printTraitsInfo(int());     //扔一个临时对象进去
	printTraitsInfo(string());
	printTraitsInfo(A());
	printTraitsInfo(B());
	printTraitsInfo(C(1));
	printTraitsInfo(list<int>());

	return 0;
}