#define _CRT_SECURE_NO_WARNINGS

#include "MenuState.h"
//#include <cstdio>

CMenuState::CMenuState(CGame *game) : CState(game)
{
}

CMenuState::~CMenuState(void)
{
}

void CMenuState::Initial()
{
	m_back = new CSprite(Graphics(), L"..\\Content\\Menu\\main.png");
	m_sel = new CSprite(Graphics(), L"..\\Content\\Menu\\select.png");

	m_ranking = new CSprite(Graphics(), L"..\\Content\\Menu\\ranking.png");

	m_index = EMI_START;

	FILE *fp = fopen("Ranking.txt", "rt");
	for(int i = 0; i < 3; i++)
		fscanf(fp, "%c %c %c %d\n", 
		&m_rank[i].initial[0], &m_rank[i].initial[1], &m_rank[i].initial[2], &m_rank[i].point);
	fclose(fp);

	m_inputDelay = new CDelay(200);
	m_isRanking = false;

	m_rankFont = new CImageFont(Graphics());

	m_isSelect = false;
	m_charList = new CSprite(Graphics(), L"..\\Content\\Menu\\char.png");
	m_charCursor = new CSprite(Graphics(), L"..\\Content\\Menu\\char_select.png");
	m_lstIndex = EPT_NANO_MOUSE;

	m_title = new CSound(L"..\\Content\\Sound\\title.wma");
	m_title->Play(true);
}

void CMenuState::Update(float dt)
{
	m_title->Update();

	bool keyDown = false;
	m_inputDelay->Update(dt);

	if(m_isRanking)
	{
		if(Game()->KeyPress(VK_SPACE) || Game()->KeyPress(VK_ESCAPE))
		{
			if(m_inputDelay->Check())
			{
				m_isRanking = false;
				keyDown = true;
			}
		}
	}
	else if(m_isSelect)
	{
		if(Game()->KeyPress(VK_SPACE))
		{
			if(m_inputDelay->Check())
			{
				((CGameState*)Game()->GetStates(STATE_GAME))->m_selectedType = m_lstIndex;
				Game()->SetState(STATE_GAME);
				return;
			}
		}
		if(Game()->KeyPress(VK_ESCAPE))
		{
			if(m_inputDelay->Check())
			{
				m_isSelect = false;
				keyDown = true;
			}
		}
		if(Game()->KeyPress(VK_LEFT))
		{
			if(m_inputDelay->Check())
			{
				if(m_lstIndex > EPT_NANO_MOUSE)
					m_lstIndex = (PlayerType)(m_lstIndex - 1);
				else
					m_lstIndex = EPT_NANO_FIGHTER;
				keyDown = true;
			}
		}
		if(Game()->KeyPress(VK_RIGHT))
		{
			if(m_inputDelay->Check())
			{
				if(m_lstIndex < EPT_NANO_FIGHTER)
					m_lstIndex = (PlayerType)(m_lstIndex + 1);
				else
					m_lstIndex = EPT_NANO_MOUSE;
				keyDown = true;
			}
		}
	}
	else
	{
		if(Game()->KeyPress(VK_UP))
		{
			if(m_inputDelay->Check())
			{
				if(m_index > EMI_START)
					m_index = (MenuIndex)(m_index - 1);
				else
					m_index = EMI_EXIT;
				keyDown = true;
			}
		}
		if(Game()->KeyPress(VK_DOWN))
		{
			if(m_inputDelay->Check())
			{
				if(m_index < EMI_EXIT)
					m_index = (MenuIndex)(m_index + 1);
				else
					m_index = EMI_START;
				keyDown = true;
			}
		}

		if(Game()->KeyPress(VK_SPACE))
		{
			if(m_inputDelay->Check())
			{
				switch(m_index)
				{
				case EMI_START:
					m_isSelect = true;
					break;
				case EMI_RANKING:
					m_isRanking = true;
					break;
				case EMI_EXIT:
					PostQuitMessage(0);
					break;
				}
				keyDown = true;
			}
		}
	}

	if(keyDown) m_inputDelay->Reset();
}

void CMenuState::Draw(float dt)
{
	if(!m_isRanking)
	{
		Graphics()->Draw(m_back, 0, 0);
		
		if(m_isSelect)
		{
			Graphics()->Draw(m_charList, (float)(400 - m_charList->GetWidth() / 2), 
				(float)(300 - m_charList->GetHeight() / 2));
			Graphics()->Draw(m_charCursor, 
				(float)(58 + (int)m_lstIndex * (m_charCursor->GetWidth() + 3)), 
				(float)(315 - m_charList->GetHeight() / 2));
		}
		else
		{
			Graphics()->Draw(m_sel, 580, (float)(400 + (int)m_index * 52));
		}
	}
	else
	{
		Graphics()->Draw(m_ranking, 0, 0);

		for(int i = 0; i < 3; i++)
		{
			wchar_t temp[4] = {0,};
			wsprintf(temp, L"%c%c%c", m_rank[i].initial[0], m_rank[i].initial[1], m_rank[i].initial[2]);
			m_rankFont->Draw(184, (float)(227 + i * 84), temp);
			m_rankFont->Draw(469, (float)(227 + i * 84), m_rank[i].point);
		}
	}
}

void CMenuState::Destroy()
{
	m_title->Stop();
	delete m_title;
	delete m_charCursor;
	delete m_charList;
	delete m_rankFont;
	delete m_inputDelay;
	delete m_back;
	delete m_sel;
	delete m_ranking;
}