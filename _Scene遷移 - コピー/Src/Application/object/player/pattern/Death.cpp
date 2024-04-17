#include "Death.h"
#include "../Player.h"

void Death::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > 5)
	{
		m_CoolCnt = 0;
		m_AnimeCnt++;
		if (m_AnimeCnt > 7)
		{
			m_AnimeCnt = 0;
			m_player->DisableAlive();
		}
	}
}