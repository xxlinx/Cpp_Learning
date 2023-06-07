#include <iostream>
using namespace std;

void myfunc(void* ptmp)
{
    printf("myfunc(void *ptmp)\n");
}
void myfunc(int tmpvalue)
{
    printf("myfunc(int tmpvalue)\n");
}


int main()
{
    //范围for 用于遍历一个序列
    {
        int v[]{ 12,13,14,16,18 };

        //数组v中每个元素，依次放入x并打印x值。
        //这里相当于把v的每个元素值拷贝到x中，然后打印x值
        //for (auto x : v) 
        for (auto& x : v) //使用引用的方式，避免数据的拷贝动作   x的地址每一轮循环都在变
        {
            cout << x << endl;
        }
        for (auto x : { 11,34,56,21,34,34 }) //这是个元素序列，for就是应用于任意的这种元素序列
        {
            cout << x << endl;
        }
    }

    //内存分配问题
    {
        //c语言中 malloc 和free 是函数 后面是有 ( ) 的
        {
            int* p = NULL;  //c的空指针
            p = (int*)malloc(10 * sizeof(int)); //分配了40字节
            if (p != NULL)
            {
                *p = 5;  //这种写法其实只会用到分配的40字节中的4个字节
                cout << *p << endl;
                free(p); //千万不要忘记，否则就是内存泄漏。如果泄露多了，程序就会崩溃
            }
        }
        char* point = NULL;
        point = (char*)malloc(100 * sizeof(char)); //100个位置
        if (point != NULL)
        {
            strcpy_s(point, 20, "hello world!");  //strcpy不安全，拷贝越界把不该冲的内存就给冲了
            //第二个参数是该地址能容纳的元素个数。
            //strcpy_s，如果拷贝越界会发出警告窗口并停止程序运行（用搜索引擎学习）
            cout << point << endl;
            free(point);
        }

        {
            int* p = (int*)malloc(sizeof(int) * 100); //分配可以放得下100个整数的内存空间。 
            if (p != NULL) 
            {
                int* q = p;
                *q++ = 1;// 自增运算符和指针运算符优先级相同，并且是自右至左结合的，所以等价于
				               //*(q++); ++在后边是先用后加，所以 整个的作用是得到q指向的变量的值(*q)，
                               //然后再使q指针自加1，指向下一个数组元素。
                *q++ = 5;
                cout << *p << endl;   //1
                cout << *(p + 1) << endl;  //5
                free(p);
            }
        }

        //c++ 版本 new delete 是运算符，不是函数
        {
            {
                //开辟一个存放整数的存储空间,返回一个指向该存储空间的地址。将一个int类型的地址赋给整型指针myint
                int* myint = new int;
                if (myint != NULL)//其实如果new失败可能不会返回NULL，而是直接报异常
                {
                    *myint = 8; //*myint代表指针指向的变量
                    cout << *myint << endl; //8
                    delete myint; //释放
                }
            }
            {
                //开辟一个大小为100的整型数组空间
                int* a = new int[100]; 
                if (a != NULL)
                {
                    int* p = a;
                    *p++ = 12;
                    *p++ = 18;
                    cout << *a << endl;      //12
                    cout << *(a + 1) << endl;  //18

                    delete[] a;    //释放int数组空间  带有 [ ] 也要配对使用
                    //new时用了[],delete就要用[]，否则回收的内存就是第一个数组元素空间而不是整个数组
                       //[]起了回收整个数组的作用。
                   //delete中这个[]这里不用写数组中元素个数，保持空着，系统有办法知道这个数组大小，写了数字也没用会被系统忽略.
                }
            }

            {
                int* myint = new int(18);  //同时将整数空间赋值为18
                if (myint != NULL)
                {
                    cout << *myint << endl;// 18
                    *myint = 8; //*myint代表指针指向的变量
                    cout << *myint << endl;//8
                    delete myint;  //释放
                }
            }
            
        }
    }

    //nullptr c++11 的关键字 代表 空指针
    {
        {
            char* p = NULL;  //NULL实际就是0
            char* q = nullptr;
            int* a = nullptr;
            if (p == nullptr) //条件成立
            {
                cout << "nullo" << endl;
            }
            myfunc(NULL); //调用void myfunc(int tmpvalue)
            myfunc(nullptr);//调用void myfunc(void* ptmp) 
        }
        {
            //nullptr NULL 是不同的类型
            cout << typeid(NULL).name() << endl;   //int 
            cout << typeid(nullptr).name() << endl;  //std::nullptr_t		
        }

    }


    return 0;
}

