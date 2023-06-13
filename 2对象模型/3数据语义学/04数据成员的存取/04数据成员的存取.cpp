#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class FAC {
public:
	int m_fai;
	int m_faj;
};

//class MYACLS 
class MYACLS : public FAC
{
public:
	int m_i;
	static int m_si; //这是声明不是定义
	int m_j;

public:
	void myfunc()
	{
		m_i = 5;
		m_j = 6;
	}
};
int MYACLS::m_si = 0; //这才是定义


int main() {

	MYACLS myobj;
	MYACLS* pmyobj = new MYACLS();
	cout << MYACLS::m_si << endl;  //通过类名使用静态成员变量
	cout << myobj.m_si << endl;    //通过对象名使用静态成员变量
	cout << pmyobj->m_si << endl;  //对象指针

	MYACLS::m_si = 1;
	myobj.m_si = 2;
	pmyobj->m_si = 3;

	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("MYACLS::m_si = %p\n", &MYACLS::m_si);
	printf("MYACLS::m_si = %p\n", &myobj.m_si);
	printf("MYACLS::m_si = %p\n", &pmyobj->m_si);

	pmyobj->myfunc();

	printf("MYACLS::m_i = %d\n", &MYACLS::m_i); //0
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j); //4

	pmyobj->m_faj = 7;  //给父类的成员变量赋值

	return 0;
}