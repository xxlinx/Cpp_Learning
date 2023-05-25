#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>

using namespace std;

//自己创建的线程也是从一个函数开始运行
/*
void myprint()
{
	cout << "我的线程开始执行了" << endl;
	//...
	//Sleep(1000); //休息1000毫秒（1秒）
	cout << "我的线程执行完毕了" << endl;	
	return;
}
*/
void myprint()
{
	cout << "我的线程开始执行了" << endl;

	cout << "我的线程执行完毕了1" << endl;
	cout << "我的线程执行完毕了2" << endl;
	cout << "我的线程执行完毕了3" << endl;
	cout << "我的线程执行完毕了4" << endl;
	cout << "我的线程执行完毕了5" << endl;
	cout << "我的线程执行完毕了6" << endl;
	cout << "我的线程执行完毕了7" << endl;
	cout << "我的线程执行完毕了8" << endl;
	cout << "我的线程执行完毕了9" << endl;
	cout << "我的线程执行完毕了10" << endl;
	cout << "我的线程执行完毕了11" << endl;
	cout << "我的线程执行完毕了12" << endl;
	return;
}

class TA
{
public:
	//TA(int& i) :m_i(i) {		
	TA(int i) :m_i(i) {
		printf("TA()构造函数执行，m_i=%d,this=%p\n", m_i, this);
	}
	~TA() {
		printf("~TA()析构函数执行，m_i=%d,this=%p\n", m_i, this);
	}
	TA(const TA& ta) :m_i(ta.m_i) {
		printf("TA()拷贝构造函数执行，m_i=%d,this=%p\n", m_i, this);
	}

public:

	void operator()() //不带参数
	{
		cout << "mi1的值为:" << m_i << endl; //隐患，m_i可能没有有效值
		cout << "mi2的值为:" << m_i << endl;
		cout << "mi3的值为:" << m_i << endl;
		cout << "mi4的值为:" << m_i << endl;
		cout << "mi5的值为:" << m_i << endl;
		cout << "mi6的值为:" << m_i << endl;
	}
	//int& m_i; //引入一个引用类型的成员变量
	int m_i;
};


//void test01() {
//	thread mytobj(myprint); //创建一个线程，也可以称为创建一个子线程
//	mytobj.detach();
//	cout << "main主函数执行结束!" << endl;
//}

int main() {
	//cout << "I Love China!" << endl; 
	//实际上这个就是主线程在执行，主线程序从main函数返回，则整个进程执行完毕

	/*
	std::thread mytobj(myprint);
	mytobj.join();
	cout << "main主函数执行结束!" << endl;
	*/

	/*
	thread mytobj(myprint); //创建一个线程，也可以称为创建一个子线程
	mytobj.detach();
	cout << "main主函数执行结束!" << endl;
	*/

	/*
	int myi = 6;
	TA ta(myi);
	thread mytobj3(ta);  //ta 为可调用对象
	//这里不可以是临时对象thread mytobj3(TA()); 否则编译无法通过

	mytobj3.join();//为保证等待线程执行结束，这里使用join.
	cout << "main主函数执行结束!" << endl;
	*/

	auto mylamthread = [] {
		cout << "我的线程开始执行了" << endl;
		//...
		cout << "我的线程执行完毕了" << endl;
	};
	thread mytobj4(mylamthread);
	mytobj4.join();
	cout << "main主函数执行结束!" << endl;

	return 0;
}