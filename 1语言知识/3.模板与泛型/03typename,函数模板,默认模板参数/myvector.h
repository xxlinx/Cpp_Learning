#pragma once
//自己的容器类模板
template<typename T> //名字为T的模板参数，用来表示myvector这个容器所保存的元素类型
class myvector
{
public:
	typedef  T* myiterator;    //迭代器  类型成员

public:
	myvector();               //构造函数
	//myvector& operator=(const myvector&);   //赋值运算符重载,在类模板内部使用模板名myvector并不需要提供模板参数,当然提供也行,可以写成myvector<T>
	myvector<T>& operator=(const myvector<T>&);   //赋值运算符重载

public:
	//void myfunc() {};
	void myfunc();

public:
	//迭代器接口
	myiterator mybegin();     //迭代器起始位置
	myiterator myend();       //迭代器结束位置
};

template<typename T>
void myvector<T>::myfunc()
{

}
template<typename T>
myvector<T>::myvector()
{
}

template<typename T>
myvector<T>& myvector<T>::operator=(const myvector<T>&) //第一个<T>表示返回的是一个实例化了的myvector，第三个<T>不是必加
{
	//......
	return *this;
}

template<typename T>
//typename必须性
//返回的是一个类型成员，只在定义类模板的时候才用到这个东西
//这里的typename 不能换成 class
typename myvector<T>::myiterator myvector<T>::mybegin()
{
	//.....
}