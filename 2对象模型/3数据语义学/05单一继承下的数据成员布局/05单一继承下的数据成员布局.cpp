#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

//父类成员是先出现的，然后才是子类成员（这里是讨论常规状态）
//class FAC  //父类
//{
//public:
//	int m_fai;
//	int m_faj;
//};
//class MYACLS : public FAC  //子类
//{
//public:
//	int m_i;
//	int m_j;
//};

//class Base
//{
//public:
//	int m_i1;
//	char m_c1;
//	char m_c2;
//	char m_c3;
//};

class Base1{

public:
	int m_i1;
	char m_c1;
};

class Base2 :public Base1{

public:
	char m_c2;
};

class Base3 :public Base2{

public:
	char m_c3;
};


int main(){
	/*{
		printf("MYACLS::m_i = %d\n", &FAC::m_fai);
		printf("MYACLS::m_i = %d\n", &FAC::m_faj);
		printf("MYACLS::m_i = %d\n", &MYACLS::m_fai);
		printf("MYACLS::m_i = %d\n", &MYACLS::m_faj);
		printf("MYACLS::m_i = %d\n", &MYACLS::m_i);
		printf("MYACLS::m_j = %d\n", &MYACLS::m_j);

	}

	{
		FAC facobj;
		MYACLS myaclobj;
	}*/

	/*{
		cout << sizeof(Base) << endl;

		printf("Base::m_i1 = %d\n", &Base::m_i1);
		printf("Base::m_c1 = %d\n", &Base::m_c1);
		printf("Base::m_c2 = %d\n", &Base::m_c2);
		printf("Base::m_c3 = %d\n", &Base::m_c3);

	}*/


	cout << sizeof(Base1) << endl; //8
	cout << sizeof(Base2) << endl; //12
	cout << sizeof(Base3) << endl; //16

	printf("Base3::m_i1 = %d\n", &Base3::m_i1);
	printf("Base3::m_c1 = %d\n", &Base3::m_c1);
	printf("Base3::m_c2 = %d\n", &Base3::m_c2);
	printf("Base3::m_c3 = %d\n", &Base3::m_c3);


	Base3 aaa;
	aaa.m_c2 = 5;
	return 0;
}