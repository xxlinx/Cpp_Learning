#include <iostream>
#include <vector>

using namespace std;

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
void test01() {
	A* pa = new A(); //类A的构造函数被调用
	delete pa; //类A的析构函数被调用

	void* myorgpoint = operator new(100); //分配100字节内存，一般没人这样做

	int* p = new int;  //分配出去4字节
	delete p;         //回收内存的时候，编译器怎样知道要回收4字节？这就是new内部有记录机制，它分配出去多少，它会找个地方记录下来，回收的时候就按这个字节数回收

}

//shaerd_ptr基础
//make_shared函数
void test02() {
	shared_ptr<int> pi(new int(100));//pi指向一个值为100的int型数据
	//shared_ptr<int> pi2 = new int(100); 
	//这个写法不行，智能指针是explicit，是不可以进行隐式类型转换的，必须用直接初始化形式。而带等号一般都表示要隐式类型转换的
	shared_ptr<int> p2 = std::make_shared<int>(100); //这个shared_ptr指向一个值为100的整型的内存 ，类似int *pi = new int(100);
	shared_ptr<string> p3 = std::make_shared<string>(5, 'a'); //5个字符a,类似于string mystr(5, 'a');，注意到，make_shared后圆括号里的参数的形式取决于<>中的类型名，此时这些参数必须和string里的某个构造函数匹配

	shared_ptr<int> p4 = make_shared<int>(); //p4指向一个int，int里保存的值是0；这个就是值初始化
	p4 = make_shared<int>(400); //p4释放刚才的对象，重新指向新对象

	auto p5 = std::make_shared<string>(5, 'a'); //用auto保存make_shared结果，写法上比较简单

	cout << "测试" << endl;
}


int main() {

	test01();
	test02();

	return 0;
}