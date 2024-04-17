#pragma once

class Game;

class Hit
{
public:
	Hit(){ m_pOwner = nullptr; }
	~Hit(){}

	void Init();

	void PlyEmyHit();
	void BltEmyHit();

	void SetOwner(Game* a_pOwner) { m_pOwner = a_pOwner; }
private:
	Game* m_pOwner;
};