#include <iostream>
#include <vector>
#include <thread>

#include <windows.h>

using namespace std;

//C++语言只会为 const引用产生临时对象，所以第二个参数要加const
void myprint(int i, const string& pmybuf) //第一个参数不建议使用用引用以免出问题，第二个参数虽然使用了引用&string，但实际上还是发生了对象拷贝，这个跟系统内部工作机理有关
{
	cout << i << endl;     
	//cout << pmybuf << endl;
	const char* ptmp = pmybuf.c_str();
	cout << pmybuf.c_str() << endl;
	return;
}

//class A
//{
//public:
//	A(int a) :m_i(a) { cout << "A::A(int a)构造函数执行" << this << endl; }
//	A(const A& a) { cout << "A::A(const A)拷贝构造函数执行" << this << endl; }
//	~A() { cout << "~A::A()析构函数执行" << this << endl; }
//	int m_i;
//};

//临时对象构造时机
class A
{
public:
	A(int a) :m_i(a) {
		cout << "A::A(int a)构造函数执行，this = " << this << "，threadid = " << std::this_thread::get_id() << endl;
	}
	A(const A& a) {
		cout << "A::A(const A)拷贝构造函数执行，this = " << this << "，threadid = " << std::this_thread::get_id() << endl;
	}
	~A()
	{
		cout << "~A::A()析构函数执行，this = " << this << "，threadid = " << std::this_thread::get_id() << endl;
	}
public:
	void thread_work(int num) //带一个参数
	{
		cout << "子线程thread_work执行，this = " << this << ",threadid = " << std::this_thread::get_id() << endl;
	}

public:
	void operator()(int num)
	{
		cout << "子线程（）执行，this = " << this << "threadid = " << std::this_thread::get_id() << endl;
	}


	int m_i;
	//mutable  int m_i;
};

void myprint2(A& pmybuf) {
	cout << "子线程myprint2的参数pmybuf的地址是：" << &pmybuf << "，threadid = " << std::this_thread::get_id() << endl;

}



int main() {
	/*
	cout << "主线程id = " << std::this_thread::get_id() << endl;
	int mvar = 1;
	//std::thread mytobj(myprint2, mvar);
	std::thread mytobj(myprint2, A(mvar)); 
	//这两个构造的线程是不同的
	mytobj.join(); //用join方便观察
	cout << "main主函数执行结束!" << endl;
	*/

	A myobj(10);
	std::thread mytobj(&A::thread_work, myobj, 15);
	mytobj.join();
	cout << "main主函数执行结束!" << endl;



	return 0;
}