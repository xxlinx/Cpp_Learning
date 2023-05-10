#include <iostream>
#include <vector>

using namespace std;

//c++ 一条表达式，要么是左值，要么就是右值，不存在两者都是的情况。
//一个左值可能同时具有左值属性和右值属性
void test01() {
	int a;
	printf("%d\n", a = 4); //4
	//打印的是a代表的值
	(a = 4) = 8;
	//最终 a = 8
}
void test02() {
	int a = 5;  //变量就是一个左值
	&a; //&肯定要作用于一个左值对象。但它返回的是个地址（指针），这个指针是个右值比如0x008ffdd4，比如&123这肯定不成立把

}
void test03() {
	string abc = "I Love China!";
	abc[0];

	vector<int>::iterator iter;  //迭代器类似指针变量
	//...
	//iter++; iter--;
}
//通过一个运算符在一个字面值上能不能操作，我们就能判断运算符是否需要左值
//左值代表一个地址，所以左值表达式的求值结果，就是一个对象，就得有地址。


//引用分类
void test04() {
	//1.左值引用
	int value = 10;
	int& refval = value; //value的别名是refval， &在此不是求地址运算，而是起标识作用（标识是个引用）
	refval = 13;		 //等价于value=13;	

	//2不希望改变值的对象  const 引用
	const int& refval2 = value;
	//refval2 = 18;//错，编译器提示：表达式必须是可修改的左值

	//3右值引用 目的   
	//两个&
	int&& refrightvalue = 3; //绑定到一个常量
	refrightvalue = 5; //还可以修改值
}
//左值引用
void test05() {

	int a = 1;
	int& b{ a };  //b绑到a，当然可以
	//int& c;       //不可以，引用必须要初始化
	//int& c = 1;   //不可以，要绑到左值上，不能绑定到右值上
	const int& c = 1; //可以，const引用可以绑定到右值上，所以const引用可以说比较特殊

	int tempvalue = 1; //可以把tempvalue看成一个临时变量
	const int& c2 = tempvalue;
}
//右值引用
void test06() {
	string strtest{ "I love China!" };
	string& r1{ strtest };       //可以，左值引用绑定左值
	//string &r2{"I love China!"};  //不可以，左值 引用不能绑定到临时变量上
	const string& r3{ "I love China!" };  //可以，创建个临时变量，绑定到左值r3上,const引用不但可以绑定到右值，还可以执行到string的隐式类型转换并将所得到的值放到string临时变量中
	//string &&r4{ strtest };      //不可以，右值 引用不能绑到左值上去
	string&& r5{ "I love China!" }; //可以，绑定一个临时变量，临时变量内容是I Love China!
	int i = 10;
	int& ri = i;               //可以，左值引用，没问题
	//int &&ri2 = i;           //不可以，不能将一个右值引用绑定到一个左值上
	//int &ri3 = i * 100;      //不可以，左值引用不能往右值上绑，i*100是右值；
	const int& ri4 = i * 100;  //可以，const引用可以绑定到右值
	int&& ri5 = i * 1000;      //可以，乘法结果是右值


}

//std::move
//就是把一个左值强制转换成一个右值
void test07() {
	int i = 10;
	//int&& ri20 = i; //不可以，因为i是左值，不能绑到右值引用上去
	int&& ri20 = std::move(i); //可以，所以move的能力是把一个左值转换为一个右值
	ri20 = 15; //可以，现在ri20就代表i了，执行后i的值也变成15了

	int&& ri6 = 100;  //可以
	//int &&ri8 = ri6; //不可以，ri8是右值引用，但ri6是左值
	int&& ri8 = std::move(ri6); //可以了,所以move的能力是 把一个左值转换为一个右值
	ri6 = 68;   //可以，执行后ri8也跟着变成68了
	ri8 = 52;   //可以，执行后ri6也跟着变成52了

	string st = "I love China!";
	const char* p = st.c_str();

	string def = std::move(st);//string里的移动构造函数把st的内容转移到了def中去。
	//这个转移并不是std::move干的	 这里st的值就变成空了
	//这个 = 会导致string 类型里的 移动构造函数,把st的内容转到def,并把自己值清空了
	const char* q = def.c_str();  //st def 的地址是不一样，开辟新内存来做的
}
void test08() {
	string st = "I love China!";
	//std::move(st); //执行后，st没变为空，其实是值压根没变，这更进一步证明前面范例中的st变为空是string这个类中的移动构造函数所致
	string&& def = std::move(st); //这个可不会触发string的移动构造函数，st值不会变为空，这行代码只是将st转成右值并绑到def上
	st = "abd"; //执行后def也就变成"abd"了
	def = "cde"; //执行后def也变成"cde"了

}


int main() {

	test01();
	test02();
	test03();
	test04();
	test05();
	test06();
	test07();
	test08();
	return 0;
}