#ifndef __MEN__
#define __MEN__

#include "Human.h"

class Men : public Human
{
	friend  void func(const Men& tmpmen);    //һ�������������ú����Ǳ������Ԫ����

public:
	using Human::samenamefunc; //using�����ø��ຯ��������ɼ�

public:
	Men();
	virtual ~Men();
public:
	void samenamefunc(int);
	void funcmen() {};

	virtual void eat() override;

	virtual CSuiBian_Sub* ovr() { return NULL; }

	//public:
private:
	void funcmen2() const
	{
		std::cout << "Men:funcmen2" << std::endl;
	};

};
#endif
