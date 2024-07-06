#include "pch.h"
#include "CScene_CutScene.h"

#include "CCore.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CBtnUI.h"

#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSoundMgr.h"
#include "CSceneMgr.h"

#include "CTexture.h"
#include "CKeyMgr.h"

CScene_CutScene::CScene_CutScene()
	: m_sceneNum(0)
	, m_cutNum(0)
{
	m_pTex[0].push_back(CResMgr::GetInst()->LoadTexture(L"lv01_1", L"texture\\lv01_1.bmp"));
	m_pTex[0].push_back(CResMgr::GetInst()->LoadTexture(L"lv01_2", L"texture\\lv01_2.bmp"));
	m_pTex[0].push_back(CResMgr::GetInst()->LoadTexture(L"lv01_3", L"texture\\lv01_3.bmp"));

	m_pTex[1].push_back(CResMgr::GetInst()->LoadTexture(L"lv02_1", L"texture\\lv02_1.bmp"));
	m_pTex[1].push_back(CResMgr::GetInst()->LoadTexture(L"lv02_2", L"texture\\lv02_2.bmp"));

	m_pTex[2].push_back(CResMgr::GetInst()->LoadTexture(L"lv03_1", L"texture\\lv03_1.bmp"));
	m_pTex[2].push_back(CResMgr::GetInst()->LoadTexture(L"lv03_2", L"texture\\lv03_2.bmp"));

	m_pTex[3].push_back(CResMgr::GetInst()->LoadTexture(L"lv04_1", L"texture\\lv04_1.bmp"));
	m_pTex[3].push_back(CResMgr::GetInst()->LoadTexture(L"lv04_2", L"texture\\lv04_2.bmp"));

	m_pTex[4].push_back(CResMgr::GetInst()->LoadTexture(L"lv05_1", L"texture\\lv05_1.bmp"));
	m_pTex[4].push_back(CResMgr::GetInst()->LoadTexture(L"lv05_2", L"texture\\lv05_2.bmp"));

	m_pTex[5].push_back(CResMgr::GetInst()->LoadTexture(L"lv06_1", L"texture\\lv06_1.bmp"));
	m_pTex[5].push_back(CResMgr::GetInst()->LoadTexture(L"lv06_2", L"texture\\lv06_2.bmp"));

	m_pTex[6].push_back(CResMgr::GetInst()->LoadTexture(L"event", L"texture\\event.bmp"));
	m_pTex[6].push_back(CResMgr::GetInst()->LoadTexture(L"lv07_1", L"texture\\lv07_1.bmp"));
	m_pTex[6].push_back(CResMgr::GetInst()->LoadTexture(L"lv07_2", L"texture\\lv07_2.bmp"));

	m_pTex[7].push_back(CResMgr::GetInst()->LoadTexture(L"lv08_1", L"texture\\lv08_1.bmp"));
	m_pTex[7].push_back(CResMgr::GetInst()->LoadTexture(L"lv08_2", L"texture\\lv08_2.bmp"));

	m_pTex[8].push_back(CResMgr::GetInst()->LoadTexture(L"lv09_1", L"texture\\lv09_1.bmp"));
	m_pTex[8].push_back(CResMgr::GetInst()->LoadTexture(L"lv09_2", L"texture\\lv09_2.bmp"));

	m_pTex[9].push_back(CResMgr::GetInst()->LoadTexture(L"lv10_1", L"texture\\lv10_1.bmp"));
	m_pTex[9].push_back(CResMgr::GetInst()->LoadTexture(L"lv10_2", L"texture\\lv10_2.bmp"));

	m_pTex[10].push_back(CResMgr::GetInst()->LoadTexture(L"lv11_1", L"texture\\lv11_1.bmp"));
	m_pTex[10].push_back(CResMgr::GetInst()->LoadTexture(L"lv11_2", L"texture\\lv11_2.bmp"));

	m_pTex[11].push_back(CResMgr::GetInst()->LoadTexture(L"lv12_1", L"texture\\lv12_ending_1.bmp"));
	m_pTex[11].push_back(CResMgr::GetInst()->LoadTexture(L"lv12_2", L"texture\\lv12_ending_2.bmp"));
	m_pTex[11].push_back(CResMgr::GetInst()->LoadTexture(L"lv12_3", L"texture\\lv12_ending_3.bmp"));
}

CScene_CutScene::~CScene_CutScene()
{

}

void CScene_CutScene::update()
{
	CScene::update(); 
// 	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);

	if (KEY_TAP(KEY::SPACE))
	{
		if (m_pTex[m_sceneNum].size() > m_cutNum)
		{
			SetBackTexture(m_pTex[m_sceneNum][m_cutNum++]);
		}
		else
		{
			ChangeScene((SCENE_TYPE)GetNextScene());
		}		
	}
}

void CScene_CutScene::Enter()
{
	m_sceneNum = (int)GetNextScene();
	if (m_sceneNum == 2)
	{
		m_sceneNum = 11;
	}
	else
	{
		m_sceneNum -= 6;
	}

	m_cutNum = 0;
	SetBackTexture(m_pTex[m_sceneNum][m_cutNum++]);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
}

void CScene_CutScene::Exit()
{
// 	CSoundMgr::GetInst()->StopMusic();

	DeleteAll();
	SetBackTexture(nullptr);
}

