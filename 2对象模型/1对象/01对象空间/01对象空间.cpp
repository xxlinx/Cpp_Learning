#include <iostream>
class A{
public:
	void func() {};
	void func1() {};
	void func2() {};

	int ab;
};

int main() {
	{
		std::cout << "Hello World!\n";
		printf("很高兴我们大家一起学习!\n");
		printf("35+48的值是%d\n", 35 + 48);
	}

	{
		//char aaa[1000] = "safasdfa\0def";
		//printf(aaa);

	}
	//{
	//	A a;
	//	//sizeof()：返回一个对象所占的字节数字
	//	int ilen = sizeof(a); //等价于sizeof(A)，结果为1
	//	printf("ilen = %d\n", ilen); //ilen = 1
	//}
	//{
	//	A a;	
	//	int ilen = sizeof(a); 	
	//	a.ab = 'c';
	//	printf("ilen = %d\n", ilen); //ilen = 1
	//}
	{
		A a;
		int ilen = sizeof(a);
		a.ab = 12;
		printf("ilen = %d\n", ilen);
	}
	return 0;

}