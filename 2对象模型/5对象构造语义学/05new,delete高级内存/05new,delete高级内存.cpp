#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;


int main() {
	void* p = malloc(0);
	char* q = new char[0];

	strcpy_s((char*)p, 100, "This is a test1!");
	strcpy_s(q, 100, "This is a test2");

	free(p);
	delete[] q;

	return 0;
}