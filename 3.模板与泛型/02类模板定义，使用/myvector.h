#pragma once


//自己的容器类模板
template<typename T>//名字为T的模板参数，用来表示myvector这个容器所保存的元素类型
class myvector {
public:
	typedef T* myiterator;   //迭代器 指针

public:
	myvector();		//构造函数

	//myvector& operator=(const myvector&);   //赋值运算符重载,在类模板内部使用模板名myvector并不需要提供模板参数,当然提供也行,可以写成myvector<T>
	myvector<T>& operator=(const myvector<T>&);   //赋值运算符重载

public:
	//void myfunc() {};
	//成员函数的函数体 如果写在定义这里面，就隐式的声明为内联函数,不建议
	void myfunc();


public:
	//迭代器接口
	myiterator mybegin();//迭代器起始位置
	myiterator myend();       //迭代器结束位置
};

//模板的普通函数定义
template<typename T>
void myvector<T>::myfunc() {

}

//模板的构造函数
template<typename T>
myvector<T>::myvector() {

}


//类模板名字的使用
//模板的重载
template<typename T>
//第一个<T>表示返回的是一个实例化的myvector
myvector<T>& myvector<T>::operator = (const myvector <T>&) {
	//...
	return *this;
}