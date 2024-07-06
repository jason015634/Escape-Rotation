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
			//m_arrObj[i] �׷� ������ j ��ü ����
			delete m_arrObj[i][j];
		}
	}//���� �ȿ� �ִ� ������ �ּ� Ÿ���̶� ���� ������ ����� ��

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
			// nullptr ���� ����� ����ó�� �߰� : if(m_arrObj[i][j])
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
					// �¿�
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
					// �¿�
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
	// �÷��̾� ��ġ�� �߽����� ȸ��

	// PlgBlt : �»��, ����, ���ϴ��� ��ǥ�� ������ �ִ� POINT ����ü �迭�� �ʿ�� �Ѵ� - m_rotatePoint

	// �ؽ����� �߽ɿ������� ������ point ��ǥ�� ����Ű�� ���� ���͸� ���Ѵ�
	Vec2 dirVec[3];
	for (size_t i = 0; i < 3; i++)
	{
		dirVec[i] = m_rotatePoint[i] - playerPosition;
		dirVec[i].Normalize();
	}

	// �÷��̾�κ��� �� point��ǥ���� �Ÿ��� ���Ѵ�
	float distance[3];
	for (size_t i = 0; i < 3; i++)
	{
		distance[i] = sqrt(pow(m_rotatePoint[i].x - playerPosition.x, 2) + pow(m_rotatePoint[i].y - playerPosition.y, 2));
	}

	// �� ���⺤�͵��� ȸ�� ��ȯ�� �̿��Ͽ� ���ϴ� �������� ȸ����Ų��
	Vec2 rotatedDirVec[3];
	for (size_t i = 0; i < 3; i++)
	{
		rotatedDirVec[i].x = dirVec[i].x * cos(radian) - dirVec[i].y * sin(radian);
		rotatedDirVec[i].y = dirVec[i].x * sin(radian) + dirVec[i].y * cos(radian);
	}

	// ��ȯ�� ��ǥ�� �Ÿ��� ���� ���� ���̷� �����ش�
	Vec2 newPos[3];
	for (size_t i = 0; i < 3; i++)
	{
		newPos[i] = rotatedDirVec[i] * distance[i];
	}

	// ��ȯ�� ��ǥ�� ������ �������� �Ǿ��ִ�. ���� ��ġ�� ���� �����Ѵ�.
	for (size_t i = 0; i < 3; i++)
	{
		m_rotatePoint[i] = newPos[i] + playerPosition;
	}

	POINT point[3];
	for (size_t i = 0; i < 3; i++)
	{
		point[i] = { (long)m_rotatePoint[i].x, (long)m_rotatePoint[i].y };
	}

	// ��� ����
	BitBlt(CCore::GetInst()->GetMemDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, m_pBackTex->GetDC(), 0, 0, SRCCOPY);
	// ����Ÿ ��� �ִ� ȸ�� DC ȸ�����Ѽ� ���� ���� ����
	PlgBlt(m_hTempDC, point, CCore::GetInst()->GetRotateDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, NULL, NULL, NULL);
	TransparentBlt(CCore::GetInst()->GetMemDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, m_hTempDC,0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, RGB(255, 0, 255));
	BitBlt(m_hTempDC, 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, CCore::GetInst()->GetUIDC(), 0, 0, SRCCOPY);	// ȸ�� ������ �� ui ����
	TransparentBlt(CCore::GetInst()->GetMemDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, m_hTempDC, 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y, RGB(255, 0, 255));


	// ���� ���
	BitBlt(CCore::GetInst()->GetMainDC(), 0, 0, CCore::GetInst()->GetResolution().x, CCore::GetInst()->GetResolution().y
		, CCore::GetInst()->GetMemDC(), 0, 0, SRCCOPY);
}

void CScene::render()
{
	// ��� �ؽ��İ� �ִٸ� ������
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
		// iterator ���� ���߿� ��,,~~
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
//	// �»�� ���� ��ǥ��
//	Vec2 vLeftTop = vCamLook - vResolution / 2.f;
//
//	int iTileSize = TILE_SIZE;
//	// ��üȭ�鿡�� ī�޶��� �»�� ��ǥ ��ġ������ ��� ��
//	int iLTCol = (int)vLeftTop.x / iTileSize;
//	int iLTRow = (int)vLeftTop.y / iTileSize;
//
//
//	//�»�� ��ġ�� �ִ� Ÿ���� �ε���
//	int iLTIdx = m_iTileX * iLTRow + iLTCol;
//	//�ػ� �ȿ� ������ Ÿ���� �Ѱ���
//	//�ݺ����� �� Ƚ���� ����
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
			// ī�޶� ��ġ ������ test
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

	FILE* pFile = nullptr;				// RAM�� ����� �����Ϳ� ���� ���� ��ġ�� �̾��ִ� Stream���� (���� ��ġ)

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");		// ���̳ʸ� ���� �б� 
	assert(pFile);
	// ���̳ʸ� ���� �ϴ� ������ �׳� ���� �ҽ� 
	// ��� �����͸� ���� �����ͷ� ������
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
			idx = pTile->GetImgIdx(); // �̹� �����Ǿ��ִ� Ÿ�� ���ͷκ��� �̹��� �ε����� �޾ƿ´�
				CObject* pLever = new CLever;

			if (idx == 0)
			{
				continue;
			}
			else if (idx == 3 || idx == 2)
			{
				// i, j�� ��ġ ������ �����ϰ�
				// �̹��� �ε��� ������ �޾ƿ����ϱ�
				//�ش� ��ġ�� createTile�� ���ټ� �ִ�
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

				// 4 = ��, 5 = ��, 6 = ��, 7 = ��
				if (idx == 4 || idx == 6) // ����
				{
					pSpike->SetName(L"TBspike");
					(pSpike->GetCollider())->SetScale(Vec2((float)pSpike->GetScale().x - 20.f, (float)pSpike->GetScale().y / 2.f));
					(pSpike->GetCollider())->SetOffsetPos(Vec2(0.f, (idx - 5) * -20.f));
				}
				else if (idx == 5 || idx == 7) // �¿�
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