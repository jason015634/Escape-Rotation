#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CRigidBody.h"
#include "CGravity.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_bAlive(true)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;

	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}

	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
// 	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Runer_2-side.bmp");

	/*CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 0.f), Vec2(500.f, 500.f), Vec2(500.f, 0.f), 0.1f, 8);
	GetAnimator()->Play(L"WALK_RIGHT", true);*/
}


CObject::~CObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}

	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}

	if (nullptr != m_pRigidBody)
	{
		delete m_pRigidBody;
	}

	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
	}
}


void CObject::finalupdate()
{
	/*if (m_pAnimator)
	{
		m_pAnimator->finalupdate();
	}*/

	if (m_pGravity)
	{
		m_pGravity->finalupdate();
	}

	if (m_pRigidBody)
	{
		m_pRigidBody->finalupdate();
	}

	if (m_pCollider)
	{
		m_pCollider->finalupdate();
	}

}



void CObject::render(HDC _dc)
{
	// 오브젝트의 고유 좌표값이 아닌 카메라로 부터의 위치값 사용
	// 고유 좌표값에서 카메라
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	// RenderPos 기반으로 그려줌
	//Rectangle(_dc,
	//	(int)(vRenderPos.x - m_vScale.x / 2.f),
	//	(int)(vRenderPos.y - m_vScale.y / 2.f),
	//	(int)(vRenderPos.x + m_vScale.x / 2.f),
	//	(int)(vRenderPos.y + m_vScale.y / 2.f));

	//component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}

	// Debugging
	/*if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
	}*/

}


void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

