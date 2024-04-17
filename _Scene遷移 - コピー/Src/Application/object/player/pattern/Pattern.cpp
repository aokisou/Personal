#include "Pattern.h"

void Pattern::Init(Player* a_player)
{
	m_player = a_player;
	m_AnimeCnt = 0;
	m_CoolCnt = 0;
}

void Pattern::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > 5)
	{
		m_CoolCnt = 0;
		m_AnimeCnt++;
		if (m_AnimeCnt > 4)
		{
			m_AnimeCnt = 0;
		}
	}
}