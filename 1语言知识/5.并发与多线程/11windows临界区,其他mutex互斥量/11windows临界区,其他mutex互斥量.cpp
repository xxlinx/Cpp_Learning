#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

#include <windows.h>

using namespace std;


#define __WINDOWSLJQ__  //宏定义

//本类用于自动释放Windows下的临界区，防止忘记LeaveCriticalSection的情况发生
class CWinLock {
public:
	CWinLock(CRITICAL_SECTION* pCritSect) //构造函数
	{
		m_pCritical = pCritSect;
		EnterCriticalSection(m_pCritical);
	}
	~CWinLock() //析构函数
	{
		LeaveCriticalSection(m_pCritical);
	}
private:
	CRITICAL_SECTION* m_pCritical;
};


class A {
public:
	A() {
#ifdef __WINDOWSLJQ__
		InitializeCriticalSection(&my_winsec);  //初始化临界区
#endif
	}
	virtual ~A() {
#ifdef __WINDOWSLJQ__ 
		DeleteCriticalSection(&my_winsec);  //释放临界区
#endif
	}
	//把收到的消息入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; i++) {
			cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
#ifdef __WINDOWSLJQ__ 
			//EnterCriticalSection(&my_winsec); //进入临界区
			//EnterCriticalSection(&my_winsec); //调用两次

			CWinLock wlock(&my_winsec);
			CWinLock wlock2(&my_winsec); //调用多次也没问题
			msgRecvQueue.push_back(i);
			//LeaveCriticalSection(&my_winsec); //离开临界区
			//LeaveCriticalSection(&my_winsec);//也要调用两次
#else
			//my_mutex.lock();
			std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
			msgRecvQueue.push_back(i);
			//my_mutex.unlock();
#endif
		}
	}

	bool outMsgLULProc(int& command) {
#ifdef __WINDOWSLJQ__ 
		EnterCriticalSection(&my_winsec);
		if (!msgRecvQueue.empty())
		{
			int command = msgRecvQueue.front();//返回第一个元素但不检查元素存在与否
			msgRecvQueue.pop_front();
			LeaveCriticalSection(&my_winsec);
			return true;
		}
		LeaveCriticalSection(&my_winsec);
#else
		my_mutex.lock();
		if (!msgRecvQueue.empty())
		{
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			my_mutex.unlock();
			return true;
		}
		my_mutex.unlock();
#endif
		return false;
	}

	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{
			bool result = outMsgLULProc(command);
			if (result == true)
			{
				cout << "outMsgRecvQueue()执行了，从容器中取出一个元素" << command << endl;
				//这里可以考虑处理数据
				//......			
			}
			else
			{
				cout << "outMsgRecvQueue()执行了，但目前收消息队列中是空元素" << i << endl;
			}
		}
		cout << "end" << endl;
	}

private:
	std::list<int> msgRecvQueue;
	std::mutex my_mutex;
	//std::recursive_timed_mutex my_mutex;
#ifdef __WINDOWSLJQ__ 
	//windows下叫临界区（类似于互斥量mutex）
	CRITICAL_SECTION my_winsec;
#endif
};

int main() {
	A  myobja;
	std::thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja);
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutnMsgObj.join();
	cout << "main主函数执行结束!" << endl;
	return 0;
}