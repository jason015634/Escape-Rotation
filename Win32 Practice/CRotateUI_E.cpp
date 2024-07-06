#include "pch.h"
#include "CRotateUI_E.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CRotateUI_E::CRotateUI_E()
{
	m_pTex_RotateUI_E = CResMgr::GetInst()->LoadTexture(L"pRotateUI_E", L"texture\\but_E.bmp");
}


CRotateUI_E::~CRotateUI_E()
{
}

void CRotateUI_E::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// 	if (m_bCamAffected)
	// 	{
	// 		// 카메라 영향을 받는다면 카메라 렌더링 영역을 받아와서 렌더해줘야함
	// 		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	// 	}


	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)this->GetScale().x
		, (int)this->GetScale().y
		, m_pTex_RotateUI_E->GetDC(), 0, 0
		, (int)this->GetScale().x
		, (int)this->GetScale().y, RGB(255, 0, 255));
}

void CRotateUI_E::MouseOn()
{

}

void CRotateUI_E::MouseLbtnDown()
{

}

void CRotateUI_E::MouseLbtnUp()
{

}

void CRotateUI_E::MouseLbtnClicked()
{

}

