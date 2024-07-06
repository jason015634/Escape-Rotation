#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(0.1f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vec2(250.f,450.f))
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{


	// 추가 가속도
	m_vAccel = m_vAccel + m_vAccelA;

	// 속도
	m_vVelocity = m_vVelocity + m_vAccel * fDT;

	

	// 속도 제한 검사
	if (abs(m_vVelocity.x) > abs(m_vMaxVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vVelocity.y) > abs(m_vMaxVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y/ abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// 속도에 따른 이동
	Move();

	//힘 초기화
	m_vForce = Vec2(0.f, 0.f);

	//추가 가속도 초기화
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// 이동 방향
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos = vPos + m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);

	}

}