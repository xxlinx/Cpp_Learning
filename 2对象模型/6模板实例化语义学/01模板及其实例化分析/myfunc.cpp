#include <iostream>
#include "mytemplate.h"
using namespace std;
int ftest() {
	ATPL<int> myobj;
	myobj.m_sti2 = 21;
	cout << myobj.m_sti2 << endl;
	return 15;
}