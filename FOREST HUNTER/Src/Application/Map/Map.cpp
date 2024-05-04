#include "map.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include "../Scene/BaseScene/Game/GameScene.h"
#include "../Object/Player/Player.h"
#include "../Utility/Utility.h"

#define MAPSIZE 64		//マップサイズ
#define MAXRECORD 10	//画像1列に入るマップチップ

void Map::Init()
{
	m_Size = MAPSIZE;

	int heightSize = m_pos.size(), widthSize = m_pos[0].size();

	for (int i = 0; i < heightSize; i++)
	{
		for (int j = 0; j < widthSize; j++)
		{
			m_pos[i][j] = { (float)(j * m_Size - SCREEN::width / Half),(float)((i * m_Size - SCREEN::height / Half) * Reverse) };
			m_mat[i][j] = Math::Matrix::CreateTranslation(m_pos[i][j].x, m_pos[i][j].y, 0);
			m_src[i][j] = Math::Rectangle((m_data[i][j] % MAXRECORD) * m_Size, (m_data[i][j] / MAXRECORD) * m_Size, m_Size, m_Size);

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
			case MapTile::MTMinotaur:
				m_pOwner->CreateMinotaur(m_pos[i][j]);
				m_data[i][j] = MapTile::none;
				break;
			}
		}
	}
}

void Map::Update(int _s, int _e, float _scrollX)
{
	int heightSize = m_pos.size();
	for (int i = 0; i < heightSize; i++)
	{
		for (int j = _s; j < _e; j++)
		{
			if (m_data[i][j] >= MapTile::Tutorial)
			{
				if (m_pOwner->GetPlayer()->GetPos().x > m_pos[i][j].x)
				{
					m_pOwner->SetDrawTutorial(m_data[i][j]);
					m_data[i][j] = MapTile::none;
				}
			}
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
			if (m_data[i][j] == MapTile::none || m_data[i][j] >= MapTile::Tutorial) { continue; }
			SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
			SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_src[i][j]);
		}
	}
}

void Map::SetMapData(std::string _filenme)
{
	//きれいにしてから入れる
	m_data.clear();
	m_pos.clear();
	m_mat.clear();
	m_src.clear();

	std::ifstream ifs(_filenme);

	std::string str, field;

	while (getline(ifs, str))
	{
		std::istringstream iss(str);

		std::vector<Math::Matrix> m;
		std::vector<Math::Vector2> p;
		std::vector<int> n;
		std::vector<Math::Rectangle> s;

		while (getline(iss, field, ','))
		{
			Math::Matrix m1;
			Math::Vector2 p1;
			int n1 = stoi(field);
			Math::Rectangle s1;

			m.push_back(m1);
			p.push_back(p1);
			n.push_back(n1);
			s.push_back(s1);
		}
		m_mat.push_back(m);
		m_pos.push_back(p);
		m_data.push_back(n);
		m_src.push_back(s);
	}

	ifs.close();

	Init();
}

void Map::Release()
{
	m_data.clear();
	m_pos.clear();
	m_mat.clear();
	m_src.clear();
}

int Map::GetHalfSize()
{
	return m_Size / Half;
}