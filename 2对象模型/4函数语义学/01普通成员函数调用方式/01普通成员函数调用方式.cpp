#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class MYACLS
{
public:
	int m_i;
	void myfunc(int abc)
	{
		m_i += abc;
	}
};

//全局函数gmyfunc
void gmyfunc(MYACLS* ptmp, int abc)
{
	ptmp->m_i += abc;
}

int main() {

	MYACLS  myacls;
	myacls.myfunc(18);    //调用成员函数
	gmyfunc(&myacls, 18); //调用全局函数
	printf("MYACLS::myfunc地址=%p\n", &MYACLS::myfunc);

	return 0;
}