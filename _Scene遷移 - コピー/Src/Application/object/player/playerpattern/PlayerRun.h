#pragma once

#include "PlayerPattern.h"

class Player;

class PlayerRun :public PlayerPattern
{
public:
	PlayerRun() {}
	~PlayerRun(){ Release(); }

	void Update()override;

	int GetStateType()override { return playerRun; }
};