#pragma once


//�Լ���������ģ��
template<typename T>//����ΪT��ģ�������������ʾmyvector��������������Ԫ������
class myvector {
public:
	typedef T* myiterator;   //������ ָ��

public:
	myvector();		//���캯��

	//myvector& operator=(const myvector&);   //��ֵ���������,����ģ���ڲ�ʹ��ģ����myvector������Ҫ�ṩģ�����,��Ȼ�ṩҲ��,����д��myvector<T>
	myvector<T>& operator=(const myvector<T>&);   //��ֵ���������

public:
	//void myfunc() {};
	//��Ա�����ĺ����� ���д�ڶ��������棬����ʽ������Ϊ��������,������
	void myfunc();


public:
	//�������ӿ�
	myiterator mybegin();//��������ʼλ��
	myiterator myend();       //����������λ��
};

//ģ�����ͨ��������
template<typename T>
void myvector<T>::myfunc() {

}

//ģ��Ĺ��캯��
template<typename T>
myvector<T>::myvector() {

}


//��ģ�����ֵ�ʹ��
//ģ�������
template<typename T>
//��һ��<T>��ʾ���ص���һ��ʵ������myvector
myvector<T>& myvector<T>::operator = (const myvector <T>&) {
	//...
	return *this;
}