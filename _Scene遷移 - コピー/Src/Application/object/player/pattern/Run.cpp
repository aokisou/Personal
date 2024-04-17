#include "Run.h"

void Run::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > 5)
	{
		m_CoolCnt = 0;
		m_AnimeCnt++;
		if (m_AnimeCnt > 5)
		{
			m_AnimeCnt = 0;
		}
	}
}