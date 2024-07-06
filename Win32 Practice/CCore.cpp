#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "Win32 Practice.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
// #include "CSound.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CGravity.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"

CCore::CCore()
	: m_hWnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_hObjBit(0),
	m_hObjDC(0),
	m_hRotateBit(0),
	m_hRotateDC(0),
	m_hUIBit(0),
	m_hUIDC(0),
	m_hBit(0),
	m_hMemDC(0),
	m_arrBrush{},
	m_arrPen{}
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_hObjDC);
	DeleteObject(m_hObjBit);

	DeleteDC(m_hRotateDC);
	DeleteObject(m_hRotateBit);

	DeleteDC(m_hUIDC);
	DeleteObject(m_hBit);

	DeleteDC(m_hMemDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	////해상도에 맞게 윈도우 조정
	RECT rt = { 0,0,m_ptResolution.x ,m_ptResolution.y };
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);//메뉴 바, 타이틀바 ,경계 픽셀생각해서 clientrect가 내가 지정한 값이 되게 조정해주는 함수
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right, rt.bottom, 0);

	m_hDC = GetDC(m_hWnd);

	//이중 버퍼링 용도의 비트맵과 DC를 만든다.
	CPathMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	m_hObjBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hObjDC = CreateCompatibleDC(m_hDC);

	m_hRotateBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hRotateDC = CreateCompatibleDC(m_hDC);

	m_hUIBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hUIDC = CreateCompatibleDC(m_hDC);

	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);//윈도우와 똑같은 크기의 비트맵을 생성
	m_hMemDC = CreateCompatibleDC(m_hDC);

	SelectObject(m_hObjDC, m_hObjBit);
	SelectObject(m_hRotateDC, m_hRotateBit);
	SelectObject(m_hUIDC, m_hUIBit);
	SelectObject(m_hMemDC, m_hBit);


	//자주 사용하는 펜과 브러쉬 생성
	CreateBrushPen();

	//Manager 초기화

	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();

	//CSceneMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Title_BGM);
	// Sound 로드 테스트
// 	CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\sample15s.wav");
// 	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");
// 
// 	pNewSound->PlayToBGM(true);
// 
// 	pNewSound->SetPosition(50.f);
// 	pNewSound->SetVolume(20.f);


	return S_OK;
}

double deg2rad(double degree)
{
	return degree * PI / 180;
}


void CCore::progress()
{
	//=========
	//Manager Update
	//=========
	CTimeMgr::GetInst()->update();

	// 회전 로직
	static double drawTime = 0;	// fixedUpdate 대신 렌더링에 사용할 time

	// 현재 씬에 플레이어가 필요한 경우만 회전에 필요한 로직 진입
	CScene* curScene = CSceneMgr::GetInst()->GetCurScene();
	if (curScene->GetSceneIndex() == 0 || curScene->GetSceneIndex() > 5)
	{
		
		CObject* player = curScene->GetPlayer();

		// 플레이어가 점프 상태일 때, 공중에 떠 있을 때, 공중에서 좌우 벽에 닿아 WALK 상태일 때 Q, E 키 비활성화
		if ((!(player->GetGravity()->isGround())) 
			|| (((CPlayer*)player)->GetCurState() == PLAYER_STATE::JUMP))
			//|| (player->GetGravity()->isGround() && ((CPlayer*)player)->GetCurState() == PLAYER_STATE::WALK))
		{
			CKeyMgr::GetInst()->SetKeyUnable(KEY::Q);
			CKeyMgr::GetInst()->SetKeyUnable(KEY::E);
		}

		// Q, E 키가 눌렸으면
		m_ckRotate = CKeyMgr::GetInst()->CheckRotate();
		if (m_ckRotate)
		{
			// 회전 효과음 
			CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Rotate);

			assert(player != nullptr);
			m_playerPosition = player->GetPos();
			m_playerPosition = CCamera::GetInst()->GetRenderPos(m_playerPosition);

			//// 회전 렌더링 기준점 초기화
			curScene->SetRotatePoint(
				Vec2(m_playerPosition.x - m_ptResolution.x / 2, m_playerPosition.y - m_ptResolution.y / 2),
				Vec2(m_playerPosition.x + m_ptResolution.x / 2, m_playerPosition.y - m_ptResolution.y / 2),
				Vec2(m_playerPosition.x - m_ptResolution.x / 2, m_playerPosition.y + m_ptResolution.y / 2));

			// 1초가 되는동안 회전 렌더링만
			while (!CTimeMgr::GetInst()->CheckAcc())
			{
				CTimeMgr::GetInst()->update();
				CTimeMgr::GetInst()->render();
				drawTime += (fDT * 1000); // fDT : ns

				//	 매 프레임 실행하지 않고 fixedUpdate 안에서 실행하듯 렌더링
				while (drawTime >= 20)
				{
					drawTime -= 20;
					curScene->RenderRotation(deg2rad(1.8 * m_ckRotate), m_playerPosition);
				}
			}
			// 1초가 끝나면 실제 회전
			if (m_ckRotate == 1)
			{
				CSceneMgr::GetInst()->GetCurScene()->RotateRight();
			}
			else
			{
				CSceneMgr::GetInst()->GetCurScene()->RotateLeft();
			}

			// 1초가 끝나고 KeyMgr 다시 update
			CKeyMgr::GetInst()->update();
		}
		else
		{
			CKeyMgr::GetInst()->update();
		}
	}
	else
	{
		// 플레이어가 필요 없는 씬에서 UI 동작을 위한 키매니저 업데이트
		CKeyMgr::GetInst()->update();
	}

	//=========
	//Scene Update
	//=========
	CSceneMgr::GetInst()->update();
	CCamera::GetInst()->update();

	//충돌체크
	CCollisionMgr::GetInst()->update();

	// ui 이벤트 체크
	CUIMgr::GetInst()->update();

	//=========
	//Rendering
	//=========	//화면 Clear

	// 배경 복사
	//BitBlt(m_hMemDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBackDC, 0, 0, SRCCOPY);

	// 오브젝트 transparent 준비
	SelectGDI magenta(m_hObjDC, BRUSH_TYPE::MAGENTA);
	Rectangle(m_hObjDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectGDI white(m_hObjDC, BRUSH_TYPE::WHITE);
	// UI transparent 준비
	SelectGDI magenta2(m_hUIDC, BRUSH_TYPE::MAGENTA);
	Rectangle(m_hUIDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectGDI white2(m_hUIDC, BRUSH_TYPE::WHITE); // todo fix : ui 렌더링이 검은색으로 됨 흠

	// 오브젝트 렌더링
	CSceneMgr::GetInst()->render();

	BitBlt(m_hRotateDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hObjDC, 0, 0, SRCCOPY); // 회전에 사용할 rotationDC 준비
	TransparentBlt(m_hMemDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hObjDC, 0, 0, m_ptResolution.x, m_ptResolution.y, RGB(255, 0, 255));
	// UI 렌더링
	TransparentBlt(m_hMemDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hUIDC, 0, 0, m_ptResolution.x, m_ptResolution.y, RGB(255, 0, 255));

	// 최종 출력
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hMemDC, 0, 0, SRCCOPY);


	CTimeMgr::GetInst()->render();

	// ==============
	// 이벤트 지연처리
	// ==============
	CEventMgr::GetInst()->update();
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)CreateSolidBrush(WHITE_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::MAGENTA] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
