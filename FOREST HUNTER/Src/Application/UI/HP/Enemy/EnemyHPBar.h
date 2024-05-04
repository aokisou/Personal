#pragma once

class EnemyHPBar
{
public:
	EnemyHPBar(KdTexture* _gaugeTex, KdTexture* _barTex) { Init(_gaugeTex,_barTex); }
	~EnemyHPBar() { Release(); }
	void Update(float* _hp, int _maxHP, Math::Vector2 _pos);
	void Draw(int _maxHP);

private:
	void Init(KdTexture* _gaugeTex,KdTexture* _barTex);
	void Release();

	float m_hp = 0.0f;

	Math::Matrix m_gaugeMat = Math::Matrix::Identity;
	Math::Matrix m_barMat = Math::Matrix::Identity;

	KdTexture* m_pGaugeTex;
	KdTexture* m_pBarTex;
};