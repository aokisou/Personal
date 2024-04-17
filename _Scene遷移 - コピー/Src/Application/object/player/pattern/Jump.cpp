#include "Jump.h"

void Jump::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > 10)
	{
		m_CoolCnt -= 10;
		m_AnimeCnt++;
		if (m_AnimeCnt > 1)
		{
			m_AnimeCnt = 0;
		}
	}
}