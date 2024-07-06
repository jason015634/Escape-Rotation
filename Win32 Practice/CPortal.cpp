#include "pch.h"
#include "CPortal.h"
#include "CCollider.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CSoundMgr.h"

CPortal::CPortal()
	: m_isManipulable(false)
	, m_pTex(nullptr)
	, m_imgIdx(17)
{
	CreateCollider();
}

CPortal::~CPortal()
{
}

void CPortal::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CPortal::update()
{
	if (m_isManipulable == true && (KEY_TAP(KEY::UP)|| KEY_TAP(KEY::W)) && CSceneMgr::GetInst()->GetCurScene()->GetRotateState() % 4 == 0)
	{
		// Æ÷Å»°ú »óÈ£ÀÛ¿ë½Ã ÄÆ¾ÀÀ¸·Î
		CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Portal);

		ChangeScene(SCENE_TYPE::LEVEL_CUTSCENE, (SCENE_TYPE)(CSceneMgr::GetInst()->GetCurScene()->GetSceneIndex() + 1));
	}
}

void CPortal::render(HDC _dc)
{
	if (nullptr == m_pTex || -1 == m_imgIdx)
		return;
	CTexture* pTex_Portal[4] = { CResMgr::GetInst()->LoadTexture(L"Portal",  L"texture\\portal_up.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Portal2", L"texture\\portal_up_2.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Portal3", L"texture\\portal_up_3.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Portal4", L"texture\\portal_up_4.bmp") };

	CTexture* pTex_Portal2[4] = { CResMgr::GetInst()->LoadTexture(L"Portal5",  L"texture\\portal_down.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Portal6", L"texture\\portal_down2.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Portal7", L"texture\\portal_down3.bmp")
								, CResMgr::GetInst()->LoadTexture(L"Portal8", L"texture\\portal_down4.bmp") };

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	int rotatestate = CSceneMgr::GetInst()->GetCurScene()->GetRotateState();

	if (m_imgIdx == 18)
	{
		BitBlt(_dc
			, vRenderPos.x - vScale.x / 2.f
			, vRenderPos.y - vScale.y / 2.f
			, vScale.x
			, vScale.y
			, pTex_Portal[rotatestate]->GetDC()
			, 0
			, 0
			, SRCCOPY);
	}
	else if (m_imgIdx == 19)
	{
		BitBlt(_dc
			, vRenderPos.x - vScale.x / 2.f
			, vRenderPos.y - vScale.y / 2.f
			, vScale.x
			, vScale.y
			, pTex_Portal2[rotatestate]->GetDC()
			, 0
			, 0
			, SRCCOPY);
	}


	//component_render(_dc);
}

void CPortal::OnCollisionEnter(CCollider* _pOther)
{
	ChangeState(true);
}

void CPortal::OnCollisionExit(CCollider* _pOther)
{
	ChangeState(false);
}
