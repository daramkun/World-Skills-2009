#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class CGraphics
{
	friend class CImg;
	friend class CFnt;
private:
	IDirect3D9 *m_d3d;
	IDirect3DDevice9 *m_d3dDevice;
	ID3DXSprite *m_d3dSprite;

public:
	CGraphics(void);
	~CGraphics(void);

	bool Create(HWND hWnd);
	void Destroy();

	void Clear(D3DCOLOR color);

	void Begin();
	void End();

	void Rendering();
};

extern CGraphics g_Graphics;