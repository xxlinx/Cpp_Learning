#pragma once

//������ģ�������ʹ��

template<typename T, int size = 10>
class myarray {
public:
	void myfunc();
private:
	T arr[size];
};

template<typename T, int size>
void myarray<T, size>::myfunc()
{
	std::cout << size << std::endl;
	return;
}


//ע�⣺
//1.�����Ͳ�����Ϊ������ģ�����
/*
template<typename T, double size>
class myarray{...};
*/
//2.�����Ͳ�����Ϊ������ģ�����
/*
class a {

};
template<typename T,a size>
class myarrat{...};
*/