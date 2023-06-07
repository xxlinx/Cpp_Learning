#include <iostream>
#include <vector>

using namespace std;
void test01() {
	auto pi = make_shared<int>(100);
	//weak_ptr<int> piw(pi);
	//piw弱共享pi,pi引用计数（强引用计数）不改变，弱引用计数字会从0变成1；pi和piw两者指向相同位置
	
	weak_ptr<int> piw;
	piw = pi; //pi这里是一个shared_ptr，赋值给一个weak_ptr。pi和piw两者指向相同位置
	weak_ptr<int> piw2;
	piw2 = piw; //把weak_ptr赋给另外一个weak_ptr，现在pi是1个强引用，2个弱引用

	auto pi2 = piw.lock(); //强引用(shared_ptr)计数会加1，现在pi是2个强引用，2个弱引用
	if (pi2 != nullptr)    //条件成立；写成if(pi2)也可以
	{
		cout << "所指对象存在" << endl;
	}
}

//weak_ptr操作
//use_count常用操作
void test02() {
	auto pi = make_shared<int>(100);
	auto pi2(pi); //pi2类型是个shared_ptr
	weak_ptr<int> piw(pi);
	int isc = piw.use_count(); //2:与本piw共享对象的shared_ptr数量
	pi.reset();
	pi2.reset();
	if (piw.expired()) //是否过期,此时成立
	{
		cout << "piw已过期" << endl;
	}
}

//expired成员函数
void test03() {
	auto pi = make_shared<int>(100);
	auto pi2(pi); //pi2类型是个shared_ptr
	weak_ptr<int> piw(pi);
	int isc = piw.use_count(); //2:与本piw共享对象的shared_ptr数量
	pi.reset();
	pi2.reset();
	if (piw.expired()) //是否过期,此时成立
	{
		cout << "piw已过期" << endl;
	}
}

//reset成员函数
void test04() {

	auto pi = make_shared<int>(100);
	weak_ptr<int> piw(pi);
	piw.reset();	//pi是1个强引用，无弱引用
}

//lock成员函数
void test05() {
	auto p1 = make_shared<int>(42);
	weak_ptr<int> pw;
	pw = p1;    //可以用shared_ptr给weak_ptr值，现在p1是1个强引用，1个弱引用
	if (!pw.expired()) //条件成立
	{
		//没过期：
		auto p2 = pw.lock(); //返回的p2是一个shared_ptr，现在p1是2个强引用，1个弱引用			
		if (p2 != nullptr)//条件成立
		{
			cout << "所指对象存在" << endl;
		}

		//离开这个范围，p1的强引用计数恢复为1，弱引用保持为1
	}
	else
	{
		cout << "pw已经过期" << endl;
	}
	//走到这里，p1是1个强引用，1个弱引用	

}
void test06() {

	weak_ptr<int> pw;
	{
		auto p1 = make_shared<int>(42);
		pw = p1; //可以用shared_ptr给weak_ptr值
	} //离开这里时p1就失效了，那么pw会变成啥情况？
	//这里pw这个weak_ptr就会过期了
	if (pw.expired()) //条件成立
	{
		cout << "pw已经过期" << endl;
	}
}


//尺寸问题
void test07() {
	shared_ptr<int> p1(new int(100));
	weak_ptr<int> pw(p1);
	int ilen = sizeof(p1);  //8
	int ilen2 = sizeof(pw); //8
	cout << "设置断点" << endl;
}

int main() {

	test01();

	test02();
	test03();
	test04();
	test05();
	test06();
	test07();

	return 0;
}