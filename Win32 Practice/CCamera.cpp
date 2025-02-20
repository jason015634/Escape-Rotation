#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	:m_pTargetObj(nullptr)
{

}

CCamera::~CCamera()
{

}

//Vec2 CCamera::GetRenderPos(Vec2 _vObjPos)
//{
//	
//}

void CCamera::init()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	CalDiff();
}

void CCamera::CalDiff()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vLookAt - vCenter;
}
