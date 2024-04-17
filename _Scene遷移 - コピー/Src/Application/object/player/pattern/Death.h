#pragma once

#include "Pattern.h"

class Death :public Pattern
{
public:
	Death() {}
	~Death(){}

	void Update()override;

	int GetStateType() override{ return death; }
};