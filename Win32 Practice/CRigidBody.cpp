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


	// �߰� ���ӵ�
	m_vAccel = m_vAccel + m_vAccelA;

	// �ӵ�
	m_vVelocity = m_vVelocity + m_vAccel * fDT;

	

	// �ӵ� ���� �˻�
	if (abs(m_vVelocity.x) > abs(m_vMaxVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vVelocity.y) > abs(m_vMaxVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y/ abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// �ӵ��� ���� �̵�
	Move();

	//�� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	//�߰� ���ӵ� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos = vPos + m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);

	}

}