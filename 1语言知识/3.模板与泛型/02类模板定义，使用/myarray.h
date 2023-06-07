#pragma once

//非类型模板参数的使用

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


//注意：
//1.浮点型不可作为非类型模板参数
/*
template<typename T, double size>
class myarray{...};
*/
//2.类类型不能作为非类型模板参数
/*
class a {

};
template<typename T,a size>
class myarrat{...};
*/