#include <iostream>
#include <vector>

#include "myvector.h"
#include "myarray.h"

using namespace std;

void test01() {
	myvector<int> tmpvec;  //实例化模板类  T被替换成了int
	myvector <double> tmpvec2; //T被替换成了double
	myvector <string> tmpvec3; //T被替换成了string

}
void test02() {
	myarray<int> tmparr;
	tmparr.myfunc(); //10

	myarray<int, 50> tmparr2;
	tmparr2.myfunc(); //50

}

int main() {
	test01();
	test02();
	return 0;
}