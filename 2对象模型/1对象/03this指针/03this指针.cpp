#include <iostream>

using namespace std;

class A {
public:
	int a;
	A() {
		printf("A::A() 的 this指针是：%p!\n", this);
	}
	void funA() { printf("A::funcA: this = %p\n", this); }

};

class B {
public:
	int b;
	B() {
		printf("B::B() 的 this指针是：%p!\n", this);
	}
	void funB() { printf("B::funcB: this = %p\n", this); }

};

class C : public A, public B {
public:
	int c;
	C() {
		printf("C::C() 的 this指针是：%p!\n", this);
	}
	void funC() { printf("C::funcC: this = %p\n", this); }
	void funB() { printf("C::funcB: this = %p\n", this); } //定义在C类中
};


int main() {
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	C myc;
	myc.funA();
	myc.funB();
	myc.B::funB();
	myc.funC();

	return 0;

}