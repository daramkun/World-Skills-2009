#include "Sound.h"

CSound::CSound(wchar_t *filename)
{
	CoInitialize(NULL);

	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
		(void**)&m_graphBuilder);

	m_graphBuilder->RenderFile(filename, NULL);

	m_graphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_mediaControl);
	m_graphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_mediaPosition);
}

CSound::~CSound(void)
{
	SafeRelease(m_graphBuilder);
	SafeRelease(m_mediaPosition);
	SafeRelease(m_mediaControl);
	CoUninitialize();
}

void CSound::Play(bool isLoop)
{
	Stop();
	m_mediaControl->Run();
	m_isLoop = isLoop;
	m_isPlay = true;
}

void CSound::Stop()
{
	m_mediaControl->StopWhenReady();
	m_mediaPosition->put_CurrentPosition(0);
	m_isPlay = false;
}

void CSound::Update()
{
	if(!m_isPlay) return;

	REFTIME cur, dur;
	m_mediaPosition->get_CurrentPosition(&cur);
	m_mediaPosition->get_Duration(&dur);
	
	if(cur == dur || cur == 0)
	{
		Stop(); 
		
		if(m_isLoop)
			Play(true);
	}
}