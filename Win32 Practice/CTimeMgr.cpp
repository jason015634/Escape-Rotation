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
	//���� ī��Ʈ
	QueryPerformanceCounter(&m_llCurCount);

	//�ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//����ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;

	// �ش� �ڵ� ���� �������� �����ϸ� �ٴ� �ݶ��̴� ������x ��ǥ�� ��������
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);

	
	// �÷��̾� ��ġ, ī�޶� ��ġ test
	CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER)[0];
	m_playerPos = player->GetPos();	//Vec2(0, 0); 	// �� �� ���� ������
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

	static double dAcc = 0.f;	// 1�� üũ�� ���� �����ð�
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
