#include <iostream>
#include <vector>
#include <thread>
#include <list>

#include <windows.h>

using namespace std;

vector<int> g_v = { 1,2,3 };

//线程入口函数，可以给多个线程使用

//void myprint(int inum)
//{
//	cout << "myprint线程开始执行了,线程编号=" << inum << endl;
//	//干各种事情
//	cout << "myprint线程结束执行了,线程编号=" << inum << endl;
//	return;
//}
void myprint(int inum)
{
	cout << "id为" << std::this_thread::get_id() << "的线程 打印g_v值" << g_v[0] << g_v[1] << g_v[2] << endl;
	return;
}

class A {
public:
	//把收到的消息入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;

			//假设这个数字就是我收到的命令，我直接放到消息队列里来
			msgRecvQueue.push_back(i); 			
		}
	}

	//把数据从消息队列中取出的线程
	void outMsgRecvQueue() {
		for (int i = 0; i < 100000; i++) {
			if (!msgRecvQueue.empty()) {
				int command = msgRecvQueue.front();//返回第一个元素但不检查元素存在与否
				msgRecvQueue.pop_front();          //移除第一个元素但不返回	
				//这里可以考虑处理数据
				//......
			}
			else {
				cout << "outMsgRecvQueue()执行了，但目前收消息队列中是空元素" << i << endl;
			}
		}
		cout << "end" << endl;
	}

private:
	std::list<int>  msgRecvQueue; 
	//容器（收消息队列），专门用于代表玩家给咱们发送过来的命令

};


int main() {
	
	//1.创建和等待多个线程
	/*
	vector <thread> mythreads;
	//线程入口函数都为myprint
	for (int i = 0; i < 5; i++) {
		mythreads.push_back(thread(myprint, i));  //创建并开始执行线程
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
		iter->join(); //等待5个线程都返回
	}
	cout << "main主函数执行结束!" << endl; //最后执行这句，然后整个进程退出
	*/

	//2.数据共享问题
	//2.1只读得数据
	/*
	vector <thread> mythreads;
	//线程入口函数都为myprint
	for (int i = 0; i < 5; i++) {
		mythreads.push_back(thread(myprint, i));  //创建并开始执行线程
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
		iter->join(); //等待5个线程都返回
	}
	cout << "main主函数执行结束!" << endl;//最后执行这句，然后整个进程退出
	*/
	//2.2有读有写的数据
	//不可同时读写，会崩溃

	//3.共享数据的保护
	A myobja;

	std::thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja);

	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myInMsgObj.join();
	myOutnMsgObj.join();
	cout << "main主函数执行结束!" << endl;

	return 0;
}