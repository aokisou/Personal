#pragma once

#include "Pattern.h"

class PlayerJump :public PlayerPattern
{
public:
	PlayerJump() {}
	~PlayerJump(){ Release(); }

	void Update()override;

	int GetStateType()override { return jump; }
};