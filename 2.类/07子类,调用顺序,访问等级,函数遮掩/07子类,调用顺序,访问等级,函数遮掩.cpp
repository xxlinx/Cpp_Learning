#include <iostream>
#include <vector>

#include "Men.h"
using namespace std;

int main() {

	//函数遮蔽
	{
		Men men;
		men.samenamefunc(1); //执行子类的samenamefunc函数，虽然父类也有带一个参数的该函数，但子类函数还是覆盖了父类同名函数
		men.samenamefunc();  //执行父类的不带参函数的samenamefunc函数
			/*执行了Human::Human()构造函数
			执行了Men::Men()构造函数
			执行了Human::samenamefunc()
			执行了Human::samenamefunc(int)
			执行了void Men::samenamefunc(int)
			执行了Human::samenamefunc()
			执行了Human::samenamefunc()*/

	}


	return 0;
}