#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CScene_Start.h"
#include "CTile.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CSceneMgr.h"
#include "SelectGDI.h"
#include "CCamera.h"
#include "CCore.h"
#include "CGround.h"
#include "CEmptyObj.h"
#include "CSpike.h"
#include "CLever.h"
#include "CLazer.h"
#include "CPortal.h"
CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_rotateState(0)
	, m_hTempBit(0)
	, m_hTempDC(0)
{
	CPathMgr::GetInst()->init();

}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			//m_arrObj[i] 그룹 벡터의 j 물체 삭제
			delete m_arrObj[i][j];
		}
	}//벡터 안에 있는 값들이 주소 타입이라서 따로 삭제를 해줘야 함

	DeleteDC(m_hTempDC);
	DeleteObject(m_hTempBit);
}

void CScene::Enter()
{

}
void CScene::Exit()
{

}

void CScene::start()
{
	m_hTempBit = CreateCompatibleBitmap(CCore::GetInst()->GetMainDC(), CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y);
	m_hTempDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	SelectObject(m_hTempDC, m_hTempBit);

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->start();
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			// nullptr 문제 생기면 예외처리 추가 : if(m_arrObj[i][j])
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::RotateRight()
{
	Vec2 PlayerPos = m_arrObj[(UINT)GROUP_TYPE::PLAYER][0]->GetPos();
	Vec2 RelativePos;


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if (i == (UINT)GROUP_TYPE::UI)
			continue;
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j]->GetName() != L"LRspike")
			{
				RelativePos = m_arrObj[i][j]->GetPos() - PlayerPos;
				RelativePos = Vec2(-RelativePos.y, RelativePos.x);
				m_arrObj[i][j]->SetPos(Vec2(PlayerPos.x + RelativePos.x, PlayerPos.y + RelativePos.y));
				m_arrObj[i][j]->SetScale(Vec2(m_arrObj[i][j]->GetScale().y, m_arrObj[i][j]->GetScale().x));
				if (m_arrObj[i][j]->GetCollider() != nullptr && m_arrObj[i][j]->GetName() != L"Player")
				{
					// todo

					m_arrObj[i][j]->GetCollider()->SetScale(Vec2(m_arrObj[i][j]->GetCollider()->GetScale().y, m_arrObj[i][j]->GetCollider()->GetScale().x));
					m_arrObj[i][j]->GetCollider()->SetOffsetPos(
						Vec2(m_arrObj[i][j]->GetCollider()->GetOffsetPos().y * (m_rotateState % 2 - 1)
							, m_arrObj[i][j]->GetCollider()->GetOffsetPos().x
						));
				}
			}

			
		}
	}
	m_rotateState++;
	m_rotateState = m_rotateState % 4;
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if (i == (UINT)GROUP_TYPE::UI)
			continue;
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j]->GetName() == L"LRspike")
			{
				RelativePos = m_arrObj[i][j]->GetPos() - PlayerPos;
				RelativePos = Vec2(-RelativePos.y, RelativePos.x);
				m_arrObj[i][j]->SetPos(Vec2(PlayerPos.x + RelativePos.x, PlayerPos.y + RelativePos.y));
				m_arrObj[i][j]->SetScale(Vec2(m_arrObj[i][j]->GetScale().y, m_arrObj[i][j]->GetScale().x));
				if (m_arrObj[i][j]->GetCollider() != nullptr && m_arrObj[i][j]->GetName() != L"Player")
				{
					// todo

					m_arrObj[i][j]->GetCollider()->SetScale(Vec2(m_arrObj[i][j]->GetCollider()->GetScale().y, m_arrObj[i][j]->GetCollider()->GetScale().x));
					m_arrObj[i][j]->GetCollider()->SetOffsetPos(
						Vec2(m_arrObj[i][j]->GetCollider()->GetOffsetPos().y * (m_rotateState % 2 - 1)
							, m_arrObj[i][j]->GetCollider()->GetOffsetPos().x
						));
				}
			}
		}
	}

}

