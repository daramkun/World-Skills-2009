#pragma once

class CDelay
{
private:
	int m_delay;
	float m_elaps;

public:
	CDelay(int delay);

	void Update(float dt);
	void Reset();
	bool Check();
};
