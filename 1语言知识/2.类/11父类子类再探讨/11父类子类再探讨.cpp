#include <iostream>
#include <vector>

#include "Men.h"
#include "Women.h"

using namespace std;

void test01() {
	B btest(10, 20, 50);
	btest.myinfoB(); //50
	btest.myinfoA(); //10
}


int main() {
	test01();
	return 0;
}