void CScene::RotateLeft()
{
	Vec2 PlayerPos = m_arrObj[(UINT)GROUP_TYPE::PLAYER][0]->GetPos();
	Vec2 RelativePos;

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if (i == (UINT)GROUP_TYPE::UI)
			continue;
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j]->GetName() != L"LRspike")
			{
				RelativePos = m_arrObj[i][j]->GetPos() - PlayerPos;
				RelativePos = Vec2(RelativePos.y, -RelativePos.x);
				m_arrObj[i][j]->SetPos(Vec2(PlayerPos.x + RelativePos.x, PlayerPos.y + RelativePos.y));
				m_arrObj[i][j]->SetScale(Vec2(m_arrObj[i][j]->GetScale().y, m_arrObj[i][j]->GetScale().x));
				if (m_arrObj[i][j]->GetCollider() != nullptr && m_arrObj[i][j]->GetName() != L"Player")
				{
					// 좌우
					m_arrObj[i][j]->GetCollider()->SetScale(Vec2(m_arrObj[i][j]->GetCollider()->GetScale().y, m_arrObj[i][j]->GetCollider()->GetScale().x));
					m_arrObj[i][j]->GetCollider()->SetOffsetPos(
						Vec2(m_arrObj[i][j]->GetCollider()->GetOffsetPos().y
							, m_arrObj[i][j]->GetCollider()->GetOffsetPos().x * (m_rotateState % 2) * (-1)
						));
				}
			}


		}
	}

	m_rotateState--;
	if (m_rotateState < 0)
		m_rotateState += 4;
	
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if (i == (UINT)GROUP_TYPE::UI)
			continue;
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j]->GetName() == L"LRspike")
			{
				RelativePos = m_arrObj[i][j]->GetPos() - PlayerPos;
				RelativePos = Vec2(RelativePos.y, -RelativePos.x);
				m_arrObj[i][j]->SetPos(Vec2(PlayerPos.x + RelativePos.x, PlayerPos.y + RelativePos.y));
				m_arrObj[i][j]->SetScale(Vec2(m_arrObj[i][j]->GetScale().y, m_arrObj[i][j]->GetScale().x));
				if (m_arrObj[i][j]->GetCollider() != nullptr && m_arrObj[i][j]->GetName() != L"Player")
				{
					// 좌우
					m_arrObj[i][j]->GetCollider()->SetScale(Vec2(m_arrObj[i][j]->GetCollider()->GetScale().y, m_arrObj[i][j]->GetCollider()->GetScale().x));
					m_arrObj[i][j]->GetCollider()->SetOffsetPos(
						Vec2(m_arrObj[i][j]->GetCollider()->GetOffsetPos().y
							, m_arrObj[i][j]->GetCollider()->GetOffsetPos().x * (m_rotateState % 2) * (-1)
						));
				}
			}
			

		}
	}
}

void CScene::RenderRotation(float radian, Vec2 playerPosition)
{
	// 플레이어 위치를 중심으로 회전

	// PlgBlt : 좌상단, 우상단, 좌하단의 좌표를 가지고 있는 POINT 구조체 배열을 필요로 한다 - m_rotatePoint

	// 텍스쳐의 중심에서부터 각각의 point 좌표를 가리키는 방향 벡터를 구한다
	Vec2 dirVec[3];
	for (size_t i = 0; i < 3; i++)
	{
		dirVec[i] = m_rotatePoint[i] - playerPosition;
		dirVec[i].Normalize();
	}

	// 플레이어로부터 각 point좌표들의 거리를 구한다
	float distance[3];
	for (size_t i = 0; i < 3; i++)
	{
		distance[i] = sqrt(pow(m_rotatePoint[i].x - playerPosition.x, 2) + pow(m_rotatePoint[i].y - playerPosition.y, 2));
	}

	// 각 방향벡터들을 회전 변환을 이용하여 원하는 방향으로 회전시킨다
	Vec2 rotatedDirVec[3];
	for (size_t i = 0; i < 3; i++)
	{
		rotatedDirVec[i].x = dirVec[i].x * cos(radian) - dirVec[i].y * sin(radian);
		rotatedDirVec[i].y = dirVec[i].x * sin(radian) + dirVec[i].y * cos(radian);
	}

	// 변환된 좌표에 거리를 곱해 원래 길이로 맞춰준다
	Vec2 newPos[3];
	for (size_t i = 0; i < 3; i++)
	{
		newPos[i] = rotatedDirVec[i] * distance[i];
	}

	// 변환된 좌표는 중점이 원점으로 되어있다. 원래 위치를 더해 적용한다.
	for (size_t i = 0; i < 3; i++)
	{
		m_rotatePoint[i] = newPos[i] + playerPosition;
	}

	POINT point[3];
	for (size_t i = 0; i < 3; i++)
	{
		point[i] = { (long)m_rotatePoint[i].x, (long)m_rotatePoint[i].y };
	}

	// 배경 복사
	BitBlt(CCore::GetInst()->GetMemDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, m_pBackTex->GetDC(), 0, 0, SRCCOPY);
	// 마젠타 배경 있는 회전 DC 회전시켜서 색깔 빼고 적용
	PlgBlt(m_hTempDC, point, CCore::GetInst()->GetRotateDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, NULL, NULL, NULL);
	TransparentBlt(CCore::GetInst()->GetMemDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, m_hTempDC,0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, RGB(255, 0, 255));
	BitBlt(m_hTempDC, 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, CCore::GetInst()->GetUIDC(), 0, 0, SRCCOPY);	// 회전 렌더링 시 ui 고정
	TransparentBlt(CCore::GetInst()->GetMemDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, m_hTempDC, 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, RGB(255, 0, 255));


	// 최종 출력
	BitBlt(CCore::GetInst()->GetMainDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, CCore::GetInst()->GetMemDC(), 0, 0, SRCCOPY);
}

