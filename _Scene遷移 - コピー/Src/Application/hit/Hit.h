#pragma once

class GameScene;

class Hit
{
public:
	Hit(){ m_pOwner = nullptr; }
	~Hit(){}

	void Init();

	void PlyEmyHit();
	void ArrEmyHit();

	void SetOwner(GameScene* a_pOwner) { m_pOwner = a_pOwner; }
private:
	GameScene* m_pOwner;
};