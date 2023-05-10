#include <iostream>
#include <vector>

#include "Men.h"
#include "Women.h"
#include "func.h"

#include "A.h"
#include "B.h"
using namespace std;

//友元函数
void test01() {
	Men men;
	func(men);
}

//友元类
void test02() {
	A a;
	B b;
	b.callBAF(3, a); //3
}

//友元成员函数
void test03() {

}

int main() {


	return 0;
}