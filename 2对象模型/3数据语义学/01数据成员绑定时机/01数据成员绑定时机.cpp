#include <iostream>
#include <time.h>

using namespace std;

//对成员函数myfunc的解析是整个类A定义完毕后才开始

/*
string myvar;
class A {
public:
	int myfunc() {

	}
private:
	int myvar;

};
*/

typedef string mytype;
class A {
	typedef int mytype;
public:
	void myfunc(mytype tmpvalue);
	//void myfunc(mytype tmpvalue) //这个mytype是string类型
	//{
	//	m_value = tmpvalue;
	//}

private:
	//typedef int mytype;
	mytype m_value;	//这个mytype是int类型	
};
void A::myfunc(mytype tmpvalue) //这个mytype又变成了int类型，但若在类中定义myfunc，那么参数中出现的mytype是string类型
{
	m_value = tmpvalue;
}

void myfunc(mytype tmpvalue)//这个mytype就是string类型
{
	string mvalue = tmpvalue;
}

int main() {



	return 0;
}