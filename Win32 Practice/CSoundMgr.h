#pragma once

#define MAX_SIZE_SOUND 7
#define EFFECT_MAX_SIZE 9



using namespace FMOD;

class CSoundMgr
{
	SINGLE(CSoundMgr);
public:
	void PlayBGM(BGM_SOUND soundnum);
	void PlaySFX(SFX_SOUND soundnum);

	void StopMusic();
	void init();
	void Release();

private:
	// FMOD 시스템
	FMOD_SYSTEM* m_pSystem;
	// 배경음악 리소스를 저장할 변수
	FMOD_SOUND* m_pBGM[(UINT)BGM_SOUND::END];
	// 효과음 리소스를 저장할 변수
	FMOD_SOUND* m_pSFX[(UINT)SFX_SOUND::END];
	// 배경음악과 효과음 채널
	FMOD_CHANNEL* m_pChannel[(UINT)CH::END];
	bool m_isPlaying;
};
