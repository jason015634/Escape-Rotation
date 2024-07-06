#include "pch.h"
#include "CGround.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CTexture.h"

CGround::CGround()
	:m_pTex(nullptr)
	, m_imgIdx(3)
{
	CreateCollider();
}

CGround::~CGround()
{
}

void CGround::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CGround::update()
{
}

void CGround::render(HDC _dc)
{
	if (nullptr == m_pTex || -1 == m_imgIdx)
		return;

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = (UINT)m_imgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_imgIdx / iMaxRow;

	if (iMaxRow < iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();


	BitBlt(_dc
		, vRenderPos.x - vScale.x /2.f
		, vRenderPos.y - vScale.y / 2.f
		, vScale.x
		, vScale.y
		, m_pTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}


void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLenY = abs(vObjPos.y - vPos.y);
		float fValueY = (vObjScale.y + vScale.y) / 2.f - fLenY;

		float fLenX = abs(vObjPos.x - vPos.x);
		float fValueX = (vObjScale.x + vScale.x) / 2.f - fLenX;

		vObjPos = pOtherObj->GetPos();
		
		if (fValueX < 20.f)
		{
			
			if (fValueY > 20.f) // if (fValueY > 1)
			{
				if (vPos.x < vObjPos.x)
				{
					vObjPos.x += abs(fValueX);
				}
				else
				{
					vObjPos.x -= abs(fValueX);
				}
			}
		}
		else
		{
			pOtherObj->GetGravity()->SetGround(true);
			if (vPos.y< vObjPos.y)
			{
				vObjPos.y += (fValueY);
				Vec2 vV = _pOther->GetObj()->GetRigidBody()->GetVelocity();
				_pOther->GetObj()->GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));
			}
			
			else
			{
				vObjPos.y -= (fValueY);
			}
			
		}
		
		
		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLenY = abs(vObjPos.y - vPos.y);
		float fValueY = (vObjScale.y + vScale.y) / 2.f - fLenY;

		float fLenX = abs(vObjPos.x - vPos.x);
		float fValueX = (vObjScale.x + vScale.x) / 2.f - fLenX;

		// 충돌을 접한 상태로 유지하기 위해서 일부러 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		
		if (fValueX < 20.f)
		{
			
			if (fValueY > 20.f) // if (fValueY > 1)
			{
				if (vPos.x < vObjPos.x)
				{
					vObjPos.x += abs(fValueX); 
				}
				else
				{
					vObjPos.x -= abs(fValueX);
				}
			}
		}
		else
		{
			pOtherObj->GetGravity()->SetGround(true);
			if (vPos.y < vObjPos.y)
			{
				vObjPos.y += (fValueY);
				Vec2 vV = _pOther->GetObj()->GetRigidBody()->GetVelocity();
				_pOther->GetObj()->GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));
			}
				
			
			else
			{
				vObjPos.y -= (fValueY);
			}
		}
		
		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}
}
