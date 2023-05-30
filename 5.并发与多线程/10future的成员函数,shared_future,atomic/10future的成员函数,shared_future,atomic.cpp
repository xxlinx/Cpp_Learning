#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <future>
#include <windows.h>

using namespace std;
/*
int mythread()
{
	cout << "mythread() start" << " threadid = " << std::this_thread::get_id() << endl; //新的线程id
	std::chrono::milliseconds dura(5000); //1秒 = 1000毫秒，所以5000毫秒 = 5秒
	std::this_thread::sleep_for(dura); //休息一定的时长
	cout << "mythread() end" << " threadid = " << std::this_thread::get_id() << endl;
	return 5;
}
*/
std::atomic<int> g_mycout = 0;
void mythread()
{
	for (int i = 0; i < 10000000; i++) //1千万
	{
		//g_my_mutex.lock();
		//g_mycout++; //对应的操作就是原子操作，不会被打断
		//g_mycout+=1; //对应的操作就是原子操作，不会被打断
		g_mycout = g_mycout + 1; //这样写就不是原子操作了
		//g_my_mutex.unlock();
	}
	return;
}

int main() {

	/*
	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	std::future<int>  result = std::async(mythread);
	//std::future<int>  result = std::async(std::launch::deferred,mythread); //流程并不会卡在这里
	cout << "continue......!" << endl;
	//cout << result.get() << endl;  //卡在这里等待线程执行完,但是这种get因为一些内部特殊操作（移动操作），不能get多次，只能get一次
	//future_status看成一个枚举类型
	std::future_status status = result.wait_for(std::chrono::seconds(1));

	if (status == std::future_status::timeout) {
		//超时线程还没执行完
		cout << "超时线程没执行完!" << endl;
		cout << result.get() << endl; //没执行完这里也要求卡在这里等线程返回
	}
	else if (status == std::future_status::ready) {
		//线程成功返回
		cout << "线程成功执行完毕并返回!" << endl;
		cout << result.get() << endl;
	}
	else if (status == std::future_status::deferred) {
		//如果async的第一个参数被设置为std::launch::deferred,则本条件成立
		cout << "线程被延迟执行!" << endl;
		cout << result.get() << endl;  //上节说过，这会导致在主线程中执行了线程入口函数
	}
	*/

	//原子操作 std::atomic

	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	thread mytobj1(mythread);
	thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
	cout << "两个线程都执行完毕，最终的g_mycout的结果是" << g_mycout << endl;




	cout << "main主函数执行结束!" << endl;
	return 0;
}