void CScene::render()
{
	// 배경 텍스쳐가 있다면 렌더링
	if (m_pBackTex)
	{
		BitBlt(
			CCore::GetInst()->GetMemDC()
			, 0, 0
			, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
			, m_pBackTex->GetDC(), 0, 0, SRCCOPY);
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			//render_tile(CCore::GetInst()->GetObjDC());
			continue;
		}

		if ((UINT)GROUP_TYPE::UI == i)
		{
			for (size_t j = 0; j < m_arrObj[i].size(); j++)
			{
				m_arrObj[i][j]->render(CCore::GetInst()->GetUIDC());
			}

			continue;
		}

		//bool test = (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Tool Scene");
		// iterator 터짐 나중에 해,,~~
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end();)
		{

			if (!(*iter)->IsDead())
			{
				(*iter)->render(CCore::GetInst()->GetObjDC());
				iter++;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}


	}

	if (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Tool Scene")
	{
		CreateGrid(CCore::GetInst()->GetMainDC());
	}
}

//void CScene::render_tile(HDC _dc)
//{
//
//	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
//
//	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
//
//	Vec2 vResolution = CCore::GetInst()->GetResolution();
//	
//	Vec2 vRtResolution;
//
//	// 좌상단 위의 좌표값
//	Vec2 vLeftTop = vCamLook - vResolution / 2.f;
//
//	int iTileSize = TILE_SIZE;
//	// 전체화면에서 카메라의 좌상단 좌표 위치까지의 행과 열
//	int iLTCol = (int)vLeftTop.x / iTileSize;
//	int iLTRow = (int)vLeftTop.y / iTileSize;
//
//
//	//좌상단 위치에 있는 타일의 인덱스
//	int iLTIdx = m_iTileX * iLTRow + iLTCol;
//	//해상도 안에 들어오는 타일의 총개수
//	//반복문을 돌 횟수를 위함
//	int iClientWidth = (int)vResolution.x / iTileSize +2;
//	int iClientHeight = (int)vResolution.y / iTileSize + 2;
//
//	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
//	{
//		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
//		{
//			if (iCurCol < 0 || m_iTileX <= iCurCol
//				|| iCurRow < 0 || m_iTileY <= iCurRow)
//			{
//				continue;
//			}
//			int iIdx = (m_iTileX * iCurRow) + iCurCol; 
//
//			vecTile[iIdx]->render(_dc);
//		}
//	}
//}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}



bool CScene::clear()
{
	/*if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTile(L"tile\\Test.tile");
		return true;
	}
	else if (KEY_TAP(KEY::CTRL))
	{
		LoadTile(L"tile\\Test.tile");
		return false;
	}*/
	return true;
}


void CScene::CreateTileClick()
{

}

void CScene::CreateGrid(HDC _hdc)
{
	float renderLeft = 0.f, renderTop = 0.f, renderRight = 0.f, renderBottom = 0.f;
	for (int i = 0; i < m_gridX; i++)
	{
		for (int j = 0; j < m_gridY; j++)
		{
			renderLeft = (i * TILE_SIZE) / 2.f + (CCamera::GetInst()->GetRenderPos(Vec2((i * TILE_SIZE) / 2.f, 0.f))).x;
			renderTop = (j * TILE_SIZE) / 2.f + (CCamera::GetInst()->GetRenderPos(Vec2(0.f, (j * TILE_SIZE) / 2.f))).y;
			renderRight = ((i + 1) * TILE_SIZE) / 2.f + (CCamera::GetInst()->GetRenderPos(Vec2(((i + 1) * TILE_SIZE) / 2.f, 0.f))).x;
			renderBottom = ((j + 1) * TILE_SIZE) / 2.f + (CCamera::GetInst()->GetRenderPos(Vec2(0.f, ((j + 1) * TILE_SIZE) / 2.f))).y;

			SelectGDI a(_hdc, BRUSH_TYPE::HOLLOW);
			Rectangle(_hdc,
				renderLeft, renderTop, renderRight, renderBottom);
		}
	}
}


