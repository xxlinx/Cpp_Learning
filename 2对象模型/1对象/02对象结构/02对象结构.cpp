#include <iostream>

using namespace std;
//class A{
//	int a = 100;
//};
//class A{
//	static int a;
//	static int b;
//};

//class A {
//	static void sfunc() {};
//	void myfunc() {};
//};

class A {
	virtual void myfunc3() {};
	virtual void myfunc4() {};
};

class myobject {
public:
	myobject() {}; //构造函数
	virtual ~myobject() {}; //析构函数

	float getvalue() const {//普通成员函数
		return m_value;
	}
	static int s_getcount() {//静态成员函数
		return ms_scount;
	}
	virtual void vfrandfunc() {}; //虚函数

protected:
	float m_value; //普通成员变量 
	static int ms_scount; //静态成员变量
};


int main() {
	//{
	//	A aobj;  //sizeof(aobj)=1,不管几个静态成员变量，sizeof的大小不增加
	//	std::cout << sizeof(aobj) << std::endl;
	//}

	//{
	//	A aobj;  //sizeof(aobj)=1
	//	std::cout << sizeof(aobj) << std::endl;
	//}
	//{
	//	int ilen2 = sizeof(char*); //8
	//	int ilen3 = sizeof(int*); //8
	//}
	{
		myobject obj;
		int ilen = sizeof(obj);
		cout << ilen << endl;
	}
	return 0;

}