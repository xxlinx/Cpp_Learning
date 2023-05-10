#include "women.h"
#include <iostream>
Women::Women()
{
	std::cout << "执行了Women::Women()构造函数" << std::endl;
}
void Women::eat()
{
	std::cout << "女人喜欢吃面食" << std::endl;
}
Women::~Women()
{
	std::cout << "执行了Women::~Women()析构函数" << std::endl;
}