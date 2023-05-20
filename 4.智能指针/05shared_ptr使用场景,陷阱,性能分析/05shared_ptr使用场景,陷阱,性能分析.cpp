#include <iostream>
#include <vector>

using namespace std;

shared_ptr<int> createO(int value)
{
	return make_shared<int>(value); //返回一个shared_ptr
}
//void myfunc(int value)
//{
//	shared_ptr<int> ptmp = createO(10);
//	return;  //ptmp离开了作用域（ptmp是局部变量），因此它指向的内存会被自动释放；
//}
shared_ptr<int> myfunc(int value)
{
	shared_ptr<int> ptmp = createO(10);
	return ptmp;  //这个return会导致 引用计数递增，所以ptmp指向的内存不会释放。这相当于返回了一个ptmp的拷贝。ptmp销毁计数-1，return ptmp;使计数+1
}
void test01() {
	myfunc(12);
}

//使用陷阱分析
void proc(shared_ptr<int> ptr)
{
	return;
}


void test02() {
	int* p = new int(100); //裸指针
	//proc(p);//语法错 int *p不能转换成shared_ptr<int>
	shared_ptr<int>(p); //参数是个临时shared_ptr，用一个裸指针显式构造的
	//*p = 45; //不可以预料到的结果；因为p指向的内存已经被释放了
}
void test03() {
	shared_ptr<int> myp(new int(100));
	proc(myp);
	*myp = 45; //myp可是shared_ptr<...>类型，*代表解引用
}
//不要用同一个裸指针初始化多个shared_ptr
void test04() {
	//int* pi = new int;
	//shared_ptr<int> p1(pi);
	//shared_ptr<int> p2(pi); //p1一个引用，p2一个引用，会导致p1,p2两个指针之间无关联关系（每个的强引用计数都是1），所以释放时pi所指向的内存释放2次，这显然会出问题
	shared_ptr<int> p1(new int); //这种写法至少大大降低了用pi来创建p2的可能性
}
//慎用get返回的指针
void test05() {
	//shared_ptr<int> myp(new int(100));
	//int* p = myp.get(); //返回myp中保存的指针
	//delete p;  //不可以这样，会导致异常
}

//class CT
//{
//public:
//	shared_ptr<CT> getself()
//	{
//		return shared_ptr<CT>(this);
//	}
//};
class CT :public std::enable_shared_from_this<CT> //这是C++标准库里提供的一个类模板
{
public:
	shared_ptr<CT> getself()
	{
		return shared_from_this();//这个是enable_shared_from_this类中方法,要通过此方法返回智能指针
	}
};
void test06() {
	shared_ptr<CT> pct1(new CT);
	shared_ptr<CT> pct2 = pct1->getself(); //修改后就没有问题了
}
//移动语义
void test07() {

	shared_ptr<int> p1(new int(100));  //p1指向该对象(内存)
	shared_ptr<int> p2(std::move(p1)); //移动语义，移动构造p2，p1不再指向该对象而变成空，p2指向了该对象，引用计数保持为1
	shared_ptr<int> p3;
	p3 = std::move(p2); //移动赋值，p2指向空，p3指向该对象，整个对象引用计数依旧为1		

}

//内存分配不一样
void test08() {
	shared_ptr<string> ps1(new string("I Love China!")); //分配两次
	auto ps2 = make_shared<string>("I Love China!");  //分配一次
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