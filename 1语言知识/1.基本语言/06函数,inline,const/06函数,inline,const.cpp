#include <iostream>


using namespace std;
//函数新特性

int func(int, int); //函数声明  可以没有形参的名字
int func(int a, int) {   //函数定义的时候，不用的形参可以没有名字

	return 1;
}

//后置返回类型
auto func123(int a, int b) -> void;  //函数声明
auto func123(int a, int b) -> void   //函数定义
{
	return;
}

void test01() {
	func(12, 13);  //调用的时候不可以省略
}


//内联函数 inline
//加在函数定义前， 可不是加在函数声明前 

/*---------------------------*/
//内联函数的定义也是放在头文件中
/*---------------------------*/
inline int myfunc(int testv) {
	return 1;
}
void test02() {
	myfunc(2);
}

//const
void test03() {
	{
		//const char *
		{
			char str[] = "I Love China!";
			char* p;
			p = str;
			*p = 'Y';
			p++;    //p可以指向不同的位置，只要这些位置的内存归我们管即可
		}
		{
			char str[] = "I Love China!";
			const char* p;
			//char const * p;  //两个等价
			p = str;
			//*p = 'Y'; //错误，p指向的内容不能通过p来修改（p所指向的目标，那个目标中的内容不能通过p来改变）
			str[0] = 'Y'; //正确
			p++;
		}

		//char * const  常量指针
		{
			char str[] = "I Love China!";
			char* const p = str; //这种情况 定义的时候必须初始化
			//p++; //这不可以，p指向一个内容后，不可以再指向其他内容(p不可以指向不同目标)
			*p = 'Y'; //但可以修改指向的目标中的内容		
		}

		//const char * const   或者  char const * const 
		//指向不可变，指向的内容不可变



	}

}

//函数形参带有const
struct student {
		int num; 
	};
void fs(student& stu)
{
	stu.num = 1010;
}
void fs2(const student& stu) {
	//这里就不可修改形参的值
	//stu.num = 2023;   error
}

void test04() {
	
	student abc;
	abc.num = 100;
	fs(abc);
	cout << abc.num << endl;

}

int main() {
	test01();
	test02();
	test03();
	return 0;
}