void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\obj_listup.bmp");

	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
			// 카메라 위치 고정용 test
			//if (j == 0)
			//	CCamera::GetInst()->SetTarget(pTile);
		}
	}
}


void CScene::LoadTile(const wstring& _strRelativePath)
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\obj_listup.bmp");

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;				// RAM에 저장된 데이터와 파일 저장 장치를 이어주는 Stream역할 (연결 장치)

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");		// 바이너리 모드로 읽기 
	assert(pFile);
	// 바이너리 모드로 하는 이유는 그냥 모드로 할시 
	// 모든 데이터를 문자 데이터로 저장함
	UINT xCount;
	UINT yCount;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	CTile* pTile;
	int idx;
	
	for (size_t i = 0; i < yCount; ++i)
	{
		for (size_t j = 0; j < xCount; ++j)
		{
			pTile = (CTile*)vecTile[i * xCount + j];
			pTile->Load(pFile);
			idx = pTile->GetImgIdx(); // 이미 생성되어있는 타일 벡터로부터 이미지 인덱스를 받아온다
				CObject* pLever = new CLever;

			if (idx == 0)
			{
				continue;
			}
			else if (idx == 3 || idx == 2)
			{
				// i, j로 위치 접근이 가능하고
				// 이미지 인덱스 정보도 받아왔으니까
				//해당 위치에 createTile을 해줄수 있다
				CObject* pGround = new CGround;
				pGround->SetName(L"Ground");
				pGround->SetPos(Vec2((float)j * TILE_SIZE + 32, (float)i * TILE_SIZE + 32));
				pGround->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
				((CGround*)pGround)->SetTexture(pTileTex);
				((CGround*)pGround)->SetImgIdx(idx);
				AddObject(pGround, GROUP_TYPE::GROUND);
			}
			else if (idx == 1)
			{
				CObject* pEmptyObj = new CEmptyObj;
				pEmptyObj->SetPos(Vec2((float)j * TILE_SIZE + 32, (float)i * TILE_SIZE + 32));
				pEmptyObj->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
				((CEmptyObj*)pEmptyObj)->SetTexture(pTileTex);
				((CEmptyObj*)pEmptyObj)->SetImgIdx(idx);
				AddObject(pEmptyObj, GROUP_TYPE::EmptyObj);
			}
			else if (idx == 4 || idx == 5 || idx == 6 || idx == 7)
			{
				CObject* pSpike = new CSpike;
				pSpike->SetPos(Vec2((float)j * TILE_SIZE + 32, (float)i * TILE_SIZE + 32));
				pSpike->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));

				// 4 = 하, 5 = 좌, 6 = 상, 7 = 우
				if (idx == 4 || idx == 6) // 상하
				{
					pSpike->SetName(L"TBspike");
					(pSpike->GetCollider())->SetScale(Vec2((float)pSpike->GetScale().x - 20.f, (float)pSpike->GetScale().y / 2.f));
					(pSpike->GetCollider())->SetOffsetPos(Vec2(0.f, (idx - 5) * -20.f));
				}
				else if (idx == 5 || idx == 7) // 좌우
				{
					pSpike->SetName(L"LRspike");
					(pSpike->GetCollider())->SetScale(Vec2((float)pSpike->GetScale().x / 2.f, (float)pSpike->GetScale().y - 20.f));
					(pSpike->GetCollider())->SetOffsetPos(Vec2((idx - 6) * 20.f, 0.f));
				}

				//(pSpike->GetCollider())->SetOffsetPos();
				((CSpike*)pSpike)->SetTexture(pTileTex);
				((CSpike*)pSpike)->SetImgIdx(idx);
				AddObject(pSpike, GROUP_TYPE::SPIKE);
			}
			else if (idx == 18)
			{
				CObject* pPortal = new CPortal;
				pPortal->SetPos(Vec2((float)j * TILE_SIZE + 32, (float)i * TILE_SIZE+32));
				pPortal->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
				((CPortal*)pPortal)->SetTexture(pTileTex);
				((CPortal*)pPortal)->SetImgIdx(idx);
				AddObject(pPortal, GROUP_TYPE::PORTAL);
			}
			else if (idx == 19)
			{
				CObject* pPortal = new CPortal;
				pPortal->SetPos(Vec2((float)j * TILE_SIZE + 32, (float)i * TILE_SIZE + 32));
				pPortal->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
				((CPortal*)pPortal)->SetTexture(pTileTex);
				((CPortal*)pPortal)->SetImgIdx(idx);
				AddObject(pPortal, GROUP_TYPE::PORTAL);
			}
		}
	}



	fclose(pFile);
}

void CScene::LoadTileData()
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