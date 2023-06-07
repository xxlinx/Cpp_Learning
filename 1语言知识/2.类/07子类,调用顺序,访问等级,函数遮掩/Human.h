#pragma once
class Human
{
public:
	Human();
	Human(int);
public:
	void samenamefunc();
	void samenamefunc(int);

public:
	int m_Age;
	char m_Name[100];
	void funcpub() {};

protected:
	int m_pro1;
	void funcpor() {};

private:
	int m_priv1;
	void funcpriv() {};
};

