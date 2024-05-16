#include "main.h"
#include "Scene.h"
#include <vector>
#include <fstream>
#include <sstream>

void Scene::Draw2D()
{
	for (std::vector<std::shared_ptr<ANode>> oneRaneNode : m_nodeList)
	{
		for (std::shared_ptr<ANode> node : oneRaneNode)
		{
			SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
			switch (node->data)
			{
			case 0:
				SHADER.m_spriteShader.DrawBox(node->pos.x, node->pos.y, 32, 32, &Math::Color{ 1,1,1,1 });
				break;
			case 1:
				SHADER.m_spriteShader.DrawBox(node->pos.x, node->pos.y, 32, 32, &Math::Color{ 1,1,0,1 });
				break;
			case 2:
				SHADER.m_spriteShader.DrawBox(node->pos.x, node->pos.y, 32, 32, &Math::Color{ 1,0,0,1 });
				break;
			}
		}
	}

	SHADER.m_spriteShader.SetMatrix(m_pmat);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0,&Math::Rectangle(0,0,64,64));
}

void Scene::Update()
{
	if (!m_bOK)
	{
		m_nowMinScoreNode = SearchMinScoreNode();
	}

	if (m_nowMinScoreNode != nullptr && !m_bOK)
	{
		if (m_nowMinScoreNode->data == 2)
		{
			m_minScoreNode = GetPath(m_nowMinScoreNode);
			m_bOK = true;
		}
	}

	if (m_bOK)
	{
		if (m_minScoreNode.size() == 1)
		{
			m_num = { m_minScoreNode[0]->num };
		}
		if (m_minScoreNode.size() == 0)
		{
			Reset();
			return;
		}
		else
		{
			if (m_minScoreNode[0] != nullptr)
			{
				Move(m_minScoreNode[0]);
			}
			if ((int)m_ppos.x == (int)m_minScoreNode[0]->pos.x)
			{
				if ((int)m_ppos.y == (int)m_minScoreNode[0]->pos.y)
				{
					m_minScoreNode.erase(m_minScoreNode.begin());
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!m_bKey)
		{
			Reset();
			m_bKey = true;
		}
	}
	else
	{
		m_bKey = false;
	}

	m_pmat = Math::Matrix::CreateTranslation(m_ppos.x, m_ppos.y, 0);

	m_frame++;
}

std::shared_ptr<ANode> Scene::SearchMinScoreNode()
{
	// 最小スコア
	int min = 99999999;
	// 最小実コスト
	int minCost = 99999999;
	std::shared_ptr<ANode> minNode = m_nowMinScoreNode;

	OpenNodeState(minNode);

	for (std::vector<std::shared_ptr<ANode>> oneRaneNode : m_nodeList)
	{
		for (std::shared_ptr<ANode> node : oneRaneNode)
		{
			int score = node->score;
			if (node->state != State::open) { continue; }

			if (score > min) {
				// スコアが大きい
				continue;
			}
			if (score == min && node->cost >= minCost) {
				// スコアが同じときは実コストも比較する
				continue;
			}

			// 最小値更新
			min = score;
			minCost = node->cost;
			minNode = node;
		}
	}

	return minNode;
}

std::vector<std::shared_ptr<ANode>> Scene::GetPath(std::shared_ptr<ANode> _node)
{
	std::vector<std::shared_ptr<ANode>> _path;

	while (_node->rootNode != nullptr)
	{
		_path.insert(_path.begin(), _node);
		_node = _node->rootNode;
	}

	return _path;
}

void Scene::OpenNodeState(std::shared_ptr<ANode> _node)
{
	int i = 0, j = 0;
	for (std::vector<std::shared_ptr<ANode>> oneRaneNode : m_nodeList)
	{
		for (std::shared_ptr<ANode> node : oneRaneNode)
		{
			if (node->pos == _node->pos)
			{
				_node->state = State::close;
				//上の列
				if (i - 1 >= 0 && j - 1 >= 0)
				{
					if (m_nodeList[i - 1][j - 1]->state != State::close)
					{
						m_nodeList[i - 1][j - 1]->state = State::open;
						if (m_nodeList[i - 1][j - 1]->rootNode == nullptr)
						{
							m_nodeList[i - 1][j - 1]->rootNode = _node;
						}
					}
				}
				if (i - 1 >= 0)
				{
					if (m_nodeList[i - 1][j]->state != State::close)
					{
						m_nodeList[i - 1][j]->state = State::open;
						if (m_nodeList[i - 1][j]->rootNode == nullptr)
						{
							m_nodeList[i - 1][j]->rootNode = _node;
						}
					}
				}
				if (i - 1 >= 0 && j + 1 < m_nodeList[0].size())
				{
					if (m_nodeList[i - 1][j + 1]->state != State::close)
					{
						m_nodeList[i - 1][j + 1]->state = State::open;
						if (m_nodeList[i - 1][j + 1]->rootNode == nullptr)
						{
							m_nodeList[i - 1][j + 1]->rootNode = _node;
						}
					}
				}

				//中の列
				if (j - 1 >= 0)
				{
					if (m_nodeList[i][j - 1]->state != State::close)
					{
						m_nodeList[i][j - 1]->state = State::open;
						if (m_nodeList[i][j - 1]->rootNode == nullptr)
						{
							m_nodeList[i][j - 1]->rootNode = _node;
						}
					}
				}
				if (j + 1 < m_nodeList[0].size())
				{
					if (m_nodeList[i][j + 1]->state != State::close)
					{
						m_nodeList[i][j + 1]->state = State::open;
						if (m_nodeList[i][j + 1]->rootNode == nullptr)
						{
							m_nodeList[i][j + 1]->rootNode = _node;
						}
					}
				}

				//下の列
				if (i + 1 < m_nodeList.size() && j - 1 >= 0)
				{
					if (m_nodeList[i + 1][j - 1]->state != State::close)
					{
						m_nodeList[i + 1][j - 1]->state = State::open;
						if (m_nodeList[i + 1][j - 1]->rootNode == nullptr)
						{
							m_nodeList[i + 1][j - 1]->rootNode = _node;
						}
					}
				}
				if (i + 1 < m_nodeList.size())
				{
					if (m_nodeList[i + 1][j]->state != State::close)
					{
						m_nodeList[i + 1][j]->state = State::open;
						if (m_nodeList[i + 1][j]->rootNode == nullptr)
						{
							m_nodeList[i + 1][j]->rootNode = _node;
						}
					}
				}
				if (i + 1 < m_nodeList.size() && j + 1 < m_nodeList[0].size())
				{
					if (m_nodeList[i + 1][j + 1]->state != State::close)
					{
						m_nodeList[i + 1][j + 1]->state = State::open;
						if (m_nodeList[i + 1][j + 1]->rootNode == nullptr)
						{
							m_nodeList[i + 1][j + 1]->rootNode = _node;
						}
					}
				}
			}
			if (node->state == State::open)
			{
				if (node->cost == 0)
				{
					float dx, dy;
					dx = abs(m_nodeList[(int)m_goalNum.x][(int)m_goalNum.y]->num.x - node->num.x);
					dy = abs(m_nodeList[(int)m_goalNum.x][(int)m_goalNum.y]->num.y - node->num.y);

					if (node->rootNode != nullptr)
					{
						node->cost = node->rootNode->cost + 1;
					}
					if (dx >= dy)
					{
						node->h = dx;
					}
					else
					{
						node->h = dy;
					}
					node->score = node->h + node->cost;
				}
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void Scene::Move(std::shared_ptr<ANode> _node)
{
	int deg = GetAngleDeg(m_ppos,_node->pos);
	m_pmove = {cos(DirectX::XMConvertToRadians(deg)), sin(DirectX::XMConvertToRadians(deg))};
	m_ppos += m_pmove;
}

float Scene::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
	float a, b;
	a = dest.x - src.x;
	b = dest.y - src.y;
	float rad;
	rad = atan2(b, a);
	float deg;
	//deg = rad * 180.0f / 3.14f;
	deg = DirectX::XMConvertToDegrees(rad);
	if (deg < 0)
	{
		deg += 360;
	}
	return deg;
}

void Scene::Reset()
{
	m_num = m_nowMinScoreNode->num;

	std::ifstream ifs(m_file[rand() % 5]);
	std::string str, field;

	int i = 0, j = 0;

	m_nodeList.clear();
	m_minScoreNode.clear();
	m_nowMinScoreNode = nullptr;

	while (getline(ifs, str))
	{
		std::istringstream iss(str);

		std::vector<std::shared_ptr<ANode>> _n;

		while (getline(iss, field, ','))
		{
			std::shared_ptr<ANode> n = std::make_shared<ANode>();
			n->pos = { j * 64.0f - 64.0f,i * -64.0f + 360.0f };
			n->mat = Math::Matrix::CreateTranslation(n->pos.x, n->pos.y, 0.0f);
			n->num = { (float)i,(float)j };
			n->data = stoi(field);
			n->cost = 0;
			n->h = 0;
			n->score = 0;
			if (n->data != 1)n->state = State::none;
			else n->state = State::close;
			n->rootNode = nullptr;
			if (n->data == 2)m_goalNum = { (float)i,(float)j };
			_n.push_back(n);
			j++;
		}
		m_nodeList.push_back(_n);
		i++;
		j = 0;
	}

	m_nowMinScoreNode = m_nodeList[m_num.x][m_num.y];
	m_nodeList[m_num.x][m_num.y]->state = State::open;
	float dx, dy;
	dx = m_nodeList[m_goalNum.x][m_goalNum.y]->num.x - m_nodeList[m_num.x][m_num.y]->num.x;
	dy = m_nodeList[m_goalNum.x][m_goalNum.y]->num.y - m_nodeList[m_num.x][m_num.y]->num.y;

	if (dx <= dy)
	{
		m_nodeList[m_num.x][m_num.y]->h = dx;
		m_nodeList[m_num.x][m_num.y]->score = dx;
	}
	else
	{
		m_nodeList[m_num.x][m_num.y]->h = dy;
		m_nodeList[m_num.x][m_num.y]->score = dy;
	}

	m_bOK = false;
}

void Scene::Init()
{
	srand(timeGetTime());
	std::ifstream ifs(m_file[rand() % 5]);
	std::string str, field;

	int i = 0, j = 0;

	while (getline(ifs, str))
	{
		std::istringstream iss(str);

		std::vector<std::shared_ptr<ANode>> _n;

		while (getline(iss, field, ','))
		{
			std::shared_ptr<ANode> n = std::make_shared<ANode>();
			n->pos = { j * 64.0f - 64.0f,i * -64.0f + 360.0f };
			n->mat = Math::Matrix::CreateTranslation(n->pos.x, n->pos.y, 0.0f);
			n->num = { (float)i,(float)j };
			n->data = stoi(field);
			n->cost = 0;
			n->h = 0;
			n->score = 0;
			if (n->data != 1)n->state = State::none;
			else n->state = State::close;
			n->rootNode = nullptr;
			if (n->data == 2)m_goalNum = { (float)i,(float)j };
			_n.push_back(n);
			j++;
		}
		m_nodeList.push_back(_n);
		i++;
		j = 0;
	}

	int startX = 1, startY = 1;

	m_minScoreNode.push_back(m_nodeList[startX][startY]);
	m_nowMinScoreNode = m_nodeList[startX][startY];
	m_ppos = m_nodeList[startX][startY]->pos;
	m_nodeList[startX][startY]->state = State::open;
	float dx, dy;
	dx = m_nodeList[m_nodeList.size() - 1][m_nodeList[0].size() - 1]->num.x - m_nodeList[startX][startY]->num.x;
	dy = m_nodeList[m_nodeList.size() - 1][m_nodeList[0].size() - 1]->num.y - m_nodeList[startX][startY]->num.y;

	if (dx >= dy)
	{
		m_nodeList[startX][startY]->h = dx;
		m_nodeList[startX][startY]->score = dx;
	}
	else
	{
		m_nodeList[startX][startY]->h = dy;
		m_nodeList[startX][startY]->score = dy;
	}

	m_bOK = false;
	m_frame = 0;

	m_tex.Load("player.png");
}

void Scene::Release()
{
	m_tex.Release();
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
