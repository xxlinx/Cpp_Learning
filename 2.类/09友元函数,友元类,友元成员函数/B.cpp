

#include "A.h"
#include "B.h"

void B::callBAF(int x, A& a)
{
	a.data = x;
	std::cout << a.data << std::endl;
}
