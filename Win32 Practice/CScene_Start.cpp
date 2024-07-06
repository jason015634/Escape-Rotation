#include "pch.h"
#include "CCore.h"

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

#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CTile.h"
#include "CCamera.h"

#include "CCollisionMgr.h"
#include "CSoundMgr.h"
#include "CKeyMgr.h"

#include "CBtnUI.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CPanelUI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

void ChangeSceneLoad_Start(DWORD_PTR, DWORD_PTR);
void ExitGame_Start(DWORD_PTR, DWORD_PTR);
void ResumeGame_Start(DWORD_PTR, DWORD_PTR);

bool bSettingOn_Start = false;

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{

}


void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TITLE);
	}

	// 
	if (KEY_TAP(KEY::ESC) && !bSettingOn_Start)
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
		pResumeBtn->SetClickedCallBack(ResumeGame_Start,0,0);

		CBtnUI* pLoadGameBtn = new CBtnUI;
		pLoadGameBtn->SetName(L"LoadGame");
		pLoadGameBtn->SetScale(Vec2(240.f, 60.f));
		pLoadGameBtn->SetPos(Vec2(235.f, 305.f));
		pLoadGameBtn->SetClickedCallBack(ChangeSceneLoad_Start, 0, 0);

		CBtnUI* pExitGameBtn = new CBtnUI;
		pExitGameBtn->SetName(L"ExitGame");
		pExitGameBtn->SetScale(Vec2(240.f, 60.f));
		pExitGameBtn->SetPos(Vec2(235.f, 425.f));
		pExitGameBtn->SetClickedCallBack(ExitGame_Start, 0, 0);

		m_pUI->AddChild(pResumeBtn);
		m_pUI->AddChild(pLoadGameBtn);
		m_pUI->AddChild(pExitGameBtn);

		AddObject(m_pUI, GROUP_TYPE::UI);

		bSettingOn_Start = true;
	}

	
}

void CScene_Start::Enter()
{
	CScene::SetRotateState(0);
	//CPathMgr::GetInst()->init();

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// ��� �ؽ��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"GameBackground_Blue", L"texture\\game_background_blue.bmp");
	SetBackTexture(pTex);

	// Ÿ�� ��ġ
	CreateTile(64, 64);
	wstring szname = L"tile\\Stage09.tile";
	LoadTile(szname);

	// Player �߰� 
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(1728.f, 1750.f));
	pObj->SetScale(Vec2(40.f, 80.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	


	// --------ui �߰� test--------
// 	CUI* pPanelUI = new CPanelUI;
// 	pPanelUI->SetName(L"ParentUI1");
// 	pPanelUI->SetScale(Vec2(500.f, 300.f));
// 	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));
// 
// 	CBtnUI* pBtnUI = new CBtnUI;
// 	pBtnUI->SetName(L"ChildUI1");
// 	pBtnUI->SetScale(Vec2(100.f, 40.f));
// 	pBtnUI->SetPos(Vec2(0.f, 0.f));
// 
// 	pPanelUI->AddChild(pBtnUI);
// 	AddObject(pPanelUI, GROUP_TYPE::UI);
// 
// 	// ��ư Ŭ�� �̺�Ʈ �ݹ��Լ�
// 	pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
// 
// 	// ���纻 UI
// 	CUI* pClonePanel = pPanelUI->Clone();
// 	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
// 	AddObject(pClonePanel, GROUP_TYPE::UI);
// 
// 	m_pUI = pClonePanel;

		

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


	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹üũ
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
	CSoundMgr::GetInst()->init();
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Title_BGM);
	bSettingOn_Start = false;

	start();
}

void ChangeSceneLoad_Start(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	ChangeScene(SCENE_TYPE::LEVEL);
}

void ExitGame_Start(DWORD_PTR, DWORD_PTR)
{
	PostQuitMessage(0);
}


 void ResumeGame_Start(DWORD_PTR, DWORD_PTR)
 {
	 CSceneMgr::GetInst()->GetCurScene()->PopObject(GROUP_TYPE::UI);
	 bSettingOn_Start = false;
 }


void CScene_Start::Exit()
{
	DeleteAll();
	CSoundMgr::GetInst()->StopMusic();
	CCollisionMgr::GetInst()->Reset();
}
