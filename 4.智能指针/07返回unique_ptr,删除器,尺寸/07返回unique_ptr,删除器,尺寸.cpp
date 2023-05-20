#include <iostream>
#include <vector>

using namespace std;

//返回一个unique_ptr
unique_ptr<string> tuniqp()
{
	unique_ptr<string> pr(new string("I Love China!"));
	return pr;	//从函数返回一个局部unique_ptr对象是可以的 返回局部对象pr会导致系统生成临时unique_ptr对象，并调用unique_ptr的移动构造函数
}
//也可这样写这个函数
//unique_ptr<string> tuniqp()
//{
//	return unique_ptr<string>(new string("I Love China!"));
//}
void test01() {
	unique_ptr<string> ps;
	ps = tuniqp(); //可以用ps接收tuniqp返回结果，则临时对象直接构造在ps里，如果不接收，则临时对象会释放，同时释放掉所指向的对象的内存
	cout << "断点调试" << endl;
}

//删除器  unique_ptr的删除器复杂一些
//删除器
void mydeleter(string* pdel)
{
	delete pdel;
	pdel = nullptr;
	//可以在这打印日志
}
void test02() {
	typedef void(*fp)(string*); //定义一个函数指针类型，类型名为fp
	unique_ptr<string, fp> ps1(new string("I Love China!"), mydeleter);
}
   //用using 来定义 fp2
void test03() {
	using fp2 = void(*)(string*); //用using定义一个函数指针类型，类型名为fp2
	unique_ptr<string, fp2> ps2(new string("I Love China!"), mydeleter);
}
   //又一种写法
void test04() {
	typedef decltype(mydeleter)* fp3; 
	//注意这里多了个*,因为decltype是返回函数类型，
	//加*表示函数指针类型，现在fp3应该是void *(string *)，decltype后面会讲,先知道就行
	unique_ptr<string, fp3> ps3(new string("I Love China!"), mydeleter);

	std::unique_ptr<string, decltype(mydeleter)*> ps4(new string("I Love China!"), mydeleter);
}
void test05() {
	auto mydella = [](string* pdel) {
		delete pdel;
		pdel = nullptr;
	};
	std::unique_ptr<string, decltype(mydella)> ps5(new string("I Love China!"), mydella);
	int ilen = sizeof(ps5);
}

//尺寸问题
void test06() {
	string* p;
	int ilenp = sizeof(p); //4（字节）
	unique_ptr<string> ps1(new string("I Love China!"));
	int ilen = sizeof(ps1);  //4（字节）

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