#include "pch.h"
#include "CScene_Level.h"

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

void ChangeSceneStage_01(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_02(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_03(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_04(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_05(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_06(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_07(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_08(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_09(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_10(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_11(DWORD_PTR, DWORD_PTR);
void ChangeSceneStage_12(DWORD_PTR, DWORD_PTR);
void ChangeSceneTitle(DWORD_PTR, DWORD_PTR);

CScene_Level::CScene_Level()
{
}

CScene_Level::~CScene_Level()
{
}

void CScene_Level::update()
{

	CScene::update();

}

void CScene_Level::Enter()
{
	// 레벨 선택 화면 텍스쳐 설정
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Level", L"texture\\Level.bmp");
	SetBackTexture(pTex);

	CBtnUI* but_01 = new CBtnUI;
	but_01->SetName(L"but_01");
	but_01->SetScale(Vec2(96.f, 80.f));
	but_01->SetPos(Vec2(724.f, 407.f));
	AddObject(but_01, GROUP_TYPE::UI);

	CBtnUI* but_02 = new CBtnUI;
	but_02->SetName(L"but_02");
	but_02->SetScale(Vec2(96.f, 80.f));
	but_02->SetPos(Vec2(864.f, 407.f));
	AddObject(but_02, GROUP_TYPE::UI);

	CBtnUI* but_03 = new CBtnUI;
	but_03->SetName(L"but_03");
	but_03->SetScale(Vec2(96.f, 80.f));
	but_03->SetPos(Vec2(1001.f, 407.f));
	AddObject(but_03, GROUP_TYPE::UI);

	CBtnUI* but_04 = new CBtnUI;
	but_04->SetName(L"but_04");
	but_04->SetScale(Vec2(96.f, 80.f));
	but_04->SetPos(Vec2(1141.f, 407.f));
	AddObject(but_04, GROUP_TYPE::UI);

	CBtnUI* but_05 = new CBtnUI;
	but_05->SetName(L"but_05");
	but_05->SetScale(Vec2(96.f, 80.f));
	but_05->SetPos(Vec2(724.f, 500.f));
	AddObject(but_05, GROUP_TYPE::UI);

	CBtnUI* but_06 = new CBtnUI;
	but_06->SetName(L"but_06");
	but_06->SetScale(Vec2(96.f, 80.f));
	but_06->SetPos(Vec2(864.f, 500.f));
	AddObject(but_06, GROUP_TYPE::UI);

	CBtnUI* but_07 = new CBtnUI;
	but_07->SetName(L"but_07");
	but_07->SetScale(Vec2(96.f, 80.f));
	but_07->SetPos(Vec2(1001.f, 500.f));
	AddObject(but_07, GROUP_TYPE::UI);

	CBtnUI* but_08 = new CBtnUI;
	but_08->SetName(L"but_08");
	but_08->SetScale(Vec2(96.f, 80.f));
	but_08->SetPos(Vec2(1141.f, 500.f));
	AddObject(but_08, GROUP_TYPE::UI);

	CBtnUI* but_09 = new CBtnUI;
	but_09->SetName(L"but_09");
	but_09->SetScale(Vec2(96.f, 80.f));
	but_09->SetPos(Vec2(724.f, 598.f));
	AddObject(but_09, GROUP_TYPE::UI);

	CBtnUI* but_10 = new CBtnUI;
	but_10->SetName(L"but_10");
	but_10->SetScale(Vec2(96.f, 80.f));
	but_10->SetPos(Vec2(864.f, 598.f));
	AddObject(but_10, GROUP_TYPE::UI);

	CBtnUI* but_11 = new CBtnUI;
	but_11->SetName(L"but_11");
	but_11->SetScale(Vec2(96.f, 80.f));
	but_11->SetPos(Vec2(1001.f, 598.f));
	AddObject(but_11, GROUP_TYPE::UI);

	CBtnUI* but_12 = new CBtnUI;
	but_12->SetName(L"but_12");
	but_12->SetScale(Vec2(96.f, 80.f));
	but_12->SetPos(Vec2(1141.f, 598.f));
	AddObject(but_12, GROUP_TYPE::UI);

	CBtnUI* titleButton = new CBtnUI;
	titleButton->SetName(L"Title Scene");
	titleButton->SetScale(Vec2(474.f, 94.f));
	titleButton->SetPos(Vec2(744.f, 694.f));
	AddObject(titleButton, GROUP_TYPE::UI);

	but_01->SetClickedCallBack(ChangeSceneStage_01, 0, 0);
	but_02->SetClickedCallBack(ChangeSceneStage_02, 0, 0);
	but_03->SetClickedCallBack(ChangeSceneStage_03, 0, 0);
	but_04->SetClickedCallBack(ChangeSceneStage_04, 0, 0);
	but_05->SetClickedCallBack(ChangeSceneStage_05, 0, 0);
	but_06->SetClickedCallBack(ChangeSceneStage_06, 0, 0);
	but_07->SetClickedCallBack(ChangeSceneStage_07, 0, 0);
	but_08->SetClickedCallBack(ChangeSceneStage_08, 0, 0);
	but_09->SetClickedCallBack(ChangeSceneStage_09, 0, 0);
	but_10->SetClickedCallBack(ChangeSceneStage_10, 0, 0);
	but_11->SetClickedCallBack(ChangeSceneStage_11, 0, 0);
	but_12->SetClickedCallBack(ChangeSceneStage_12, 0, 0);
	titleButton->SetClickedCallBack(ChangeSceneTitle, 0, 0);


// 	CSoundMgr::GetInst()->init();
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Title_BGM);
	start();
}

void ChangeSceneStage_01(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_01);
}
void ChangeSceneStage_02(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_02);
}
void ChangeSceneStage_03(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_03);
}
void ChangeSceneStage_04(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_04);
}
void ChangeSceneStage_05(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_05);
}
void ChangeSceneStage_06(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_06);
}
void ChangeSceneStage_07(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_07);
}
void ChangeSceneStage_08(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_08);
}
void ChangeSceneStage_09(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_09);
}
void ChangeSceneStage_10(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_10);
}
void ChangeSceneStage_11(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::STAGE_11);
}
void ChangeSceneStage_12(DWORD_PTR, DWORD_PTR)
{	
	CSoundMgr::GetInst()->StopMusic();
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);
	ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, SCENE_TYPE::TITLE);
}
void ChangeSceneTitle(DWORD_PTR, DWORD_PTR)
{
	CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::UI_Click);
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Title_BGM);
	ChangeScene(SCENE_TYPE::TITLE);
}


void CScene_Level::Exit()
{
	DeleteAll();
// 	CSoundMgr::GetInst()->StopMusic();
}

