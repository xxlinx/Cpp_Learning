#ifndef __MYCLASS_H__
#define __MYCLASS_H__

/****   ģ��������֯�ṹ   ****/

template <typename T>
class MYClass {
public:
	void func();
};

template <typename T>
//void MYClass::func()
void MYClass<T>::func() {
	std::cout << "MYClass::func��Ա����ִ����!" << std::endl;
}

//-------------------------
// ������ػ��汾���ػ��汾Ҫ���ڷ����汾֮��
//�ػ��汾
template <>
class MYClass<int> {
public:
	void func();
};
void MYClass<int>::func() {//���е�ǰ�治��Ҫtemplate <>
	std::cout << "MYClass<int>::func��Ա����ִ����!" << std::endl;
}

#endif

