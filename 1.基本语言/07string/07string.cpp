#include <iostream>
#include <string> 

using namespace std;
//string 的定义初始化
void test01() {
	string s1; //默认初始化，结果是s1 = ""，代表一个空串，里面没有字符
	string s2 = "I Love China!"; //把I Love China!这个字符串内容拷贝到了s2代表的一段内存中
	string s3("I Love China!");  //这个其实跟s2的写法效果一样
	string s4 = s2; //把s2中的内容拷贝到了s4所代表的一段内存中		
	int num = 6;
	string s5(num, 'a'); //把s5初始化为连续num个字符'a'组成的字符串。不过这种方式系统内部会创建临时对象，不太推荐
	cout << "观察" << endl;
}


//string 的部分操作
void test02() {
	string s1;
	if (s1.empty()) //成立
	{
		cout << "s1为空" << endl;
	}
	cout << s1.size() << endl;    //0
	cout << s1.length() << endl;  //0
	string s2 = "我爱中国";
	cout << s2.size() << endl; //8 ，一个汉字占2个字节
	cout << s2.length() << endl; //8

	string s3 = "I Love China";
	if (s3.size() > 4)
	{
		cout << s3[4] << endl; //v
		s3[4] = 'w';
	}
	cout << s3 << endl;  //I Lowe China

	string s4 = "abcd";
	string s5 = "hijk";
	string s6 = s4 + s5;
	cout << s6 << endl; //abcdhijk

	string s7 = "abcd";
	string s8 = "de";
	s7 = s8;
	cout << s7 << endl;  //de

	string s9 = "abc";
	string s10 = "abc";
	if (s9 == s10) //条件成立
	{
		cout << "s9==s10" << endl;
	}

	s9 = "abc";
	s10 = "abC";
	if (s9 != s10) //条件成立
	{
		cout << "s9!=s10" << endl;
	}

	//s.c_str() 返回一个字符串s中的内容指针
	s9 = "abc";
	s10 = "abC";
	const char* p = s10.c_str(); //现在p指向s10里边的字符串了，可以跟踪查看
	char str[100];
	strcpy_s(str, sizeof(str), p); //字符串内容拷贝到str中
	cout << str << endl; //abC
}

void test03()
{
	string s1 = "abc";
	string s2 = "defg";
	string s3 = s1 + " and " + s2 + 'e';
	cout << s3 << endl; //abc and defge

	//string s5 = "abc" + "def"; //语法上不允许
	string s5 = "abc" + s1 + "def"; //中间夹杂一个string对象，语法上就允许
	//string s5 = "abc" + "def" + s2; //错误，看来两个字符串不能挨着相加，否则会报语法错

}

void test04() {
	string s1;
	cin >> s1;  //输入abc回车
	cout << s1 << endl; //输出abc
}

//string for 的使用
void test05() {
	string s1 = "I Love China";
	for (auto c : s1)
	{
		cout << c << endl;  //每次输出一个字符，后边跟一个换行
	}

	
	for (auto& c : s1)
	{
		c = toupper(c); //因为c是个引用，所以这相当于改变s中的值。
	}
	cout << s1 << endl; //I LOVE CHINA
}

int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	test05();
	return 0;
}