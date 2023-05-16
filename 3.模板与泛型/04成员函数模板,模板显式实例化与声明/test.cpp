#include <iostream>
#include <vector>
#include "ca.h"

using namespace std;

//这叫"实例化定义"，只有一个.cpp文件里这样写，编译器会为其生成代码
template  A<float>;   

template void myfunc123(int v1, int v2);

void mfunc()
{
	A<float> a(1, 2);
}
