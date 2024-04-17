#pragma once

#include "Pattern.h"

class Player;

class Run :public Pattern
{
public:
	Run() {}
	~Run(){}

	void Update()override;

	int GetStateType()override { return run; }
};