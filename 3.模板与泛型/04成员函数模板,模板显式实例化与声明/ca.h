#pragma once

//��ģ��ĳ�Ա����ģ��
template<typename C>
class A {
public:
	template<typename T2>
	A(T2 v1, T2 v2);
	//���캯��Ҳ�����Լ���ģ�����T2�����������ģ�����Cû�й�ϵ

	//��Ա����ģ��
	template <typename T>
	void myft(T tmpt)
	{
		std::cout << tmpt << std::endl;
	}
	//��ͨ��Ա����
	void myftpt() {}

	//��Ա����
	C m_ic;
};

template<typename C>//�ȸ���ģ���ģ������б����Ҫ��������
template<typename T2>//�ٸ����캯��ģ���Լ���ģ������б�
A<C>::A(T2 v1, T2 v2) {
	std::cout << v1 << " " << v2 << std::endl;
}

//����ģ��
template <typename T>
void myfunc(T v1, T v2)
{
	std::cout << v1 + v2 << std::endl;
}