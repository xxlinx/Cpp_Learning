#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <atomic>
#include <ctime>

using namespace std;

//重载全局的影响太大，不建议
//void* operator new(size_t size) //重载全局operator new
//{
//	return malloc(size);
//}
//void* operator new[](size_t size)//重载全局operator new[]
//{
//	return malloc(size);
//}
//
//void operator delete(void* phead)//重载全局operator delete
//{
//	free(phead);
//}
//void operator delete[](void* phead)//重载全局operator delete[]
//{
//	free(phead);
//}

//类的重构
//class A
//{
//public:
//	A() //构造函数
//	{
//		cout << "A::A()" << endl;
//	}
//	~A() //析构函数
//	{
//		cout << "A::~A()" << endl;
//	}
//
//	void* operator new(size_t size)
//	{
//		A* ppoint = (A*)malloc(size);
//		return ppoint;
//	}
//	void  operator delete(void* phead)
//	{
//		free(phead);
//	}
//	void* operator new[](size_t size)
//	{
//		A* ppoint = (A*)malloc(size);
//		return ppoint;
//	}
//	void operator delete[](void* phead)
//	{
//		free(phead);
//	}
//};


class PLA
{
public:
	int m_a;
	PLA() :m_a(0)   //构造函数
	{
		cout << "PLA::PLA()构造函数执行" << endl;
	}
	PLA(int tempvalue) :m_a(tempvalue) //构造函数
	{
		cout << "PLA::PLA(int tempvalue)构造函数执行" << endl;
	}
	~PLA() //析构函数
	{
		cout << "PLA::~PLA()析构函数执行" << endl;
	}

	////定位new操作符的重载，注意参数是比传统new多一个参数的
	//void* operator new(size_t size, void* phead)
	//{
	//	//这里增加一些自己的额外代码，用于统计之类的，但不要分配内存
	//	return phead;//收到内存开始地址也只返回内存开始地址即可
	//}

	void* operator new(size_t size, int tvp1, int tvp2)
	{
		return NULL;
	}
	void  operator delete(void* phead, int tvp1, int tvp2)
	{
		return;
	}
};


int main() {

	void* mymemPoint = (void*)new char[sizeof(PLA)]; //内存必须事先分配出来,为了内存分配通用性，这里返回void *类型
	//开始用这个返回的void*指针
	PLA* pmyAobj1 = new(mymemPoint) PLA();   //定位new：调用无参构造函数,这里并不额外分配内存

	void* mymemPoint2 = (void*)new char[sizeof(PLA)];
	PLA* pmyAobj2 = new(mymemPoint2) PLA(12); //定位new：调用带一个参数的构造函数,这里并不额外分配内存

	//释放
	pmyAobj1->~PLA(); //根据需要，有析构函数就可以调用析构函数
	pmyAobj2->~PLA();
	delete[](void*)pmyAobj1; //分配时用char[]，释放时用delete[]，本行等价于delete[](void*)mymemPoint;
	delete[](void*)pmyAobj2;//本行等价于delete[](void*)mymemPoint2;

	//PLA* pla = new(1234, 56) PLA();   //这其实并没有实际分配内存，也没有调用类的构造函数

	return 0;
}