#pragma once

#include "State.h"
#include "Img.h"
#include "Fnt.h"

class CStateManager
{
private:
	CState *m_states[3];
	CImg m_fadeImage;
	CFnt m_help;
	int currentState;

	bool m_fadeIn, m_fadeOut;
	int m_fadeAlpha;

public:
	CStateManager(void);
	~CStateManager(void);

	bool Create();
	void Destroy();

	void SetIndex(int index, CState *state);
	void SetState(int index, double dt);

	void Update(double dt);
	void Draw();
};

extern CStateManager g_stateManager;