#pragma once

#include <iostream>
#include "human.h"
class Women : public Human
{
public:
	Women();
	virtual ~Women();

public:
	virtual void eat() override;

	virtual CSuiBian_Sub* ovr()
	{
		return NULL;
	};
};

