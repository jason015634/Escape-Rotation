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


	////�ػ󵵿� �°� ������ ����
	RECT rt = { 0,0,m_ptResolution.x ,m_ptResolution.y };
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);//�޴� ��, Ÿ��Ʋ�� ,��� �ȼ������ؼ� clientrect�� ���� ������ ���� �ǰ� �������ִ� �Լ�
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right, rt.bottom, 0);

	m_hDC = GetDC(m_hWnd);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	CPathMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	m_hObjBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hObjDC = CreateCompatibleDC(m_hDC);

	m_hRotateBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hRotateDC = CreateCompatibleDC(m_hDC);

	m_hUIBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hUIDC = CreateCompatibleDC(m_hDC);

	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);//������� �Ȱ��� ũ���� ��Ʈ���� ����
	m_hMemDC = CreateCompatibleDC(m_hDC);

	SelectObject(m_hObjDC, m_hObjBit);
	SelectObject(m_hRotateDC, m_hRotateBit);
	SelectObject(m_hUIDC, m_hUIBit);
	SelectObject(m_hMemDC, m_hBit);


	//���� ����ϴ� ��� �귯�� ����
	CreateBrushPen();

	//Manager �ʱ�ȭ

	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();

	//CSceneMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CSoundMgr::GetInst()->PlayBGM(BGM_SOUND::Title_BGM);
	// Sound �ε� �׽�Ʈ
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

	// ȸ�� ����
	static double drawTime = 0;	// fixedUpdate ��� �������� ����� time

	// ���� ���� �÷��̾ �ʿ��� ��츸 ȸ���� �ʿ��� ���� ����
	CScene* curScene = CSceneMgr::GetInst()->GetCurScene();
	if (curScene->GetSceneIndex() == 0 || curScene->GetSceneIndex() > 5)
	{
		
		CObject* player = curScene->GetPlayer();

		// �÷��̾ ���� ������ ��, ���߿� �� ���� ��, ���߿��� �¿� ���� ��� WALK ������ �� Q, E Ű ��Ȱ��ȭ
		if ((!(player->GetGravity()->isGround())) 
			|| (((CPlayer*)player)->GetCurState() == PLAYER_STATE::JUMP))
			//|| (player->GetGravity()->isGround() && ((CPlayer*)player)->GetCurState() == PLAYER_STATE::WALK))
		{
			CKeyMgr::GetInst()->SetKeyUnable(KEY::Q);
			CKeyMgr::GetInst()->SetKeyUnable(KEY::E);
		}

		// Q, E Ű�� ��������
		m_ckRotate = CKeyMgr::GetInst()->CheckRotate();
		if (m_ckRotate)
		{
			// ȸ�� ȿ���� 
			CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Rotate);

			assert(player != nullptr);
			m_playerPosition = player->GetPos();
			m_playerPosition = CCamera::GetInst()->GetRenderPos(m_playerPosition);

			//// ȸ�� ������ ������ �ʱ�ȭ
			curScene->SetRotatePoint(
				Vec2(m_playerPosition.x - m_ptResolution.x / 2, m_playerPosition.y - m_ptResolution.y / 2),
				Vec2(m_playerPosition.x + m_ptResolution.x / 2, m_playerPosition.y - m_ptResolution.y / 2),
				Vec2(m_playerPosition.x - m_ptResolution.x / 2, m_playerPosition.y + m_ptResolution.y / 2));

			// 1�ʰ� �Ǵµ��� ȸ�� ��������
			while (!CTimeMgr::GetInst()->CheckAcc())
			{
				CTimeMgr::GetInst()->update();
				CTimeMgr::GetInst()->render();
				drawTime += (fDT * 1000); // fDT : ns

				//	 �� ������ �������� �ʰ� fixedUpdate �ȿ��� �����ϵ� ������
				while (drawTime >= 20)
				{
					drawTime -= 20;
					curScene->RenderRotation(deg2rad(1.8 * m_ckRotate), m_playerPosition);
				}
			}
			// 1�ʰ� ������ ���� ȸ��
			if (m_ckRotate == 1)
			{
				CSceneMgr::GetInst()->GetCurScene()->RotateRight();
			}
			else
			{
				CSceneMgr::GetInst()->GetCurScene()->RotateLeft();
			}

			// 1�ʰ� ������ KeyMgr �ٽ� update
			CKeyMgr::GetInst()->update();
		}
		else
		{
			CKeyMgr::GetInst()->update();
		}
	}
	else
	{
		// �÷��̾ �ʿ� ���� ������ UI ������ ���� Ű�Ŵ��� ������Ʈ
		CKeyMgr::GetInst()->update();
	}

	//=========
	//Scene Update
	//=========
	CSceneMgr::GetInst()->update();
	CCamera::GetInst()->update();

	//�浹üũ
	CCollisionMgr::GetInst()->update();

	// ui �̺�Ʈ üũ
	CUIMgr::GetInst()->update();

	//=========
	//Rendering
	//=========	//ȭ�� Clear

	// ��� ����
	//BitBlt(m_hMemDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBackDC, 0, 0, SRCCOPY);

	// ������Ʈ transparent �غ�
	SelectGDI magenta(m_hObjDC, BRUSH_TYPE::MAGENTA);
	Rectangle(m_hObjDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectGDI white(m_hObjDC, BRUSH_TYPE::WHITE);
	// UI transparent �غ�
	SelectGDI magenta2(m_hUIDC, BRUSH_TYPE::MAGENTA);
	Rectangle(m_hUIDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectGDI white2(m_hUIDC, BRUSH_TYPE::WHITE); // todo fix : ui �������� ���������� �� ��

	// ������Ʈ ������
	CSceneMgr::GetInst()->render();

	BitBlt(m_hRotateDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hObjDC, 0, 0, SRCCOPY); // ȸ���� ����� rotationDC �غ�
	TransparentBlt(m_hMemDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hObjDC, 0, 0, m_ptResolution.x, m_ptResolution.y, RGB(255, 0, 255));
	// UI ������
	TransparentBlt(m_hMemDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hUIDC, 0, 0, m_ptResolution.x, m_ptResolution.y, RGB(255, 0, 255));

	// ���� ���
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hMemDC, 0, 0, SRCCOPY);


	CTimeMgr::GetInst()->render();

	// ==============
	// �̺�Ʈ ����ó��
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
