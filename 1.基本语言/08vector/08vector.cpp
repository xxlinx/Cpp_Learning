#include <iostream>
#include <vector>
using namespace std;



void test01() {
    vector<int> vjihe;
    struct student
    {
        int num;
    };

    vector<student> studlist;//可以
    vector<vector<string>> strchuan; 
    //可以，这个集合里的每一个元素都是一个vector对象（集合）
    //这样用有点绕，因为里边又包了一层，所以理解起来难度又加大了一些，不提倡这样用
    vector<int*> vjihe2;
    //vector<int&> vjihe3; //语法错误  里面得是一个对象，引用是一个别名
}

//定义初始化
void test02() {
    vector<string>  mystr;  //创建一个string类型的空vector对象（容器）。现在mystr里不包含任何元素
    mystr.push_back("abcd");
    mystr.push_back("def");
    //拷贝的初始化方式
    vector<string>  mystr2(mystr); //把mystr元素拷贝给了mystr2
    vector<string>  mystr3 = mystr;  //把mystr元素拷贝给了mystr3	
    //列表初始化  c++11标准中的
    vector<string> def = { "aaa","bbb","ccc" };
    //创建指定数量的元素
    vector <int> ijihe(15, -200); //创建15个int类型元素的集合，每个元素值都是-200
    vector<string> sjihe(5, "hello"); //创建5个hello	
        //不给元素初值的时候
    vector <int> ijihe2(20);   //20个元素，下标[0]--[19]，每一个元素值都为0
    vector <string> sjihe2(5); //5个元素，下标[0]-[4]，每一个元素值都为""  空的
    //多种初始化
    vector<int> i1(10); //圆括号括住的单个数字10，表示元素数量，每个元素值是缺省的0
    vector<int> i2{ 10 }; //{}括住的单个数字10，表示一个元素，该元素的值为10，所以{}括住一般里面表示的是元素内容
    vector<string> snor{ "hello" }; //一个元素，内容hello

    vector<string> s22{ 10 };//10个元素，每个元素为""，因为10这个数字不能作为string对象的内容，所以系统把它处理成了元素的数量了，不过不提倡这种写法
    vector<string> s23{ 10 ,"hello" }; //10个元素，每个元素内容都是"hello"

    vector<int> i3(10, 1); //先数量后内容：10个元素，每个元素值为1
    vector<int> i4{ 10, 1 }; //2个元素，第1个元素值为10，第2个元素值为1，等同于初始化列表
    //vector <int> i22{ "hello" }; //系统直接报编译错	
}

//vector的操作
void test03() {

    vector<int>  ivec;
    if (ivec.empty()) //条件成立
    {
        cout << " ivec为空" << endl;
    }

    ivec.push_back(1);
    ivec.push_back(2);
    for (int i = 3; i <= 100; i++)
    {
        ivec.push_back(i);
    }
    cout << ivec.size() << endl; //100
    ivec.clear();
    cout << ivec.size() << endl; //0

    ivec.push_back(1);
    ivec.push_back(2);
    cout << ivec[1] << endl; //2

}

//赋值
void test04() {

    vector <int> ivec; //先声明成空的vector对象
    ivec.push_back(1);
    ivec.push_back(2);
    for (int i = 3; i <= 100; i++)
    {
        ivec.push_back(i);
    }
    vector <int> ivec2;
    ivec2.push_back(111);
    ivec2 = ivec; //也得到了100个元素。用ivec中的内容取代了 ivec2中原有内容。上行这个111就被冲掉了
    ivec2 = { 12,13,14,15 }; //用{}中的值取代了ivec2原有值
    cout << ivec2.size() << endl; //4
}

// == !=
void test05() {
    vector <int> ivec; //先声明成空的vector对象
    ivec.push_back(1);
    ivec.push_back(2);
    for (int i = 3; i <= 100; i++)
    {
        ivec.push_back(i);
    }
    vector <int> ivec2;
    ivec2 = ivec;
    if (ivec2 == ivec)
        cout << "ivec2 == ivec" << endl;  //成立
    ivec2.push_back(12345);
    if (ivec2 != ivec)
        cout << "ivec2 != ivec" << endl; //成立	
}

//范围for的应用
void test06() {
    vector<int> vecvalue{ 1,2,3,4,5 };
    for (auto& vecitem : vecvalue) //为了修改vecvalue内部值，这里是引用，引用会绑定到元素上去，达到通过引用改变元素值的目的
        vecitem *= 2; //扩大一倍
    for (auto vecitem : vecvalue)
        cout << vecitem << endl;
}
/*
//for遍历的时候，不要改变vector的容量，否则输出混乱
void test07() {
    vector<int> vecvalue{ 1,2,3,4,5 };
    for (auto vecitem : vecvalue)
    {
        vecvalue.push_back(888); //导致输出彻底混乱
        cout << vecitem << endl;
    }
}
*/


int main()
{
    //test01();
    //test02();
    test03();
    test04();
    test05();
    test06();
    return 0;
}

