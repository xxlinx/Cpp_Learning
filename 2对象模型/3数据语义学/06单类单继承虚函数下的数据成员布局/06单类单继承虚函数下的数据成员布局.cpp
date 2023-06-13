#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class Base{
public:
	//virtual  void mybvirfunc() {}
	int m_bi;
};

class MYACLS :public Base{
public:
	int m_i;
	int m_j;

	virtual void myvirfunc(){
	}
	MYACLS() {//构造函数
		int abc = 1; //方便加断点
	}
	~MYACLS(){//析构函数
		int def = 0; //方便加断点
	}
};

int main() {
	/*
	MYACLS aaa;
	cout << sizeof(MYACLS) << endl;
	printf("MYACLS::m_i = %d\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j);
	*/

	//MYACLS myobj;
	//myobj.m_i = 3;
	//myobj.m_j = 6;
	//cout << "方便加断点" << endl;

	MYACLS myobj;
	myobj.m_i = 3;
	myobj.m_j = 6;
	myobj.m_bi = 9;
	cout << "方便加断点" << endl;

	return 0;
}
