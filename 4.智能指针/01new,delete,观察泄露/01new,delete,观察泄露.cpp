#include <iostream>
#include <vector>

using namespace std;   //后面再使用诸如std::cout时就可以简写成cout了；

class A
{
public:
	A()
	{
		cout << "A" << endl;
	}
	int m_i;
};


int main()
{

	{
		int* pointi = new int; //pointi指向一个int对象
		string* mystr = new string;
	}
	{
		int* pointi = new int(100); //跟踪调试，指针指向的值变成了100
		string* mystr2 = new string(5, 'a'); //生成5个a的字符串，调用的是符合给进去的参数的string构造函数来构造出合适的字符串内容
		vector<int>* pointv = new vector<int>{ 1,2,3,4,5 }; //一个容器对象，里面有5个元素，分别是1,2,3,4,5
	}
	{
		string* mystr2 = new string(); //“值初始化”，感觉和string *mystr = new string;效果一样，总之最终字符串内容为空（""）
		int* pointi3 = new int(); //值被初始化为0， 这个()加与不加确实不一样，只有加了()值才会被初始化为0

	}
	{
		A* pa1 = new A;
		A* pa2 = new A();
	}
	{

		string* mystr2 = new string(5, 'a');
		const char* p = mystr2->c_str();
		auto mystr3 = new auto(mystr2); //注意这种写法，mystr3会被推断成string *类型
		//string** mystr3 = new (string *)(mystr2);		
		delete mystr2;
		delete mystr3;
	}
	{
		const int* pointci = new const int(200); //new后面这个const可以不写，似乎都差不多；当然const对象不能修改其值
		//*pointci = 300;  //不合法		
		cout << "断点放到这里方便观察" << endl;
		delete pointci; //new的内存不能忘记释放
	}
	{
		char* p = nullptr;
		delete p;
		delete p;
	}
	{
		int i;
		int* p = &i;
		//delete p; //不是new出来的不能delete，否则编译不报错，但执行时会出现异常
	}
	{
		int* p = new int();
		int* p2 = p;
		delete p2; //没问题
		//delete p; //异常，因为p和p2指向同一块内存，该内存已经通过delete p2释放了，所以两个指针指向同一块内存这种，也比较麻烦，释放了p就不能再释放p2，释放了p2就不能再释放p，换句话说，如果释放了p2，也就不能再使用p

	}
	{
		const int* pci = new const int(300);
		delete pci; //可以delete const对象
	}
	{
		int* pci = new  int(300);
		delete pci; //可以delete const对象
		//*pci = 900;

	}

	return 0;
}
