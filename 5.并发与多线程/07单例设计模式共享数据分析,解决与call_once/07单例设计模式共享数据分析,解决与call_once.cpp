#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

#include <windows.h>

using namespace std;
std::mutex resource_mutex;

std::once_flag g_flag; //这是个系统定义的标记

class MyCAS {    //这是一个单例类
private:
	MyCAS() {} //构造函数是私有的
private:
	static MyCAS* m_instance;   //静态成员变量
private:
	static void CreateInstance() {
		cout << "CreateInstance()执行完毕" << std::this_thread::get_id();  //测试用

		m_instance = new MyCAS();
		static CGarhuishou cl;
	}
public:
	static MyCAS* GetInstance() {

		/*
		if (m_instance == NULL) {   //双重锁定
			std::unique_lock<std::mutex> mymutex(resource_mutex); //自动加锁
			if (m_instance == NULL) {
				m_instance = new MyCAS();
				static CGarhuishou cl;
			}
				
		}			
		return m_instance;
		*/
		if (m_instance == NULL) {
			std::call_once(g_flag, CreateInstance);
			
		}
		
		return m_instance;
	}


	void func() {
		cout << "测试" << endl;
	}

	class CGarhuishou {  //类中套类，用于释放对象
	public:
		~CGarhuishou() {
			if (MyCAS::m_instance) {
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
	};

};

//类静态变量初始化
MyCAS* MyCAS::m_instance = NULL;

void mythread()
{
	cout << "我的线程开始执行了" << endl;
	MyCAS* p_a = MyCAS::GetInstance(); //在这里初始化就很可能出现问题
	cout << "我的线程执行完毕了" << endl;
	return;
}


int main() {
	/*
	单例类测试
	MyCAS* p_a = MyCAS::GetInstance();
	p_a->func();
	MyCAS::GetInstance()->func();
	*/
	
	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
	
	return 0;
}