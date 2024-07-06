#include "pch.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "CCore.h"
#include "resource.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CEventMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"

#include "CUI.h"
#include "CUIMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CPlayer.h"
// 버튼에 함수포인터로 등록할 함수
//void CB_SaveTileData(DWORD_PTR, DWORD_PTR);
//void CB_LoadTileData(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
{

}
CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{

	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(40.f, 80.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	CScene::SetRotateState(0);
	CPathMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Stage_BGM);

	//타일 생성
	CreateTile(64, 64);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

}


void CScene_Tool::Exit()
{
	CSoundMgr::GetInst()->Release();
	DeleteAll();
}


void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();
	

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}

	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTileData();
	}

	if (KEY_TAP(KEY::SPACE))
	{
		LoadTileData();
	}

}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{

	   Vec2 vMousePos = MOUSE_POS;
	   vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

	   int iTileX = (int)GetTileX();
	   int iTileY = (int)GetTileY();

	   int iCol = (int)vMousePos.x / TILE_SIZE;
	   int iRow = (int)vMousePos.y / TILE_SIZE;

	   if (vMousePos.x < 0.f || iTileX <= iCol
		  || vMousePos.y < 0.f || iTileY <= iRow)
	   {
		  return;
	   }

	   UINT iIdx = iRow * iTileX + iCol;

	   const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	   ((CTile*)vecTile[iIdx])->AddImgIdx();
	}
	else if (KEY_TAP(KEY::RBTN))
	{

	   Vec2 vMousePos = MOUSE_POS;
	   vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

	   int iTileX = (int)GetTileX();
	   int iTileY = (int)GetTileY();

	   int iCol = (int)vMousePos.x / TILE_SIZE;
	   int iRow = (int)vMousePos.y / TILE_SIZE;

	   if (vMousePos.x < 0.f || iTileX <= iCol
		  || vMousePos.y < 0.f || iTileY <= iRow)
	   {
		  return;
	   }

	   UINT iIdx = iRow * iTileX + iCol;

	   const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	   ((CTile*)vecTile[iIdx])->SubImgIDx();
	}
}


// ==============================
// Tile Count Window Proc
// ==============================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT3, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT4, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			
			// ToolScene인지 확인
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{

	// 커널 오브젝트
	FILE* pFile = nullptr;				// RAM에 저장된 데이터와 파일 저장 장치를 이어주는 Stream역할 (연결 장치)

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");		// 바이너리 모드로 쓰기 
	assert(pFile);

	// 데이터 저장
	// 타일 가로세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장할 데이터를 저장
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		{
			((CTile*)vecTile[i])->Save(pFile);
		}
	}

	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	//Modal
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;


	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		wstring strRelattivePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelattivePath);
	}
}