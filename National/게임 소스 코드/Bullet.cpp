#include "Bullet.h"
#include "Sprite.h"

CSprite* CBullet::m_bullet[7];

void CBullet::InitBullet(CGraphics* g)
{
	m_bullet[0] = new CSprite(g, L"..//Content//Bullet//H_1.png");
	m_bullet[1] = new CSprite(g, L"..//Content//Bullet//H_2.png");
	m_bullet[2] = new CSprite(g, L"..//Content//Bullet//H_3.png");
	m_bullet[3] = new CSprite(g, L"..//Content//Bullet//M_1.png");
	m_bullet[4] = new CSprite(g, L"..//Content//Bullet//M_1.png");
	m_bullet[5] = new CSprite(g, L"..//Content//Bullet//M_2.png");
	m_bullet[6] = new CSprite(g, L"..//Content//Bullet//M_3.png");
}

void CBullet::DestBullet()
{
	for(int i = 0; i < 7; i++)
		delete m_bullet[i];
}

CBullet::CBullet(CState *state, BulletType type, float x, float y, float _angle, float _speed) : CGameObject(state)
{
	SetX(x); SetY(y);
	m_angle = _angle;
	m_speed = _speed;
	m_index = type;
	enabled = true;
}

CBullet::~CBullet(void)
{
}

void CBullet::Update(float dt)
{
	if(enabled)
	{
		SetX(GetX() + cosf(m_angle * 3.141592f) * m_speed * dt * 10);
		SetY(GetY() + sinf(m_angle * 3.141592f) * m_speed * dt * 10);
	}
}

void CBullet::Draw(float)
{
	if(enabled)
	{
		CSprite *img = CBullet::m_bullet[m_index];
		Graphics()->Draw(img, GetX() - img->GetWidth() / 2, GetY() - img->GetHeight() / 2,
			(float)img->GetWidth(), (float)img->GetHeight(), (m_angle + 0.5f) * 3.141592f);
	}
}

bool CBullet::CrashCheck(float _x, float _y, float _r)
{
	return ::CrashCheck(_x, _y, _r, GetX(), GetY(), CBullet::m_bullet[m_index]->GetWidth() / 2.0f);
}