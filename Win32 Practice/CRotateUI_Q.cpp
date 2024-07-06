#include "pch.h"
#include "CRotateUI_Q.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CRotateUI_Q::CRotateUI_Q()
{
	m_pTex_RotateUI_Q = CResMgr::GetInst()->LoadTexture(L"pRotateUI_Q", L"texture\\but_Q.bmp");
}


CRotateUI_Q::~CRotateUI_Q()
{
}

void CRotateUI_Q::render(HDC _dc)
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
		, m_pTex_RotateUI_Q->GetDC(), 0, 0
		, (int)this->GetScale().x
		, (int)this->GetScale().y, RGB(255, 0, 255));
}

void CRotateUI_Q::MouseOn()
{

}

void CRotateUI_Q::MouseLbtnDown()
{

}

void CRotateUI_Q::MouseLbtnUp()
{

}

void CRotateUI_Q::MouseLbtnClicked()
{

}

