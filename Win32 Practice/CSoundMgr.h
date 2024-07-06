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
	// FMOD �ý���
	FMOD_SYSTEM* m_pSystem;
	// ������� ���ҽ��� ������ ����
	FMOD_SOUND* m_pBGM[(UINT)BGM_SOUND::END];
	// ȿ���� ���ҽ��� ������ ����
	FMOD_SOUND* m_pSFX[(UINT)SFX_SOUND::END];
	// ������ǰ� ȿ���� ä��
	FMOD_CHANNEL* m_pChannel[(UINT)CH::END];
	bool m_isPlaying;
};
