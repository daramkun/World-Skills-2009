#pragma once

#include "GameObject.h"
#include "Anime.h"

class CEffect
	: public CGameObject
{
private:
	CAnime *m_anime;
	bool m_visible;

public:
	CEffect(CState *state);
	~CEffect(void);

	bool GetVisible() { return m_visible; }
	void SetVisible(bool v) { m_visible = v; }

	void Play();

	void Update(float dt);
	void Draw(float dt);
};
