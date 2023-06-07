#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

#include <windows.h>

using namespace std;

class A {
public:
	//把收到的消息（玩家命令）入到一个队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
			std::unique_lock<std::mutex> sbguard1(my_mutex);
			msgRecvQueue.push_back(i);
		}
		return;
	}

	bool outMsgLULProc(int& command) {
		std::unique_lock<std::mutex> sbguard1(my_mutex);

		if (!msgRecvQueue.empty()) {
			//消息不为空			
			command = msgRecvQueue.front(); //返回第一个元素，但不检查元素是否存在；
			msgRecvQueue.pop_front();  //移除第一个元素，但不返回；
			return true;
		}
		return false;
	}

	//把数据从消息队列中取出的线程
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; ++i)
		{
			bool result = outMsgLULProc(command);
			if (result == true)
			{
				cout << "outMsgRecvQueue()执行了，从容器中取出一个元素" << command << endl;
				//可以考虑进行命令（数据）处理
				//....
			}
			else
			{
				//消息对列为空
				cout << "outMsgRecvQueue()执行了，但目前收消息队列中是空元素" << i << endl;
			}
		}
		cout << "end" << endl;
	}

	std::unique_lock<std::mutex> rtn_unique_lock()
	{
		std::unique_lock<std::mutex> tmpguard(my_mutex);
		return tmpguard;//从函数返回一个局部unique_lock对象是可以的，返回这种局部对象tmpguard会导致系统生成临时unique_lock对象，并调用unique_lock的移动构造函数
	}
private:
	std::list<int> msgRecvQueue; //容器(消息队列)
	std::mutex my_mutex; //创建了一个互斥量 （一把锁头）
};


int main() {

	A myobja;
	std::thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja);
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutnMsgObj.join();
	cout << "main主函数执行结束!" << endl;

	return 0;
}