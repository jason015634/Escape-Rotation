#include "pch.h"
#include "CScene_Stage_08.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CGround.h"
#include "CLever.h"
#include "CLazer.h"
#include "CSpike.h"
#include "CPortal.h"

#include "CUIMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CTile.h"
#include "CCamera.h"
#include "CResMgr.h"

#include "CCollisionMgr.h"

#include "CSoundMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

void ChangeSceneLoad_08(DWORD_PTR, DWORD_PTR);
void ExitGame_08(DWORD_PTR, DWORD_PTR);
void ResumeGame_08(DWORD_PTR, DWORD_PTR);

bool bSettingOn_08 = false;

CScene_Stage_08::CScene_Stage_08()
{

}

CScene_Stage_08::~CScene_Stage_08()
{

}

void CScene_Stage_08::update()
{
	CScene::update();
// 	if (KEY_TAP(KEY::ENTER))
// 	{
// 		ChangeScene(SCENE_TYPE::STAGE_09);
// 	}

	if (KEY_TAP(KEY::ESC) && !bSettingOn_08)
	{
		//SettingUI
		m_pUI = new CPanelUI;
		m_pUI->SetName(L"SettingUI");
		m_pUI->SetScale(Vec2(710.f, 605.f));
		m_pUI->SetPos(Vec2(605.f, 240.f));
		//CResMgr::GetInst()->LoadTexture(L"SettingUI", L"texture\\setting.bmp");
		CTexture* settingTex = CResMgr::GetInst()->LoadTexture(L"SettingUI", L"texture\\setting.bmp");
		((CPanelUI*)m_pUI)->SetTexture(settingTex);

		CBtnUI* pResumeBtn = new CBtnUI;
		pResumeBtn->SetName(L"pResume");
		pResumeBtn->SetScale(Vec2(240.f, 60.f));
		pResumeBtn->SetPos(Vec2(235.f, 185.f));
		pResumeBtn->SetClickedCallBack(ResumeGame_08, 0, 0);

		CBtnUI* pLoadGameBtn = new CBtnUI;
		pLoadGameBtn->SetName(L"LoadGame");
		pLoadGameBtn->SetScale(Vec2(240.f, 60.f));
		pLoadGameBtn->SetPos(Vec2(235.f, 305.f));
		pLoadGameBtn->SetClickedCallBack(ChangeSceneLoad_08, 0, 0);

		CBtnUI* pExitGameBtn = new CBtnUI;
		pExitGameBtn->SetName(L"ExitGame");
		pExitGameBtn->SetScale(Vec2(240.f, 60.f));
		pExitGameBtn->SetPos(Vec2(235.f, 425.f));
		pExitGameBtn->SetClickedCallBack(ExitGame_08, 0, 0);

		m_pUI->AddChild(pResumeBtn);
		m_pUI->AddChild(pLoadGameBtn);
		m_pUI->AddChild(pExitGameBtn);

		AddObject(m_pUI, GROUP_TYPE::UI);

		bSettingOn_08 = true;
	}
// 	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);

}

