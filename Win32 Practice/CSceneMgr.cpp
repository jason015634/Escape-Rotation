#include "pch.h"
#include "CSceneMgr.h"
#include "CEventMgr.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_Title.h"
#include "CScene_Level.h"
#include "CScene_Stage_01.h"
#include "CScene_Stage_02.h"
#include "CScene_Stage_03.h"
#include "CScene_Stage_04.h"
#include "CScene_Stage_05.h"
#include "CScene_Stage_06.h"
#include "CScene_Stage_07.h"
#include "CScene_Stage_08.h"
#include "CScene_Stage_09.h"
#include "CScene_Stage_10.h"
#include "CScene_Stage_11.h"
#include "CScene_CutScene.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
		
	}
}

void CSceneMgr::init()
{
// 	int a = 0;
	//Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");

	m_arrScene[(UINT)SCENE_TYPE::LEVEL] = new CScene_Level;
	m_arrScene[(UINT)SCENE_TYPE::LEVEL]->SetName(L"Level Scene");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"Scene Stage_01");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetName(L"Scene Stage_02");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new CScene_Stage_03;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03]->SetName(L"Scene Stage_03");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_04] = new CScene_Stage_04;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_04]->SetName(L"Scene Stage_04");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_05] = new CScene_Stage_05;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_05]->SetName(L"Scene Stage_05");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_06] = new CScene_Stage_06;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_06]->SetName(L"Scene Stage_06");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_07] = new CScene_Stage_07;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_07]->SetName(L"Scene Stage_07");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_08] = new CScene_Stage_08;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_08]->SetName(L"Scene Stage_08");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_09] = new CScene_Stage_09;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_09]->SetName(L"Scene Stage_09");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_10] = new CScene_Stage_10;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_10]->SetName(L"Scene Stage_10");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_11] = new CScene_Stage_11;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_11]->SetName(L"Scene Stage_11");

	m_arrScene[(UINT)SCENE_TYPE::LEVEL_CUTSCENE] = new CScene_CutScene;
	m_arrScene[(UINT)SCENE_TYPE::LEVEL_CUTSCENE]->SetName(L"CutScene");

	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];
	m_pCurScene->SetSceneIndex(SCENE_TYPE::TITLE);	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();

}

void CSceneMgr::render()
{
	m_pCurScene->render();
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->SetSceneIndex(_eNext);
	m_pCurScene->Enter();
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext, SCENE_TYPE _eNNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->SetSceneIndex(_eNext);
	m_pCurScene->SetNextScene(_eNNext);
	m_pCurScene->Enter();
}