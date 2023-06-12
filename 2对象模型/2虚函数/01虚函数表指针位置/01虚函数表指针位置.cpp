#include <iostream>
#include <time.h>

using namespace std;

//虚函数指针位于对象内存的开头

class A
{
public:
	int i;   //一个成员变量，4字节
	virtual void testfunc() {}  //虚函数
};


int main() {

	A a;
	int ilen = sizeof(a);
	//cout << ilen << endl;  16

	return 0;
}