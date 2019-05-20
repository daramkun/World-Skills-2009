#define _CRT_SECURE_NO_WARNINGS

#include "ResultState.h"
#include "GameState.h"

CResultState::CResultState(CGame* game) : CState(game)
{
}

CResultState::~CResultState(void)
{
}

void CResultState::Initial()
{
	m_whensave = 0;
	CGameState* gs = ((CGameState*)Game()->GetStates(STATE_GAME));

	m_back = new CSprite(Graphics(), L"..\\Content\\Menu\\Result.png");
	m_font = new CImageFont(Graphics());

	FILE *fp = fopen("Ranking.txt", "rt");
	for(int i = 0; i < 3; i++)
		fscanf(fp, "%c %c %c %d\n", 
		&rank[i].initial[0], &rank[i].initial[1], &rank[i].initial[2], &rank[i].point);
	fclose(fp);

	bool imhigh = false;
	for(int i = 0; i < 3; i++)
	{
		if(rank[i].point < gs->m_Score)
		{
			imhigh = true;
			m_whensave = i;
			break;
		}
	}

	if(imhigh)
		m_inputRanking = true;
	else
		m_inputRanking = false;

	for(int i = 0; i < 3; i++)
		m_initial[i] = 'A';

	m_input = 0;

	m_inputDelay = new CDelay(200);
	m_edited = new CSprite(Graphics(), L"..\\Content\\Menu\\re_select.png");

	m_result = new CSound(L"..\\Content\\Sound\\result.mid");
	m_result->Play(true);
}

void CResultState::Update(float dt)
{
	bool keyDown = false;
	CGameState* gs = ((CGameState*)Game()->GetStates(STATE_GAME));

	m_inputDelay->Update(dt);

	if(m_inputRanking)
	{
		if(Game()->KeyPress(VK_LEFT))
		{
			if(m_inputDelay->Check())
			{
				if(m_input == 0)
					m_input = 2;
				else
					m_input--;
				keyDown = true;
			}
		}
		if(Game()->KeyPress(VK_RIGHT))
		{
			if(m_inputDelay->Check())
			{
				if(m_input == 2)
					m_input = 0;
				else
					m_input++;
				keyDown = true;
			}
		}

		if(Game()->KeyPress(VK_UP))
		{
			if(m_inputDelay->Check())
			{
				if(m_initial[m_input] == 'A')
					m_initial[m_input] = 'Z';
				else
					m_initial[m_input]--;
				keyDown = true;
			}
		}
		if(Game()->KeyPress(VK_DOWN))
		{
			if(m_inputDelay->Check())
			{
				if(m_initial[m_input] == 'Z')
					m_initial[m_input] = 'A';
				else
					m_initial[m_input]++;
				keyDown = true;
			}
		}
	}

	if(keyDown) m_inputDelay->Reset();

	if(Game()->KeyPress(VK_SPACE))
	{
		if(m_inputRanking)
		{
			for(int i = m_whensave; i < 2; i++)
			{
				rank[i + 1].initial[0] = rank[i].initial[0];
				rank[i + 1].initial[1] = rank[i].initial[1];
				rank[i + 1].initial[2] = rank[i].initial[2];
				rank[i + 1].point = rank[i + 1].point;
			}
			for(int i = 0; i < 3; i++)
				rank[m_whensave].initial[i] = m_initial[i];
			rank[m_whensave].point = gs->m_Score;

			FILE *fp = fopen("Ranking.txt", "wt");
			for(int i = 0; i < 3; i++)
				fprintf(fp, "%c %c %c %d\n", 
				rank[i].initial[0], rank[i].initial[1], rank[i].initial[2],
				rank[i].point);
			fclose(fp);
		}

		Game()->SetState(STATE_MENU);
	}
}

void CResultState::Draw(float dt)
{
	CGameState* gs = ((CGameState*)Game()->GetStates(STATE_GAME));
	Graphics()->Draw(m_back, 0, 0);
	m_font->Draw(255, 154, gs->m_Bac1Hit);
	m_font->Draw(455, 154, gs->m_Bac2Hit);
	m_font->Draw(645, 154, gs->m_Bac3Hit);
	m_font->Draw(255, 255, gs->m_Bac1Hit);
	m_font->Draw(455, 255, gs->m_Bac1Hit);
	m_font->Draw(180, 414, gs->m_Score);
	if(m_inputRanking)
	{
		wchar_t temp[4] = {0,};
		wsprintf(temp, L"%c%c%c", m_initial[0], m_initial[1], m_initial[2]);
		m_font->Draw(618, 442, temp);
		Graphics()->Draw(m_edited, (float)(618 + m_input * 50), 494);
	}
	else
	{
		m_font->Draw(618, 442, L"DONE");
	}
}

void CResultState::Destroy()
{
	m_result->Stop();
	delete m_result;
	delete m_edited;
	delete m_inputDelay;
	delete m_font;
	delete m_back;
}