#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include "DxUtil.h"
#include "Delay.h"

class CSprite;

class CGraphics
{
	friend class CSprite;
private:
	IDirect3D9 *m_d3d;
	IDirect3DDevice9 *m_d3dDevice;
	ID3DXSprite *m_d3dSprite;
	D3DPRESENT_PARAMETERS m_pp;
	float m_quakeValue;

	CDelay *m_delay;

public:
	CGraphics(HWND hWnd);
	~CGraphics(void);

	void Clear(D3DCOLOR, float);
	void Present();

	// 그림을 그린다
	void Draw(CSprite* spr, float x, float y);
	void Draw(CSprite* spr, float x, float y, float sw, float sh);
	void Draw(CSprite* spr, float x, float y, float sw, float sh, float angle, D3DCOLOR color = 0xffffffff);
	// 그림을 그린다(지진 효과 無)
	void DrawNoQuake(CSprite* spr, float x, float y, float sw, float sh, D3DCOLOR color = 0xffffffff);
	// 그림을 일부만 그린다(지진 효과 無)
	void DrawClip(CSprite* spr, float x, float y, float cx, float cy, float cw, float ch);

	// 지진 효과
	bool EarthQuake();
	// 약한 지진 효과
	void WeakQuake();
};
