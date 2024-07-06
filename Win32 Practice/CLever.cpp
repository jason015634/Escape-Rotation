#include "pch.h"
#include "CLever.h"
#include "CCollider.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CSoundMgr.h"
CLever::CLever()
	: m_isManipulable(false)
	, m_pTex(nullptr)
	, m_Idx(0)
	, m_isOn(true)
{
	CreateCollider();
}

CLever::~CLever()
{
}

void CLever::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));

	pTex_Blue_lever[0] = { CResMgr::GetInst()->LoadTexture(L"BlueLever", L"texture\\blue_lever.bmp") };
	pTex_Blue_lever[1] = { CResMgr::GetInst()->LoadTexture(L"BlueLever2", L"texture\\blue_lever2.bmp") };
	pTex_Blue_lever[2] = { CResMgr::GetInst()->LoadTexture(L"BlueLever3", L"texture\\blue_lever3.bmp") };
	pTex_Blue_lever[3] = { CResMgr::GetInst()->LoadTexture(L"BlueLever4", L"texture\\blue_lever4.bmp") };

	pTex_Red_lever[0] = { CResMgr::GetInst()->LoadTexture(L"RedLever", L"texture\\red_lever.bmp") };
	pTex_Red_lever[1] = { CResMgr::GetInst()->LoadTexture(L"RedLever2", L"texture\\red_lever2.bmp") };
	pTex_Red_lever[2] = { CResMgr::GetInst()->LoadTexture(L"RedLever3", L"texture\\red_lever3.bmp") };
	pTex_Red_lever[3] = { CResMgr::GetInst()->LoadTexture(L"RedLever4", L"texture\\red_lever4.bmp") };
}

void CLever::update()
{
	if (m_isManipulable == true && (KEY_TAP(KEY::UP)|| KEY_TAP(KEY::W)))
	{
		if (m_isOn)
		{
			CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Lever_On);
		}
		else
		{
			CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Lever_Off);
		}
		m_isOn = !m_isOn;
	}
}

void CLever::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	int rotatestate = CSceneMgr::GetInst()->GetCurScene()->GetRotateState();
	if (m_isOn)
	{
		BitBlt(_dc
			, vRenderPos.x - vScale.x / 2.f
			, vRenderPos.y - vScale.y / 2.f
			, vScale.x
			, vScale.y
			, pTex_Blue_lever[(m_Idx + rotatestate) % 4]->GetDC()
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
			, pTex_Red_lever[(m_Idx + rotatestate) % 4]->GetDC()
			, 0
			, 0
			, SRCCOPY);
	}
}

void CLever::OnCollisionEnter(CCollider* _pOther)
{
	ChangeState(true);
}

void CLever::OnCollisionExit(CCollider* _pOther)
{
	ChangeState(false);
}


