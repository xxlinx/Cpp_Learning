#pragma once

using namespace std;

template<class T>
T funadd(const T& a, const T& b){
	T addhe = a + b;
	return addhe;
}

template<class T>
class ATPL{
public:
	enum ECURRSTATUS{
		E_CS_Busy,
		E_CS_Free,
	};


public:
	T m_i, m_j;
	ATPL(T tmpi = 0, T tmpj = 0) {//¹¹Ôìº¯Êý
		m_i = tmpi;
		m_j = tmpj;
	}

public:
	static int m_sti;
	static T m_sti2;

public:
	void func1() const { cout << "ATPL::func1()" << endl; }
	void func2() const { cout << "ATPL::func2()" << endl; }

public:
	virtual void virfunc1() { cout << "ATPL::virfunc1()" << endl; }
	virtual void virfunc2() { cout << "ATPL::virfunc2()" << endl; }

};

template <class T> 	int ATPL<T>::m_sti = 10;
template <class T> 	T ATPL<T>::m_sti2 = 10;