void CScene_Stage_08::Enter()
{
	CScene::SetRotateState(0);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// ��� �ؽ��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"GameBackground_Green", L"texture\\game_background_green.bmp");
	SetBackTexture(pTex);

	// TileObject ��ġ
	CreateTile(64, 64);
	wstring szname = L"tile\\Stage08.tile";
	LoadTile(szname);

	// PlayerObject ��ġ
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(1728.f, 1750.f));
	pObj->SetScale(Vec2(40.f, 80.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// UI
	CUI* pHackerUI = new CPanelUI;
	pHackerUI->SetName(L"HackerUI");
	pHackerUI->SetScale(Vec2(192.f, 192.f));
	pHackerUI->SetPos(Vec2(1706.f, 866.f));
	AddObject(pHackerUI, GROUP_TYPE::UI);
	((CPanelUI*)pHackerUI)->SetTexture(CResMgr::GetInst()->LoadTexture(L"HackerUI", L"texture\\Hacker_1.bmp"));


	CUI* pRotateUI_Q = new CPanelUI;
	pRotateUI_Q->SetName(L"RotateUI_Q");
	pRotateUI_Q->SetScale(Vec2(64.f, 64.f));
	pRotateUI_Q->SetPos(Vec2(1727.f, 780.f));
	AddObject(pRotateUI_Q, GROUP_TYPE::UI);
	((CPanelUI*)pRotateUI_Q)->SetTexture(CResMgr::GetInst()->LoadTexture(L"RotateUI_Q", L"texture\\but_Q_64.bmp"));

	CUI* pRotateUI_E = new CPanelUI;
	pRotateUI_E->SetName(L"RotateUI_E");
	pRotateUI_E->SetScale(Vec2(64.f, 64.f));
	pRotateUI_E->SetPos(Vec2(1813.f, 780.f));
	AddObject(pRotateUI_E, GROUP_TYPE::UI);
	((CPanelUI*)pRotateUI_E)->SetTexture(CResMgr::GetInst()->LoadTexture(L"RotateUI_E", L"texture\\but_E_64.bmp"));

	// Lever ��ġ
	CLever* pLever = new CLever;
	pLever->SetPos(Vec2(928.f, 1952.f));
	pLever->SetScale(Vec2(64.f, 64.f));
	AddObject(pLever, GROUP_TYPE::LEVER);

	// Lever ��ġ
	CLever* pLever1 = new CLever;
	pLever1->SetPos(Vec2(2464.f, 2144.f));
	pLever1->SetScale(Vec2(64.f, 64.f));
	((CLever*)pLever1)->SetIdx(3);
	AddObject(pLever1, GROUP_TYPE::LEVER);

	for (int i = 0; i < 3; i++)
	{
		CLazer* pLazer = new CLazer;
		pLazer->SetPos(Vec2(1952.f, 1632.f + 64.f * i));
		pLazer->SetScale(Vec2(64.f, 64.f));
		(pLazer)->SetOwnerLever((CLever*)pLever);
		pLazer->SetIdx(1);
		AddObject(pLazer, GROUP_TYPE::LAZER);
	}

	for (int i = 0; i < 4; i++)
	{
		CLazer* pLazer = new CLazer;
		pLazer->SetPos(Vec2(1184.f + 64.f * i, 2016.f));
		pLazer->SetScale(Vec2(64.f, 64.f));
		(pLazer)->SetOwnerLever((CLever*)pLever);
		AddObject(pLazer, GROUP_TYPE::LAZER);
	}

	CLazer* pLazer = new CLazer;
	pLazer->SetPos(Vec2(2208.f, 1248.f));
	pLazer->SetScale(Vec2(64.f, 64.f));
	(pLazer)->SetOwnerLever((CLever*)pLever1);
	pLazer->SetIdx(1);
	AddObject(pLazer, GROUP_TYPE::LAZER);

	for (int i = 0; i < 9; i++)
	{
		CLazer* pLazer = new CLazer;
		pLazer->SetPos(Vec2(2336.f + 64.f * i, 1568.f));
		pLazer->SetScale(Vec2(64.f, 64.f));
		(pLazer)->SetOwnerLever((CLever*)pLever1);
		AddObject(pLazer, GROUP_TYPE::LAZER);
	}

	// �浹 ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LEVER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LAZER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SPIKE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);

	CCamera::GetInst()->SetTarget(pObj);

	// Camera Look ����
	// ���� ó�� ī�޶� �ٶ󺸰� �ִ� ��ġ�� �ػ� ���߾�
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// ���� ���ҽ��� ����
	// (���� �Ŵ����� ���ؼ�) ���带 �÷����Ѵ�
// 	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	bSettingOn_08 = false;

	start();
}

void ChangeSceneLoad_08(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	ChangeScene(SCENE_TYPE::LEVEL);
}

void ExitGame_08(DWORD_PTR, DWORD_PTR)
{
	BOOL DestroyWindow(HWND Hwnd);
	PostQuitMessage(0);
}


void ResumeGame_08(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSceneMgr::GetInst()->GetCurScene()->PopObject(GROUP_TYPE::UI);
	bSettingOn_08 = false;
}


void CScene_Stage_08::Exit()
{
	DeleteAll();
// 	CSoundMgr::GetInst()->StopMusic();
	CCollisionMgr::GetInst()->Reset();
}
