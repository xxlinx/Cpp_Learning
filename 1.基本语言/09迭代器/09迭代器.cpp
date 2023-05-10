#include <iostream>
#include <vector>
using namespace std;

//迭代器
void test01() {
	vector<int> iv = { 100,200,300 }; //定义一个容器
	vector<int>::iterator iter; //定义迭代器，也必须是以vector<int>开头

	iter = iv.begin();//如果容器中有元素，则begin返回的迭代器，指向的是容器中的第一个元素
	//这里相当于iter代表着元素iv[0]

	iter = iv.end(); //end返回的迭代器指向的并不是末端元素，而是末端元素的后面，这个后面怎么理解？
	//就理解成end指向的是一个不存在的元素

	//空容器的话，begin == end
	vector<int> iv2;
	vector<int>::iterator iterbegin = iv2.begin();
	vector<int>::iterator iterend = iv2.end();
	if (iterbegin == iterend) //条件成立
	{
		cout << "容器为空" << endl;
	}

}

void test02() {
	//正方向迭代
	vector<int> iv = { 100,200,300 }; //定义一个容器		
	for (vector<int>::iterator iter = iv.begin(); iter != iv.end(); iter++) //经典传统用法，这里用++、!=等运算符来对迭代器进行操作
	{
		cout << *iter << endl;
	}
	//反方向迭代   注意也是++  不是--
	vector<int> iv2 = { 100,200,300 };
	for (vector<int>::reverse_iterator riter = iv2.rbegin(); riter != iv2.rend(); riter++)
	{
		cout << *riter << endl;
	}
}

//迭代器运算符
void test03() {
	vector<int> iv = { 100,200,300 }; //定义一个容器
	vector<int>::iterator iter;
	for (iter = iv.begin(); iter != iv.end(); ++iter)
	{
		cout << *iter << endl;
	}
	// *iter 返回*iter 所指向元素的引用 要求所指向的是有效的容器元素
	//++iter; //已经指向end的迭代器，不能再++，否则运行时报错
	--iter; //等价于iter--
	cout << *iter << endl;  //300

}

void test04() {
	struct student
	{
		int num;
	};
	vector <student> sv;
	student mystu;
	mystu.num = 100;
	sv.push_back(mystu); //把对象mystu复制到了sv容器中(是复制，此时mystu和容器sv中的student没有直接关系)
	mystu.num = 200;     //在这里修改mystu中的内容不会对容器中元素值造成影响，因为容器中内容是复制进去的
	vector<student>::iterator iter;
	iter = sv.begin(); //指向第一个元素
	cout << (*iter).num << endl;  //100，注意引用方法：*iter是个结构变量，所以用.成员来引用成员
	cout << iter->num << endl;    //100，注意引用方法：iter想象成一个指针，所以用->引用成员

}

//const_iterator 迭代器    
//该迭代器指向的元素的值 不可改变,  迭代器本身是可以变换的,可以改变其指向的元素
void test05() {
	vector<int> iv = { 100,200,300 }; //定义一个容器
	vector<int>::const_iterator iter;
	for (iter = iv.begin(); iter != iv.end(); ++iter)
	{
		//*iter = 4; //不可以
		cout << *iter << endl; //可以读，常量迭代器也可以正常的从容器中读元素值
	}	
}

void test06() {
	const vector<int> iv = { 100,200,300 }; //定义一个容器,注意前面的const
	vector<int>::const_iterator iter;
	for (iter = iv.begin(); iter != iv.end(); ++iter) 
	{
		cout << *iter << endl;
	}
	//这里begin和end返回的是const_iterator，
	//返回的是iterator还是const_iterator，取决于这个容器对象是否是const对象
}
//cbegin  cend  c++11的两个新函数  返回的都是常量迭代器  不可通过常量迭代器来修改值
void test07() {
	vector<int> iv = { 100,200,300 }; //定义一个容器		
	for (auto iter = iv.cbegin(); iter != iv.cend(); ++iter)
	{
		//*iter = 58;  //错误，不能给常量赋值，这说明cbegin返回的是常量迭代器
		cout << *iter << endl;
	}
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