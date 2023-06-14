#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class MYACLS
{
public:
	int m_i;
	int m_j;
	int m_k;
};

void myfunc(int MYACLS::* mempoint, MYACLS& obj){
	obj.*mempoint = 260; //注意写法
}

int main() {

	MYACLS myobj;
	myobj.m_i = myobj.m_j = myobj.m_k = 0;
	printf("myobj.m_i = %p\n", &myobj.m_i); //用对象名.成员变量名，这里输出成员变量的内存地址

	MYACLS* pmyobj = new MYACLS();
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("pmyobj->m_j = %p\n", &pmyobj->m_j);

	int* p1 = &myobj.m_i; //对象成员变量指针
	int* p2 = &pmyobj->m_j;
	*p1 = 15;
	*p2 = 30;
	printf("p1地址 = %p,p1值=%d\n", p1, *p1);
	printf("p2地址 = %p,p2值=%d\n", p2, *p2);



	cout << "打印成员变量偏移值---------------" << endl;
	printf("MYACLS::m_i = %d\n", &MYACLS::m_i); //打偏移值用%d更容易看懂
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j);



	//成员变量指针	
	int MYACLS::* mypoint = &MYACLS::m_j;
	printf("MYACLS::m_j偏移值 = %d\n", mypoint);

	mypoint = &MYACLS::m_i;
	printf("MYACLS::m_i偏移值 = %d\n", mypoint);

	myobj.*mypoint = 22;   //注意写法
	pmyobj->*mypoint = 19; //注意写法

	myfunc(mypoint, myobj);  //注意调用方法
	myfunc(mypoint, *pmyobj); //注意调用方法
	cout << "sizeof(mypoint) = " << sizeof(mypoint) << endl;  //也是4字节

	int MYACLS::* mypoint2;
	mypoint2 = 0;
	mypoint2 = NULL;

	//mypoint2 += 1; //语法错误，普通指针可以，但成员变量指针不可以 
	//mypoint2++; //语法错误
	//mypoint2 = ( (&MYACLS::m_i) + 1);//语法错误


	printf("mypoint2 = %d\n", mypoint2);

	int MYACLS::* mypoint10 = &MYACLS::m_i;
	if (mypoint == mypoint10) {//本条件是成立的
		cout << "条件成立" << endl;
	}

	cout << "断点设置在这里" << endl;
	return 0;
}
