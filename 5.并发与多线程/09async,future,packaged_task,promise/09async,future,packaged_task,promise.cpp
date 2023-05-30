#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <future>
#include <windows.h>

using namespace std;

//int mythread(int mypar) { //线程入口函数
//
//	cout << "mythread() start" << " threadid = " << std::this_thread::get_id() << endl; //新的线程id
//	std::chrono::milliseconds dura(5000); //1秒 = 1000毫秒，所以5000毫秒 = 5秒
//	std::this_thread::sleep_for(dura); //休息一定的时长
//	cout << "mythread() end" << " threadid = " << std::this_thread::get_id() << endl;
//	return 5;
//}

class A {

public:
	int mythread(int mypar) {
		cout << mypar << endl;
		cout << "mythread() start" << " threadid = " << std::this_thread::get_id() << endl; //新的线程id
		std::chrono::milliseconds dura(5000); //1秒 = 1000毫秒，所以5000毫秒 = 5秒
		std::this_thread::sleep_for(dura); //休息一定的时长
		cout << "mythread() end" << " threadid = " << std::this_thread::get_id() << endl;
		return 5;
	}
};

void mythread(std::promise<int>& tmpp, int calc) //注意第一个参数
{
	cout << "mythread() start" << " threadid = " << std::this_thread::get_id() << endl;
	//做一系列复杂操作
	calc++;
	calc *= 10;
	//做其他运算，整个花费了5秒
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);

	//终于计算出了结果
	int result = calc; //保存结果
	tmpp.set_value(result);  //结果保存到了tmpp这个对象中
	cout << "mythread() end" << " threadid = " << std::this_thread::get_id() << endl;
}

void mythread2(std::future<int>& tmpf) //注意参数
{
	auto result = tmpf.get(); //获取值，只能get一次否则会报异常
	cout << "mythread2 result = " << result << endl;
	return;
}

vector<std::packaged_task<int(int)> > mytasks;
int main() {

	/*
	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	std::future<int>  result = std::async(mythread); //流程并不会卡在这里，注意如果线程入口函数需要参数，可以把参数放在async的第二个参数的位置
	cout << "continue......!" << endl;
	cout << result.get() << endl;  //卡在这里等待线程执行完,但是这种get因为一些内部特殊操作，不能get多次，只能get一次，否则执行会报异常	
	//result.wait(); //流程卡在这里等待线程返回，但本身不返回结果
	*/
	/*
	A a;
	int tmppar = 12;
	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	std::future<int>  result = std::async(&A::mythread, &a, tmppar);
	cout << "continue......!" << endl;
	cout << result.get() << endl;
	*/


	//packaged_task
	/*
	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread);  //把函数mythread通过packaged_task包装起来
	std::thread t1(std::ref(mypt), 1);  //线程直接开始执行，第二个参数作为线程入口函数的参数
	t1.join(); //可以调用这个等待线程执行完毕,不调用这个不行，程序会崩溃
	std::future<int> result = mypt.get_future();  //std::future对象里含有线程入口函数的返回结果，这里用result保存mythread返回的结果
	cout << result.get() << endl;
	*/
	
	/*
	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt([](int mypar) //创建或者叫包装一个任务
		{
			cout << mypar << endl;
			cout << "lambda mythread() start" << " threadid = " << std::this_thread::get_id() << endl;
			std::chrono::milliseconds dura(5000); //1秒 = 1000毫秒，所以20000毫秒 = 20秒
			std::this_thread::sleep_for(dura); //休息一定的时长
			cout << "lambda mythread() end" << " threadid = " << std::this_thread::get_id() << endl;
			return 15;
		});
	//入容器
	mytasks.push_back(std::move(mypt)); //移动语义,这里要注意,入进去后mytp就empty了
	//出容器
	std::packaged_task<int(int)> mypt2;
	auto iter = mytasks.begin();
	mypt2 = std::move(*iter); //用移动语义
	mytasks.erase(iter);//删除第一个元素，迭代器已经失效，不能再用
	mypt2(123); //直接调用
	//要取得结果，则还是要借助这个future
	std::future<int> result = mypt2.get_future();
	cout << result.get() << endl;
	*/

	//std::promise
	cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	std::promise<int> myprom; //声明一个std::promise对象myprom，保存的值类型为int
	//创建一个线程t1，将函数mythread及对象myprom作为参数放进去
	std::thread t1(mythread, std::ref(myprom), 180);
	t1.join(); //等线程执行完毕，这个必须有，否则报异常,join放在.get后面也可以

	//获取结果值
	std::future<int> fu1 = myprom.get_future(); //promise和future绑定用于获取线程返回值
	//auto result = fu1.get(); //获取值，但是这种get因为一些内部特殊操作，不能get多次，只能get一次	
	//cout << "result = " << result << endl;

	std::thread t2(mythread2, std::ref(fu1));
	t2.join(); //等线程执行完毕	

	cout << "main主函数执行结束!" << endl;
	return 0;
}