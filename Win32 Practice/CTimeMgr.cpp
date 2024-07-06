#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include "Win32 Practice.h"

// test
#include "CPlayer.h"	
#include "CSceneMgr.h"
#include "CScene.h"
#include "CCamera.h"
#include "CKeyMgr.h"
CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	,m_llFrequency{}
	,m_iCallCount()
	,m_dDT(0.)
	,m_llPrevCount{}
	,m_dAcc()
	,m_iFPS()
{
}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//현재 카운트
	QueryPerformanceCounter(&m_llCurCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//이전카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;

	// 해당 코드 없이 릴리즈모드 실행하면 바닥 콜라이더 렌더링x 좌표값 문제있음
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);

	
	// 플레이어 위치, 카메라 위치 test
	CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER)[0];
	m_playerPos = player->GetPos();	//Vec2(0, 0); 	// 씬 툴 오류 방지용
	CCamera* camera = CCamera::GetInst();
	m_cameraPos = camera->GetRenderPos(m_playerPos);
	//m_mousePos = MOUSE_POS;
	//m_realPos = CCamera::GetInst()->GetRealPos(m_mousePos);

#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}


bool CTimeMgr::CheckAcc()
{

	static double dAcc = 0.f;	// 1초 체크를 위한 누적시간
	dAcc += CTimeMgr::GetInst()->GetDT();

	if(dAcc >= 1.f)
	{
		dAcc = 0.f;
		return true;
	}

	return false;
}

void CTimeMgr::render()
{
	int rotatestate = CSceneMgr::GetInst()->GetCurScene()->GetRotateState() % 4;
	if (m_dAcc >= 1.f)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		//swprintf_s(szBuffer, L"FPS : %d, DT : %f, playerPos : (%f, %f), cameraPos : (%f, %f)",
		//	m_iFPS, m_dDT, m_playerPos.x, m_playerPos.y, m_cameraPos.x, m_cameraPos.y);
		swprintf_s(szBuffer, L"FPS : %d, DT : %f, mousePos : (%f, %f), realPos : (%f, %f), rotatestate : (%d)",
			m_iFPS, m_dDT, m_mousePos.x, m_mousePos.y, m_realPos.x, m_realPos.y, rotatestate);		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
