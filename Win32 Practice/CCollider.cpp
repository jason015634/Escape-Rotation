#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"
#include "SelectGDI.h"
#include "CGravity.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// Object의 위치를 따라간다.
	Vec2 vObjectPos = m_pOwner->GetPos();

	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	if (m_pOwner->GetGravity() != nullptr && m_pOwner->GetGravity()->isGround())
	{
		SelectGDI p(_dc, PEN_TYPE::RED);
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

		Vec2 vPos = m_pOwner->GetPos();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
		Rectangle(_dc
			, (int)(vPos.x - m_vScale.x / 2.f)
			, (int)(vPos.y - m_vScale.y / 2.f)
			, (int)(vPos.x + m_vScale.x / 2.f)
			, (int)(vPos.y + m_vScale.y / 2.f));
	}
	else
	{
		SelectGDI p(_dc, PEN_TYPE::GREEN);
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

		Vec2 vPos = m_pOwner->GetPos();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
		//vPos = GetFinalPos();
		Rectangle(_dc
			, (int)(vPos.x + m_vOffsetPos.x - m_vScale.x / 2.f)
			, (int)(vPos.y + m_vOffsetPos.y - m_vScale.y / 2.f)
			, (int)(vPos.x + m_vOffsetPos.x + m_vScale.x / 2.f)
			, (int)(vPos.y + m_vOffsetPos.y + m_vScale.y / 2.f)); 
	}


}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
}


