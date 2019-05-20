#pragma once

class CState
{
public:
	CState(void);
	~CState(void);

	virtual void Initial() {};
	virtual void Update(double et) {};
	virtual void Draw() {};
	virtual void Destroy() {};
};
