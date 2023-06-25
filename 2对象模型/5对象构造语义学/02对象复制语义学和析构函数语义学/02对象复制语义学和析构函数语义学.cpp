#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

class JI {
public:
	JI(){
		cout << "JI::JI()缺省构造函数执行了" << endl;
	}

public:
	virtual ~JI(){
		cout << "JI::~JI()析构函数执行了" << endl;
	}
};


//class A
class A :public JI{
public:
	int m_i, m_j;

	//private:
	//	A& operator=(const A& tmp);
	//	A(const A& tmptime);

	//public:
	//	A& operator=(const A& tmp) = delete;
	//	A(const A& tmptime) = delete;
public:
	A& operator=(const A& tmp){
		m_i = tmp.m_i;
		m_j = tmp.m_j;
		cout << "A::operator=(const A&)拷贝赋值运算符执行了" << endl;
		return *this;
	}
	A(const A& tmptime){
		m_i = tmptime.m_i;
		m_j = tmptime.m_j;
		cout << "A::A(const A&)拷贝构造函数执行了" << endl;
	}
	A(){
		cout << "A::A()缺省构造函数执行了" << endl;
	}
public:
	~A(){
		cout << "A::A()析构函数执行了" << endl;
	}
};

class ParC{
public:
	virtual ~ParC(){
		cout << "ParC::~ParC()虚析构函数执行了" << endl;
	}
};
class MemC{
public:
	ParC m_j;

public:
	~MemC(){
		cout << "MemC::~MemC()析构函数执行了" << endl;
	}
};

int main() {

	/********* 拷贝复制运算符与拷贝构造函数 **********/

	/********* 析构函数语义 **********/


	A aobj;

	return 0;
}