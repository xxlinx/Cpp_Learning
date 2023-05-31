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
	int m_i;
	A() //构造函数
	{
	}
public:
	~A()
	{
	}
};

int main() {

	{
		A* pa = new A();
		A* pa2 = new A;
		delete pa;
	}
	{
		int* p1 = new int;
		int* p2 = new int();
		int* p3 = new int(100);
		cout << "断点调试" << endl;
	}
	{
		operator new(12);
	}
	return 0;
}