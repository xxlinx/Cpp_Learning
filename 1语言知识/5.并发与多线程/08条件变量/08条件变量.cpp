#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

#include <windows.h>

using namespace std;

//std::condition_variable, wait, notify_once

class A {
public:
	//把收到的消息（玩家命令）入到一个队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
			std::unique_lock<std::mutex> sbguard1(my_mutex);
			msgRecvQueue.push_back(i);

			my_cond.notify_one();
			//尝试把卡（堵塞）在wait()的线程唤醒，但光唤醒了还不够，
			//这里必须把互斥量解锁，另外一个线程的wait()才会继续正常工作



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
		while (true) {
			std::unique_lock<std::mutex> sbguard1(my_mutex);
			
			//wait()用于等一个东西
			//如果wait()第二个参数的lambda表达式返回的是true，wait就直接返回
			//如果wait()第二个参数的lambda表达式返回的是false,那么wait()将解锁互斥量,并堵塞到这行，那堵到什么时候为止呢？堵到其他某个线程调用notify_one()通知为止
			
			//如果wait()不用第二个参数，那跟第二个参数为lambda表达式并且返回false效果 一样（解锁互斥量,并堵塞到这行，堵到其他某个线程调用notify_one()通知为止）

			my_cond.wait(sbguard1, [this] {   //因为用了类A的成员变量 所以这里写this  lambda 表达式
				if (!msgRecvQueue.empty())
					return true;
				return false;
				});
			//走到这，说明就是锁着的 流程走下来意味着msgRecvQueue队列里必然有数据
			command = msgRecvQueue.front(); //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();  //移除第一个元素，但不返回
			sbguard1.unlock(); //因为unique_lock的灵活性，我们可以随时unlock解锁，以免锁住太长时间
			cout << "outMsgRecvQueue()执行，取出一个元素" << command << " threadid = " << std::this_thread::get_id() << endl;

		}//end while
		cout << "end" << endl;
	}

	
private:
	std::list<int> msgRecvQueue; //容器(消息队列)
	std::mutex my_mutex; //创建了一个互斥量 （一把锁头）

	std::condition_variable my_cond; //生成一个条件变量对象 需要和一个互斥量配合使用
};


//若有多个wait的线程，则用 notify_all  用于通知所以处于wait 状态的线程
int main() {

	A myobja;
	std::thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja);
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutnMsgObj.join();
	cout << "main主函数执行结束!" << endl;

	return 0;
}