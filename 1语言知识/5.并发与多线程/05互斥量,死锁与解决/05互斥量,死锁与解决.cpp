#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

#include <windows.h>

using namespace std;

class A {
public:
	//把收到的消息入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
			{
				/*std::lock_guard<std::mutex> sbguard(my_mutex);
				std::lock_guard<std::mutex> sbguard(my_mutex2);*/

				std::lock(my_mutex, my_mutex2);
				std::lock_guard<std::mutex> sbguard(my_mutex, std::adopt_lock);
				std::lock_guard<std::mutex> sbguard(my_mutex2, std::adopt_lock);
				//my_mutex.lock();
				//假设这个数字就是我收到的命令，我直接放到消息队列里来
				msgRecvQueue.push_back(i);
				//my_mutex.unlock();

				//my_mutex.unlock();
				//my_mutex2.unlock();
			}
		}
	}

	bool outMsgLULProc(int& command) {
		//my_mutex.lock();
		//std::lock_guard<std::mutex> sbguard(my_mutex);
		//std::lock_guard<std::mutex> sbguard(my_mutex2);
		std::lock(my_mutex2, my_mutex);
		std::lock_guard<std::mutex> sbguard(my_mutex, std::adopt_lock);
		std::lock_guard<std::mutex> sbguard(my_mutex2, std::adopt_lock);

		if (!msgRecvQueue.empty()) {
			int command = msgRecvQueue.front();//返回第一个元素但不检查元素存在
			msgRecvQueue.pop_front();//移除第一个元素但不返回	
			//my_mutex.unlock();
			return true;
		}
		//my_mutex.unlock();

		//my_mutex2.unlock();
		//my_mutex.unlock();
		
		return false;
	}

	//把数据从消息队列中取出的线程
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; i++) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "outMsgRecvQueue()执行了，从容器中取出一个元素" << command << endl;
				//处理数据
				//...

			} else {
				cout << "outMsgRecvQueue()执行了，但目前收消息队列中是空元素" << i << endl;
			}
		}
		cout << "end" << endl;
	}

private:
	std::list<int>  msgRecvQueue;
	//容器（收消息队列），专门用于代表玩家给咱们发送过来的命令
	std::mutex my_mutex;//创建互斥量
	std::mutex my_mutex2; //创建互斥量
};

int main() {

	A  myobja;
	std::thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja);  //注意这里第二个参数必须是引用（用std::ref也可以），才能保证线程里用的是同一个对象（上节课详细分析过了）
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutnMsgObj.join();
	cout << "main主函数执行结束!" << endl;

	return 0;
}