#pragma once
//�Լ���������ģ��
template<typename T> //����ΪT��ģ�������������ʾmyvector��������������Ԫ������
class myvector
{
public:
	typedef  T* myiterator;    //������  ���ͳ�Ա

public:
	myvector();               //���캯��
	//myvector& operator=(const myvector&);   //��ֵ���������,����ģ���ڲ�ʹ��ģ����myvector������Ҫ�ṩģ�����,��Ȼ�ṩҲ��,����д��myvector<T>
	myvector<T>& operator=(const myvector<T>&);   //��ֵ���������

public:
	//void myfunc() {};
	void myfunc();

public:
	//�������ӿ�
	myiterator mybegin();     //��������ʼλ��
	myiterator myend();       //����������λ��
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
myvector<T>& myvector<T>::operator=(const myvector<T>&) //��һ��<T>��ʾ���ص���һ��ʵ�����˵�myvector��������<T>���Ǳؼ�
{
	//......
	return *this;
}

template<typename T>
//typename������
//���ص���һ�����ͳ�Ա��ֻ�ڶ�����ģ���ʱ����õ��������
//�����typename ���ܻ��� class
typename myvector<T>::myiterator myvector<T>::mybegin()
{
	//.....
}