#include <iostream>
#include "project1.h"
#include "project2.h"

using namespace lisi;  //这个文件，调用lisi 的函数都不用命名空间
//要避开二义性


int main() {
	std::cout << "hello world" <<std::endl;
	lisi::radius2();
	zhangsan::radius();

	radius();
	int value1 = 0, value2 = 0;
	std::cin >> value1 >> value2;
	std::cout << value1 << "与" << value2 << "和为" << value1 + value2 << std::endl;
	return 0;
}