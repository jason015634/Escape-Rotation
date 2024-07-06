#include "pch.h"
#include "CScene_Title.h"

#include "CCore.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CBtnUI.h"

#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSoundMgr.h"
#include "CSceneMgr.h"

#include "CTexture.h"
#include "CCamera.h"
#include "CKeyMgr.h"

void ChangeSceneStart(DWORD_PTR, DWORD_PTR);
void ChangeSceneLoad(DWORD_PTR, DWORD_PTR);
void ExitGame(DWORD_PTR, DWORD_PTR);

CScene_Title::CScene_Title()
{

}

CScene_Title::~CScene_Title()
{
}


void CScene_Title::update()
{
	CScene::update();
// 	if (KEY_TAP(KEY::ENTER))
// 	{
// 		ChangeScene(SCENE_TYPE::LEVEL);
// 	}

}

void CScene_Title::Enter()
{
	// Ÿ��Ʋ ȭ�� �ؽ��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Title", L"texture\\Title.bmp");
	SetBackTexture(pTex);

	CBtnUI* pNewButtonBtn = new CBtnUI;
	pNewButtonBtn->SetName(L"NewGame");
	pNewButtonBtn->SetScale(Vec2(240.f, 60.f));
	pNewButtonBtn->SetPos(Vec2(840.f, 735.f));
	AddObject(pNewButtonBtn, GROUP_TYPE::UI);

	CBtnUI* pLoadGameBtn = new CBtnUI;
	pLoadGameBtn->SetName(L"LoadGame");
	pLoadGameBtn->SetScale(Vec2(240.f, 60.f));
	pLoadGameBtn->SetPos(Vec2(840.f, 821.f));
	AddObject(pLoadGameBtn, GROUP_TYPE::UI);

	CBtnUI* pExitGameBtn = new CBtnUI;
	pExitGameBtn->SetName(L"ExitGame");
	pExitGameBtn->SetScale(Vec2(240.f, 60.f));
	pExitGameBtn->SetPos(Vec2(840.f, 907.f));
	AddObject(pExitGameBtn, GROUP_TYPE::UI);

	pNewButtonBtn->SetClickedCallBack(ChangeSceneStart, 0, 0);
	pLoadGameBtn->SetClickedCallBack(ChangeSceneLoad, 0, 0);
	pExitGameBtn->SetClickedCallBack(ExitGame, 0, 0);

	// ���� ���ҽ��� ����
	// (���� �Ŵ����� ���ؼ�) ���带 �÷����Ѵ�
// 	CSoundMgr::GetInst()->init();
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Title_BGM);

	start();
}

void ChangeSceneStart(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_01);
}

void ChangeSceneLoad(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	ChangeScene(SCENE_TYPE::LEVEL);
}

void ExitGame(DWORD_PTR, DWORD_PTR)
{
	BOOL DestroyWindow(HWND Hwnd);
	PostQuitMessage(0);
}

void CScene_Title::Exit()
{
	DeleteAll();
	SetBackTexture(nullptr);
	// �������ϸ� ȿ���� ����
	// timeMgr�� ���ؼ� �ʸ� ���� ���ϰ��� true�� release
	//CSoundMgr::GetInst()->Release();
// 	CSoundMgr::GetInst()->StopMusic();
}
