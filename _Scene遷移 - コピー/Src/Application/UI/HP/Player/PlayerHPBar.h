#pragma once

class PlayerHPBar
{
public:
	PlayerHPBar() { Init(); }
	~PlayerHPBar() { Release(); }

	void Update(int* _hp, int _maxHP);
	void Draw(int _maxHP);

private:
	void Init();
	void Release();

	int m_hp = 0;

	Math::Matrix m_gaugeMat = Math::Matrix::Identity;
	Math::Matrix m_barMat = Math::Matrix::Identity;

	KdTexture m_gaugeTex;
	KdTexture m_barTex;
};