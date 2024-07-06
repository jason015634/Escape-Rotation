#include "pch.h"
#include "CSoundMgr.h"



void CSoundMgr::init()
{
	// 시스템 초기화
	FMOD_System_Create(&m_pSystem, FMOD_VERSION);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	// BGM 리소스 추가
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\BGM\\Stage_BGM.wav", FMOD_LOOP_NORMAL, 0, &m_pBGM[(UINT)BGM_SOUND::Stage_BGM]);
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\BGM\\Title_BGM.wav", FMOD_LOOP_NORMAL, 0, &m_pBGM[(UINT)BGM_SOUND::Title_BGM]);

	// SFX 리소스 추가
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\Lever_Off.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::Lever_Off]);	
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\Lever_On.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::Lever_On]);
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\Platform_Destroy.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::Platform_Destroy]);
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\Player_Jump.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::Player_Jump]);
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\Portal.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::Portal]);
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\Rotate.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::Rotate]);
	FMOD_System_CreateSound(m_pSystem, "content\\sound\\SFX\\UI_Click.wav", FMOD_LOOP_OFF, 0, &m_pSFX[(UINT)SFX_SOUND::UI_Click]);

	m_isPlaying = false;
}

//사운드 재생
void CSoundMgr::PlayBGM(BGM_SOUND soundnum)
{
	if (!m_isPlaying)
	{
		FMOD_System_PlaySound(m_pSystem, m_pBGM[(UINT)soundnum], 0, 0, &m_pChannel[(UINT)CH::CH_BGM]);
		m_isPlaying = true;
	}

	FMOD_Channel_SetVolume(m_pChannel[(UINT)CH::CH_BGM], 0.1f);	// 볼룸 조절 0.f~1.f
}


//효과음
void CSoundMgr::PlaySFX(SFX_SOUND soundnum)
{
	FMOD_System_PlaySound(m_pSystem, m_pSFX[(UINT)soundnum], 0, 0, &m_pChannel[(UINT)CH::CH_SFX]);

	FMOD_Channel_SetVolume(m_pChannel[(UINT)CH::CH_SFX], 0.2f);	// 볼룸 조절 0.f~1.f
}

//사운드 중지
void CSoundMgr::StopMusic()
{
	if (m_isPlaying)
	{
		FMOD_Channel_Stop(m_pChannel[(UINT)CH::CH_BGM]);
		m_isPlaying = false;
	}
}

void CSoundMgr::Release()
{
// 	StopMusic();
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

CSoundMgr::CSoundMgr()
{
}

CSoundMgr::~CSoundMgr()
{
}