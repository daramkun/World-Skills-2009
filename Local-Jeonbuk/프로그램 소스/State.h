#pragma once

class CState
{
public:
	CState(void);
	~CState(void);

	virtual void Initial(){};
	virtual void Update(double dt){};
	virtual void Draw(){};
	virtual void Destroy(){};
};
