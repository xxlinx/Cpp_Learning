#include <iostream>
#include <vector>

using namespace std;

void test01() {
	unique_ptr<int> pi; //可以指向int对象的一个空指针
	if (pi == nullptr)//条件成立
	{
		cout << "pi目前还是空指针" << endl;
	}
	unique_ptr<int> pi2(new int(105)); //定义该智能指针时，直接把它绑定到一个new返回的指针上，此时pi2就指向一个值为105的int对象了	
}
void test02() {
	unique_ptr<int> p1 = std::make_unique<int>(100); //make_unique c++14里才提供
	auto p2 = std::make_unique<int>(200); //可以用auto简写
	shared_ptr<int> p3(new int(100)); //int重复两次。而且不能使用auto来简写，不然p3就变成普通指针(裸指针)了而不是智能指针

}

//unique_ptr 不支持复制的操作
//移动语义
void test03() {
	unique_ptr<string> ps1(new string("I Love China!"));
	unique_ptr<string> ps3 = std::move(ps1);  //转移后ps1为空了，ps3指向原来ps1所指

}
//release 成员函数
void test04() {
	//将所有权从ps1转移（移动）给ps2：
	unique_ptr<string> ps1(new string("I Love China!"));
	unique_ptr<string> ps2(ps1.release());
	if (ps1 == nullptr)//条件成立
	{
		cout << "ps1被置空" << endl;
	}
	//ps2.release();   //这会导致内存泄漏  需要有指针接住
	string* tempp = ps2.release(); //或者写成auto tempp = ps.release();
	delete tempp;
}
//rest 成员函数
//无参数
void test05() {

	unique_ptr<string> prs(new string("I Love China!"));
	prs.reset(); //当reset()不带参数时，释放prs指向的对象，并将prs置空
	if (prs == nullptr)//条件成立
	{
		cout << "prs被置空" << endl;
	}
}
//有参数
void test06() {
	unique_ptr<string> prsdc(new string("I Love China 1!"));
	unique_ptr<string> prsdc2(new string("I Love China 2!"));
	//当prsdc2.reset(......)中带参数时，释放prsdc2原来所指向的内存，让prsdc2指向新内存
	prsdc2.reset(prsdc.release());  //reset释放原来prsdc2指向的对象内存，让prsdc2指向prsdc所指向的内存，同时prsdc被置空

	prsdc2.reset(new string("I Love China!")); //reset参数可以是个裸指针，reset释放原来prsdc2指向的对象内存，让prsdc2指向新new出来的string		

}

// =nullptr   不仅是指针置空
void test07() {
	unique_ptr<string> ps1(new string("I Love China!"));
	ps1 = nullptr; //释放ps1指向的对象，并将ps1置空

}

//指向一个数组
void test08() {
	std::unique_ptr<int[]> ptrarray(new int[10]); //前面带上空括号[]表示是数组，下面行才可以用[下标]来引用数组元素
	ptrarray[0] = 12; //数组提供索引运算符[]
	ptrarray[1] = 24;
	ptrarray[9] = 124;  //能访问的下标是0-9，不要超过这个范围，否则可能导致程序异常		

}
class A
{
public:
	A(){
	}
	~A() //有自己的析构函数
	{
	}
};
void test09() {
	//std::unique_ptr<A> ptrarray(new A[10]); 
	//一个类A的数组，而且类A有析构函数，但前面的<>中没有使用A[]，就报异常。原因在16.2.1的5中已经解释了
	
	std::unique_ptr<A[]> ptrarray(new A[10]); 
	//这个写法没有问题，也不会泄露内存，注意前面的<>中正常的书写为A[]
}
//get 成员函数
void test10() {
	unique_ptr<string> ps1(new string("I Love China!"));
	string* ps = ps1.get();
	const char* p1 = ps->c_str();
	*ps = "This is a test very good!";
	const char* p2 = ps->c_str();  //调试观察不难发现p1和p2是不同的内存地址，这是string内部工作机制决定的
}
// * 解引用
void test11() {
	unique_ptr<string> ps1(new string("I Love China!"));
	const char* p1 = ps1->c_str();
	*ps1 = "This is a test very good!";
	const char* p2 = ps1->c_str();//调试观察不难发现p1和p2是不同的内存地址，这是string内部工作机制决定的
	std::unique_ptr<int[]> ptrarray(new int[10]); //对于定义的内容是数组，是没有*解引用运算符的
	//*ptrarray; //错误
}

//swap 成员函数
void test12() {
	unique_ptr<string> ps1(new string("I Love China1!"));
	unique_ptr<string> ps2(new string("I Love China2!"));
	std::swap(ps1, ps2); //用全局函数也可以
	ps1.swap(ps2); //也可以

}

//智能指针名字作为判断条件
void test13() {
	unique_ptr<string> ps1(new string("I Love China1!"));
	//若ps1指向一个对象，则为true
	if (ps1) //条件成立
	{
		//执行
		cout << "ps1指向了一个对象" << endl;
	}
}

//转换成shared_ptr 
auto myfunc()
{
	return unique_ptr<string>(new string("I Love China!")); //这就是一个右值（短暂的临时对象，都是右值，14.12.4中详细说过）																
}
void test14() {
	shared_ptr<string> pss1 = myfunc(); //可以成功，引用计数为1
	cout << "调试断点" << endl;
}
void test15() {
	unique_ptr<std::string> ps(new std::string("I Love China!"));
	shared_ptr<string> ps2 = std::move(ps); //执行后ps为空，ps2是shared_ptr且引用计数为1		
	cout << "调试断点" << endl;
}

int main() {

	test01();
	//...
	return 0;
}