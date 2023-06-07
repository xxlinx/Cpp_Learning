#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <atomic>
#include <ctime>

using namespace std;   

#define DECLARE_POOL_ALLOC()\
public:\
	static void *operator new(size_t size)\
	{\
		return myalloc.allocate(size);\
	}\
	static void operator delete(void *phead)\
	{\
		return myalloc.deallocate(phead);\
	}\
	static myallocator myalloc;


#define IMPLEMENT_POOL_ALLOC(classname)\
myallocator classname::myalloc;

//专门的内存池类
class myallocator   //必须保证使用本类的类 sizeof()不少于4字节,否则崩溃报错
{
public:
	//分配内存接口
	void* allocate(size_t size)
	{
		obj* tmplink;
		if (m_FreePosi == nullptr)
		{
			//为空，我要申请内存，要申请一大块内存
			size_t realsize = m_sTrunkCout * size; //申请m_sTrunkCout这么多倍的内存
			m_FreePosi = (obj*)malloc(realsize);
			tmplink = m_FreePosi;

			//把分配出来的这一大块内存（5小块），彼此用链起来，供后续使用
			for (int i = 0; i < m_sTrunkCout - 1; ++i) //0--3
			{
				tmplink->next = (obj*)((char*)tmplink + size);
				tmplink = tmplink->next;
			} //end for
			tmplink->next = nullptr;
		} //end if
		tmplink = m_FreePosi;
		m_FreePosi = m_FreePosi->next;
		return tmplink;
	}
	//释放内存接口
	void deallocate(void* phead)
	{
		((obj*)phead)->next = m_FreePosi;
		m_FreePosi = (obj*)phead;
	}
private:
	//写在类内的结构，这样只让其在类内使用
	struct obj
	{
		struct obj* next; //这个next就是个嵌入式指针
	};
	int m_sTrunkCout = 5;//一次分配5倍的该类内存作为内存池子的大小
	obj* m_FreePosi = nullptr;
};
//
//class A
//{
//public:
//	//必须保证sizeof(A)凑够4个字节的,这里两个int成员8字节了，所以使用类myallocator毫无问题
//	int m_i;
//	int m_j;
//public:
//	static myallocator myalloc; //静态成员变量，跟着类A走
//	static void* operator new(size_t size)
//	{
//		return myalloc.allocate(size);
//	}
//	static void operator delete(void* phead)
//	{
//		return myalloc.deallocate(phead);
//	}
//};
//myallocator A::myalloc; //在类A之外定义一下这个静态成员变量
class A
{
public:
	A()
	{
		cout << "类A的构造函数执行了" << endl;
	}
	~A()
	{
		cout << "类A的析构函数执行了" << endl;
	}
	DECLARE_POOL_ALLOC();

public:
	//必须保证sizeof(A)凑够4个字节的,这里两个int成员8字节了，所以使用类myallocator毫无问题
	int m_i;
	int m_j;
};
IMPLEMENT_POOL_ALLOC(A)

class TestEP
{
public:
	int m_i;
	int m_j;
public:
	struct obj
	{
		struct obj* next; //next就是个嵌入式指针
	};
};


int main()
{
	/*
	TestEP mytest;
	cout << sizeof(mytest) << endl; //8
	TestEP::obj* ptmp;              //定义一个指针
	ptmp = (TestEP::obj*) & mytest; //把对象mytest的首地址给了这个指针，这个指针指向对象mytest首地址
	ptmp->next = nullptr;           //前四个字节给成了00 00 00 00
	*/

	cout << sizeof(myallocator) << endl;
	A* mypa[100];
	for (int i = 0; i < 15; ++i)
	{
		mypa[i] = new A();
		printf("%p\n", mypa[i]);
	}
	for (int i = 0; i < 15; ++i)
	{
		delete mypa[i];
	}


	return 0;
}
