#include <iostream>
#include <vector>

using namespace std;

void myfunc(shared_ptr<int> ptmp) //如果传递引用作为形参进来，则引用计数不会增加
{
	return;
}

shared_ptr<int> myfunc2(shared_ptr<int>& ptmp) //这里是引用，所以计数还是为2
{
	return ptmp;
}
void test01() {
	auto p6 = std::make_shared<int>(100); //目前p6所指的对象只有p6一个引用者
	auto p7(p6);  //写成auto p7 = p6;也可以，智能指针拷贝，p7和p6指向相同的对象，此对象目前有两个引用者     		
	myfunc(p7); //当然，这个函数执行完毕后，这个指针的引用计数会恢复
	auto p8 = myfunc2(p7); //如果有p8接收myfunc2函数返回值，那么此时引用计数会变成3
	//myfunc2(p7); //引用计数保持2不变，因为没有变量来接收myfunc2(p7)调用的返回值
	p8 = std::make_shared<int>(200); //p8指向新对象计数1，p6,p7计数恢复为2
	p7 = std::make_shared<int>(200); //p7指向新对象计数1，p6指向的原对象恢复计数为1
	p6 = std::make_shared<int>(200); //p6指向新对象计数1，p6指向的原对象内存被释放	

}

//shared_ptr常用操作
//use_count成员函数
void test02() {
	shared_ptr<int> myp(new int(100));
	int icount = myp.use_count(); //1
	shared_ptr<int> myp2(myp);
	icount = myp.use_count(); //2
	shared_ptr<int> myp3;
	myp3 = myp2;
	icount = myp.use_count(); //3
	icount = myp3.use_count(); //3
}
//unique成员函数   是否use_count = 1
void test03() {
	shared_ptr<int> myp(new int(100));
	if (myp.unique()) //本条件成立
	{
		//"myp"独占所指向的对象
		cout << "myp unique ok" << endl;
	}
	shared_ptr<int> myp2(myp);
	if (myp.unique()) //本条件不再成立
	{
		cout << "myp unique ok" << endl;
	}
}
//reset成员函数
//无参数的时候
void test04() {
	shared_ptr<int> pi(new int(100));
	pi.reset(); //释放pi指向的对象，将pi置空
	if (pi == nullptr)//条件成立
	{
		cout << "pi被置空" << endl;
	}
	shared_ptr<int> pi1(new int(100));
	auto pi2(pi1); //pi2引用计数现在为2
	pi1.reset(); //pi1被置空，pi2引用计数变为1
}
//有参数的时候
void test05() {
	shared_ptr<int> pi(new int(100));
	pi.reset(new int(1)); //释放原内存（内容为100的内存），指向新内存（内容为1的内存）
}
void test06() {
	shared_ptr<int> pi(new int(100));
	auto pi2(pi);  //pi2引用计数为2
	pi.reset(new int(1));  //现在pi引用计数为1，上面的pi2引用计数为1
	if (pi.unique()) //本条件成立
	{
		cout << "pi unique ok" << endl;
	}
	if (pi2.unique()) //本条件成立
	{
		cout << "pi2 unique ok" << endl;
	}

	//空指针也可以
	shared_ptr<int> p; //p现在是空指针
	p.reset(new int(100)); 
	//释放pi指向的对象，让pi指向新内存
	//因为原来pi为空，所以就等于啥也没释放	
}

// * 解引用
void test07() {
	shared_ptr<int> pother(new int(12345));
	char outbuf[1024];
	sprintf_s(outbuf, sizeof(outbuf), "%d", *pother);
	//outbuf中的内容就是"12345"，pother不发生任何变化，引用计数仍旧为1
}

//get 成员函数
void test08() {
	shared_ptr<int> myp(new int(100));
	int* p = myp.get();
	*p = 45;
	//裸指针 由 智能指针管理
	//delete p; //不可，结果无法预料

}

//swap成员函数
void test09() {
	shared_ptr<string> ps1(new string("I Love China1!"));
	shared_ptr<string> ps2(new string("I Love China2!"));
	std::swap(ps1, ps2); //可以
	ps1.swap(ps2); //也可以
}

// = nullptr
void test10() {
	shared_ptr<string> ps1(new string("I Love China!"));
	ps1 = nullptr;
}

//智能指针名字作为判断条件
void test11() {
	shared_ptr<string> ps1(new string("I Love China1!"));
	//若ps1指向一个对象，则条件成立
	if (ps1)//条件成立  不是空就成立
	{
		cout << "ps1" << endl; //执行
	}
}

//指定删除器和数组问题
void myDeleter(int* p) //自己的删除器，删除整型指针用的，当p的引用计数为0，则自动调用这个删除器删除对象，释放内存
{
	delete p;
}
void test12() {
	shared_ptr<int> p(new int(12345), myDeleter); //指定删除器
	shared_ptr<int> p2(p); //现在两个引用计数指向该对象
	p2.reset(); //现在一个引用计数指向该对象，p2为nullptr了
	p.reset();//此时只有一个指针指向该对象，所以释放指向的对象，调用自己的删除器myDeleter，同时p置空
}
void test13() {
	shared_ptr<int> p(new int(12345), [](int* p) {delete p;});
	p.reset(); //会调用删除器（lambda表达式）
	//默认的删除器不支持数组对象
	shared_ptr<int[]> p(new int[10], [](int* p) {delete[] p;});
	p.reset();
}

class A
{
public:
	A()
	{
		cout << "A()构造函数被调用" << endl;
	}
	~A()
	{
		cout << "~A()析构函数被调用" << endl;
	}
};
void test14() {
	//shared_ptr<A> pA(new A[10]); 
	//异常，因为系统释放pA是使用delete pA而不是使用delete[]pA，所以必须自己写删除器
	shared_ptr<A> pA(new A[10], [](A* p) {
		delete[] p;
		}); //一切正常
}

//default_delete作为删除器
void test15() {
	shared_ptr<A> pA(new A[10], std::default_delete<A[]>());
}
void test16() {
	shared_ptr<A[]> pA(new A[10]);  //<>中加个[]就行了
	shared_ptr<int[]> p(new int[10]); //<>中加个[]就行了，而且加了[]后，引用也方便比如p[0]、p[1]......p[9]直接拿来用

}

//定义一个函数模板，解决shared_ptr管理动态数组的情形
template<typename T>
shared_ptr<T> make_shared_array(size_t size)
{
	return shared_ptr<T>(new T[size], default_delete<T[]>()); //指定了删除器
}
void test17() {
	shared_ptr<int> pintArr = make_shared_array<int>(5); //末尾数字代表数组元素个数
	shared_ptr<A> pAArr = make_shared_array<A>(15); //末尾数字代表数组元素个数

}

void test18() {
	auto lambda1 = [](int* p)
	{
		delete p;
	};

	auto lambda2 = [](int* p)
	{
		delete p;
	};
	shared_ptr<int> p1(new int(100), lambda1); //指定lambda1为删除器
	shared_ptr<int> p2(new int(200), lambda2); //指定lambda2为删除器
	p2 = p1; //p2会先调用lambda2把自己所指向对象释放，然后指向p1所指对象，现在该对象引用计数为2。整个main函数执行完毕之前还会调用lambda1释放p1,p2共同指向的对象
	
	
	vector<shared_ptr<int>> pvec{ p1,p2 }; //在.cpp源文件头#include <vector>

}

int main() {

	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	test06();

	return 0;
}