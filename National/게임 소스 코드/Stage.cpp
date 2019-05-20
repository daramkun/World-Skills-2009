#define _CRT_SECURE_NO_WARNINGS

#include "Stage.h"
#include "GameState.h"

#include "Bacteria.h"
#include "Virus.h"
#include "Cancer.h"

#include "WhiteBlood.h"
#include "RedBlood.h"

CStage::CStage(CState *state, int stageNum) : CGameObject(state)
{
	CEnermy** enermies = ((CGameState*)State())->m_vtEnermy;

	// ���� �� ��/������ �ʱ�ȭ
	for(int i = 0; i < ENERMY_COUNT; i++)
		enermies[i] = NULL;
	for(int i = 0; i < BLOOD_COUNT; i++)
	{
		((CGameState*)State())->m_redBlood[i] = NULL;
		((CGameState*)State())->m_whiteBlood[i] = NULL;
	}

	//
	// �������� ��ȣ�� ���� �ٸ� ���� ���� ���� �� �� ������ �ε�
	//

	CPlayer *player = ((CGameState*)State())->m_player;

	// �ε��� ������ ����
	char *pattern = NULL;
	wchar_t *map = NULL;
	wchar_t *num = NULL;
	switch(stageNum)
	{
	case 1:
		pattern = "Stage1.txt";
		map = L"..\\Content\\Map\\stage1_";
		num = L"..\\Content\\Interface\\stage_1.png";
		player->SetX(20); player->SetY(520);
		m_moveEnable = false;
		break;
	case 2:
		pattern = "Stage2.txt";
		map = L"..\\Content\\Map\\stage2_";
		num = L"..\\Content\\Interface\\stage_2.png";
		player->SetX(520 / 2); player->SetY(520);
		player->m_shooter->SetX(player->GetX());
		player->m_shooter->SetY(player->GetY());
		m_moveEnable = true;
		break;
	}

	// ���� �� �� �ε�
	m_map = new CAnime(Graphics(), map, 1, 2, 200);
	m_stageNumber = new CSprite(Graphics(), num);
	m_map->Play(true);

	FILE *fp = fopen(pattern, "rt");
	int count = 0; fscanf(fp, "%d", &count);
	count++;
	for(int i = 0; i < count; i++)
	{
		char type = 0; int num = 0; int x = 0; int y = 0;
		fscanf(fp, "%c %d %d %d\n", &type, &num, &x, &y);
		switch(type)
		{
		case 'B':
			enermies[i] = new CBacteria(State(), (float)x, (float)y, (BacteriaType)num);
			break;
		case 'V':
			enermies[i] = new CVirus(State(), (float)x, (float)y, (VirusType)num);
			break;
		case 'C':
			enermies[i] = new CCancer(State(), stageNum, (CancerType)num);
			break;
		}
	}
	fclose(fp);

	// �� ��ġ ����
	SetY(3000);

	m_bloodDelay = new CDelay(1000);
}

CStage::~CStage(void)
{
	// ���� ����
	for(int i = 0; i < ENERMY_COUNT; i++)
		if(((CGameState*)State())->m_vtEnermy[i] != NULL)
			delete ((CGameState*)State())->m_vtEnermy[i];
	// ��/������ ����
	for(int i = 0; i < BLOOD_COUNT; i++)
	{
		if(((CGameState*)State())->m_redBlood[i] != NULL)
			delete ((CGameState*)State())->m_redBlood[i];
		if(((CGameState*)State())->m_whiteBlood[i] != NULL)
			delete ((CGameState*)State())->m_whiteBlood[i];
	}
	// �� ����
	delete m_map;
	delete m_bloodDelay;
}

