#include <iostream>
#include <vector>

using namespace std;

class CTempValue {
public:
	int val1;
	int val2;
public:
	CTempValue(int v1 = 0, int v2 = 0); //构造函数
	CTempValue(const  CTempValue& t) : val1(t.val1), val2(t.val2) //拷贝构造函数
	{
		cout << "调用了拷贝构造函数!" << endl;
	}
	virtual ~CTempValue() //析构函数
	{
		cout << "调用了析构函数!" << endl;
	}

	CTempValue& operator=(const CTempValue& tmpv)
	{
		//不能用初始化列表，只有构造函数才有初始化列表
		val1 = tmpv.val1;
		val2 = tmpv.val2;
		cout << "调用了拷贝赋值运算符!" << endl;
		return *this;
	}
public:
	//int Add(CTempValue tobj); //普通成员函数
	int Add(CTempValue& tobj); //普通成员函数
};

CTempValue::CTempValue(int v1, int v2) :val1(v1), val2(v2)
{
	cout << "调用了构造函数!" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;
}
//int CTempValue::Add(CTempValue tobj)
//{
//	int tmp = tobj.val1 + tobj.val2;
//	tobj.val1 = 1000;            //这里修改对外界没什么影响
//	return tmp;
//}
int CTempValue::Add(CTempValue& tobj)
{
	int tmp = tobj.val1 + tobj.val2;
	tobj.val1 = 1000;            //这里修改对外界直接产生影响
	return tmp;
}

//统计字符ch在字符串strsource里出现的次数，把次数返回去
int calc(const string& strsource, char ch)
{
	const char* p = strsource.c_str();
	int icount = 0;
	//....具体的统计代码
	return icount;
}
CTempValue Double(CTempValue& ts)
{
	CTempValue tmpm; //这里会消耗一次构造和一次析构函数的调用
	tmpm.val1 = ts.val1 * 2;
	tmpm.val2 = ts.val2 * 2;
	return tmpm;  //断点到这里，会发现调用了拷贝构造函数和析构函数，这表示生成了临时对象
}




//1.以传值的方式给函数传递参数
void test01() {
	CTempValue tm(10, 20);    //调用构造函数
	int Sum = tm.Add(tm);     //这会导致拷贝构造函数的执行
	cout << "Sum = " << Sum << endl;
	cout << "tm.val1 = " << tm.val1 << endl;
}
//2.类型转换生成的临时对象
void test02() {

	CTempValue sum;
	sum = 1000;
		/*调用了构造函数!
		val1 = 0
		val2 = 0
		调用了构造函数!
		val1 = 1000
		val2 = 0
		调用了析构函数!
		调用了析构函数!*/
}
void test03() {
	CTempValue sum = 1000;
		//调用了构造函数!
		//val1 = 1000
		//val2 = 0
		//调用了析构函数!
}
void test04() {
	char mystr[100] = "I love China,oh,yeah!";
	int result = calc(mystr, 'o');
}

//3.函数返回对象的时候
void test05() {
	CTempValue ts1(10, 20);
	Double(ts1); //
		//调用了构造函数!
		//val1 = 10
		//val2 = 20
		//调用了构造函数!
		//val1 = 0
		//val2 = 0
		//调用了析构函数!
		//调用了析构函数!

}
//4.类外的运算符重载
class mynum
{
public:
	mynum(int x = 0, int y = 0) :num1(x), num2(y) //构造函数
	{
		cout << "调用了构造函数!" << endl;
	}

	mynum(const  mynum& t)  //拷贝构造函数
	{
		cout << "调用了拷贝构造函数!" << endl;
	};
	virtual ~mynum() //析构函数
	{
		cout << "调用了析构函数!" << endl;
	};


public:
	int num1;
	int num2;
};
//优化前
//mynum operator+(mynum& tmpnum1, mynum& tmpnum2) 
//{
//	mynum result;
//	result.num1 = tmpnum1.num1 + tmpnum2.num1;
//	result.num2 = tmpnum1.num2 + tmpnum2.num2;
//	return result;
//}

//优化后
mynum operator+(mynum& tmpnum1, mynum& tmpnum2)
{
	return mynum(tmpnum1.num1 + tmpnum2.num1, tmpnum1.num2 + tmpnum2.num2);
}

void test06() {
	mynum tm1;
	tm1.num1 = 10;
	tm1.num2 = 100;

	mynum tm2;
	tm2.num1 = 20;
	tm2.num2 = 200;

	mynum tm3 = tm1 + tm2;

		//调用了构造函数!
		//调用了构造函数!
		//调用了构造函数!
		//调用了析构函数!
		//调用了析构函数!
		//调用了析构函数!
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