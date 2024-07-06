#include "pch.h"
#include "CLazer.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CLever.h"
#include "CObject.h"
#include "CCollider.h"

CLazer::CLazer()
	: m_pOwnerLever(nullptr)
	, m_pTex(nullptr)
	, m_Idx(0)
{

}

CLazer::~CLazer()
{

}

void CLazer::update()
{
	if (m_pOwnerLever->GetOnOff())
	{
		if (GetOwnerGround() == nullptr)
		{
			CObject* pGround4 = new CGround;
			pGround4->GetCollider()->SetScale(Vec2((1 - 0.8f * m_Idx) * GetScale().x, (0.2f + 0.8f * m_Idx) * GetScale().y));
			pGround4->SetName(L"Ground");
			pGround4->SetPos(this->GetPos());
			pGround4->SetScale(Vec2((1 - 0.8f * m_Idx) * GetScale().x, (0.2f + 0.8f * m_Idx) * GetScale().y));
			CSceneMgr::GetInst()->GetCurScene()->AddObject(pGround4, GROUP_TYPE::GROUND);
			SetOwnerGround(pGround4);
		}
	}
	else
	{
		if (GetOwnerGround() != nullptr)
		{
			DeleteObject(GetOwnerGround());
			SetOwnerGround(nullptr);
		}
	}
}

void CLazer::start()
{
	CObject* pGround4 = new CGround;
	pGround4->SetName(L"Ground");
	pGround4->SetPos(this->GetPos());
	pGround4->SetScale(Vec2((1 - 0.8f * m_Idx) * GetScale().x, (0.2f + 0.8f * m_Idx) * GetScale().y));
	CSceneMgr::GetInst()->GetCurScene()->AddObject(pGround4, GROUP_TYPE::GROUND);
	SetOwnerGround(pGround4);

}

void CLazer::render(HDC _dc)
{
	CTexture* pTex_Lazer[2] = { CResMgr::GetInst()->LoadTexture(L"Lazer1",L"texture\\light3.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Lazer2",L"texture\\light4.bmp") };

	CTexture* pEmpty_Lazer[1] = { CResMgr::GetInst()->LoadTexture(L"EmptyTile",L"texture\\empty_tile.bmp") };

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	int rotatestate = CSceneMgr::GetInst()->GetCurScene()->GetRotateState() % 2;

	if (m_pOwnerLever->GetOnOff())
	{
	BitBlt(_dc
		, vRenderPos.x - vScale.x / 2.f
		, vRenderPos.y - vScale.y / 2.f
		, vScale.x
		, vScale.y
		, pTex_Lazer[(m_Idx + rotatestate) % 2]->GetDC()
		, 0
		, 0
		, SRCCOPY);
	}
	else
	{
		BitBlt(_dc
			, vRenderPos.x - vScale.x / 2.f
			, vRenderPos.y - vScale.y / 2.f
			, vScale.x
			, vScale.y
			, pEmpty_Lazer[0]->GetDC()
			, 0
			, 0
			, SRCCOPY);
	}

}