void CStage::Update(float dt)
{
	m_map->Update(dt);

	CEnermy* enermy;
	CPlayer* player = ((CGameState*)State())->m_player;

	if(!m_moveEnable)
	{
		player->SetX(player->GetX() + (10 * dt));
		if(player->GetX() >= 520 / 2)
		{
			m_moveEnable = true;
			player->m_shooter->SetX(player->GetX());
			player->m_shooter->SetY(player->GetY());
		}
	}
	else
	{
		// Y�� 0�� �� ������ ��ǥ �̵�
		if(GetY() <= 0)
			SetY(0);
		else
			SetY(GetY() - dt * 5);

		player->Update(dt);
	}

	// �� ������
	for(int i = 0; i < ENERMY_COUNT; i++)
	{
		enermy = ((CGameState*)State())->m_vtEnermy[i];
		if(enermy != NULL)
		{
			if(enermy->GetY() + enermy->m_anime->Current()->GetHeight() > GetY())
			{
				enermy->Update(dt);
				if(enermy->CrashPlayer(player))
				{
					if(!player->GetShield())
					{
						player->SetHp(player->GetHp() - 30);
						if(player->GetHp() > 0)
							Graphics()->WeakQuake();
					}
					else
					{
						player->SetShield(false);
					}
					enermy->SetEnabled(false);
					/*CEffect *eff = NULL;
					for(int i = 0; i < 150; i++)
					{
					if(eff != NULL)
					{
					eff = ((CGameState*)State())->m_effect[i];
					if(!eff->GetVisible())
					{
					eff->SetVisible(true);
					eff->SetX(enermy->GetX()); eff->SetY(enermy->GetY());
					eff->Play();
					break;
					}
					}
					}*/
				}

				if(enermy->GetY() - GetY() >= 650 && enermy->GetEnabled())
				{
					player->SetPg(player->GetPg() + 10);
					Graphics()->WeakQuake();
					enermy->SetEnabled(false);
				}
			}
		}
	}

	m_bloodDelay->Update(dt);

	// �������� Y ��ǥ�� 0�� �ƴϸ� �������� ������ ���� �� �׼�
	for(int i = 0; i < BLOOD_COUNT; i++)
	{
		if(((CGameState*)State())->m_whiteBlood[i] == NULL)
		{
			if(GetY() != 0)
			{
				if(m_bloodDelay->Check())
				{
					int j = rand() % 2000;
					if(j == 200)
					{
						((CGameState*)State())->m_whiteBlood[i] = new CWhiteBlood(State());
						m_bloodDelay->Reset();
					}
				}
			}
		}
		else
		{
			CWhiteBlood *wb = ((CGameState*)State())->m_whiteBlood[i];
			wb->Update(dt);
			if(wb->CheckCrash(player))
			{
				switch(wb->GetItemType())
				{
				case EIT_WEAPON:
					if(player->GetWeaponType() < 4)
					{
						player->SetWeaponType(player->GetWeaponType() + 1);
					}
					break;
				case EIT_SHIELD:
					player->SetShield(true);
					break;
				default:
					((CGameState*)State())->m_takeItem = wb->GetItemType();
					break;
				}

				delete ((CGameState*)State())->m_whiteBlood[i];
				((CGameState*)State())->m_whiteBlood[i] = NULL;
			}
		}

		if(((CGameState*)State())->m_redBlood[i] == NULL)
		{
			if(GetY() != 0)
			{
				if(m_bloodDelay->Check())
				{
					int j = rand() % 2500;
					if(j == 217)
					{
						((CGameState*)State())->m_redBlood[i] = new CRedBlood(State());
						m_bloodDelay->Reset();
					}
				}
			}
		}
		else
			((CGameState*)State())->m_redBlood[i]->Update(dt);
	}
}

void CStage::Draw(float dt)
{
	Graphics()->Draw(m_map->Current(), -100, -GetY());

	((CGameState*)State())->m_player->Draw(dt);

	for(int i = 0; i < BLOOD_COUNT; i++)
	{
		if(((CGameState*)State())->m_redBlood[i] != NULL)
			((CGameState*)State())->m_redBlood[i]->Draw(dt);
		if(((CGameState*)State())->m_whiteBlood[i] != NULL)
			((CGameState*)State())->m_whiteBlood[i]->Draw(dt);
	}

	CEnermy *enermy;
	for(int i = 0; i < ENERMY_COUNT; i++)
	{
		enermy = ((CGameState*)State())->m_vtEnermy[i];
		if(enermy != NULL)
		{
			if(enermy != NULL)
				enermy->Draw(dt);
		}
	}
}