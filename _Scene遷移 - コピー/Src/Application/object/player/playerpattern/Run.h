#pragma once

#include "Pattern.h"

class Player;

class PlayerRun :public PlayerPattern
{
public:
	PlayerRun() {}
	~PlayerRun(){ Release(); }

	void Update()override;

	int GetStateType()override { return run; }
};