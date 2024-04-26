#include "map.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include "../Scene/BaseScene/Game/GameScene.h"
#include "../Utility/Utility.h"

#define MapSize 64		//マップサイズ
#define MaxRecord 10	//画像1列に入るマップチップ

void Map::Init()
{
	m_Size = MapSize;

	int heightSize = m_pos.size(), widthSize = m_pos[0].size();

	for (int i = 0; i < heightSize; i++)
	{
		for (int j = 0; j < widthSize; j++)
		{
			m_pos[i][j] = { (float)(j * m_Size - SCREEN::width / Half),(float)((i * m_Size - SCREEN::height / Half) * Reverse) };
			m_mat[i][j] = Math::Matrix::CreateTranslation(m_pos[i][j].x, m_pos[i][j].y, 0);

			switch (m_data[i][j])
			{
			case MapTile::MTSlime:
				m_pOwner->CreateSlime(m_pos[i][j]);
				m_data[i][j] = MapTile::none;
				break;
			case MapTile::MTWolf:
				m_pOwner->CreateWolf(m_pos[i][j]);
				m_data[i][j] = MapTile::none;
				break;
			case MapTile::MTOrc:
				m_pOwner->CreateOrc(m_pos[i][j]);
				m_data[i][j] = MapTile::none;
				break;
			}
		}
	}

	m_tex.Load("Texture/Map/MapTile.png");
}

void Map::Update(int _s, int _e, float _scrollX)
{
	int heightSize = m_pos.size();
	for (int i = 0; i < heightSize; i++)
	{
		for (int j = _s; j < _e; j++)
		{
			m_mat[i][j] = Math::Matrix::CreateTranslation(m_pos[i][j].x - _scrollX, m_pos[i][j].y, 0);
		}
	}
}

void Map::Draw(int _s, int _e)
{
	int heightSize = m_pos.size();
	for (int i = 0; i < heightSize; i++)
	{
		for (int j = _s; j < _e; j++)
		{
			Draw(&m_mat[i][j], &m_data[i][j]);
		}
	}
}

void Map::Draw(Math::Matrix* _mat, int* _i)
{
	if (*_i == -1) { return; }
	int i = *_i % MaxRecord;
	int j = *_i / MaxRecord;
	SHADER.m_spriteShader.SetMatrix(*_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(i * m_Size, j * m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
}

void Map::SetMapData(std::string _filenme)
{
	std::ifstream ifs(_filenme);

	std::string str, field;

	while (getline(ifs, str))
	{
		std::istringstream iss(str);

		std::vector<Math::Matrix> m;
		std::vector<Math::Vector2> p;
		std::vector<int> n;			

		while (getline(iss, field, ','))
		{
			Math::Matrix m1;
			Math::Vector2 p1;
			int n1 = stoi(field);

			m.push_back(m1);
			p.push_back(p1);
			n.push_back(n1);
		}
		m_mat.push_back(m);
		m_pos.push_back(p);
		m_data.push_back(n);
	}

	ifs.close();

	Init();
}

void Map::Release()
{
	m_data.clear();
	m_pos.clear();
	m_mat.clear();
}

int Map::GetHalfSize()
{
	return m_Size / Half;
}