#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <atomic>
#include <windows.h>

using namespace std;

class A
{
public:
	static void* operator new(size_t size);		//应该为静态函数，但不写static似乎也行,估计是编译器内部有处理,因为new一个对象时还没对象呢，静态成员函数跟着类走，和对象无关
	static void operator delete(void* phead);

	static void* operator new[](size_t size);
	static void operator delete[](void* phead);

public:
	A()
	{
		cout << "类A的构造函数执行了" << endl;
	}
	~A()
	{
		cout << "类A的析构函数执行了" << endl;
	}
};
void* A::operator new(size_t size)
{
	cout << "A::operator new被调用了" << endl;
	A* ppoint = (A*)malloc(size);
	return ppoint;
}
void A::operator delete(void* phead)
{
	cout << "A::operator delete被调用了" << endl;
	free(phead);
}
void* A::operator new[](size_t size)
{
	cout << "A::operator new[]被调用了" << endl;
	A* ppoint = (A*)malloc(size);
	return ppoint;
}
void A::operator delete[](void* phead)
{
	cout << "A::operator delete[]被调用了" << endl;
	free(phead);
}

int main() {
	//调用自己重构的 new delete
	A* pa = new A();
	delete pa;

	//调用系统的 new delete
	A* pa2 = ::new A();
	::delete pa2;

	A* pa3 = new A[3]();
	delete[] pa3;

	return 0;
}



