#pragma once

#include "DxUtil.h"

#include <dshow.h>
#pragma comment (lib, "strmiids.lib")

class CSound
{
private:
	IGraphBuilder *m_graphBuilder;
	IMediaControl *m_mediaControl;
	IMediaPosition *m_mediaPosition;

	bool m_isPlay;
	bool m_isLoop;

public:
	CSound(wchar_t *filename);
	~CSound(void);

	void Play(bool isLoop);
	void Stop();

	void Update();
};
