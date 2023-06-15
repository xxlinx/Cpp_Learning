#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class MYACLS{
public:
	int m_i;
	void myfunc(int abc){
		//m_i += abc;
		mystfunc(); //这绝对没有问题
	}
	virtual void myvirfunc(){
		printf("myvirfunc()被调用,this = %p\n", this);
		//myvirfunc2();
		MYACLS::myvirfunc2();
	}
	virtual void myvirfunc2(){
		printf("myvirfunc2()被调用,this = %p\n", this);
	}
	static void mystfunc(){
		printf("mystfunc()被调用\n");
	}

};

//全局函数gmyfunc
void gmyfunc(MYACLS* ptmp, int abc){
	ptmp->m_i += abc;
}

int main() {

	/*
	MYACLS  myacls;
	myacls.myvirfunc();
	MYACLS* pmyacls = new MYACLS;
	pmyacls->myvirfunc();
	delete pmyacls;
	*/

	MYACLS  myacls;
	myacls.mystfunc();
	MYACLS* pmyacls = new MYACLS;
	pmyacls->mystfunc();
	((MYACLS*)0)->mystfunc();  //这样调用静态成员函数没问题
	((MYACLS*)0)->myfunc(12);
	pmyacls->mystfunc();
	printf("MYACLS::mystfunc()地址 = %p\n", MYACLS::mystfunc);

	return 0;
}

