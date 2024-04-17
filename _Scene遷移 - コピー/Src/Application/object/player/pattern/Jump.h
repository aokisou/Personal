#pragma once

#include "Pattern.h"

class Jump :public Pattern
{
public:
	Jump() {}
	~Jump(){}

	void Update()override;

	int GetStateType()override { return jump; }
};