#include "pch.h"
#include "CHackerUI.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CHackerUI::CHackerUI()
{
	m_pTex_HackerUI = CResMgr::GetInst()->LoadTexture(L"pHackerUI", L"texture\\Hacker_1.bmp");
}


CHackerUI::~CHackerUI()
{
}

void CHackerUI::render(HDC _dc)
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
		, m_pTex_HackerUI->GetDC(), 0, 0
		, (int)this->GetScale().x
		, (int)this->GetScale().y, RGB(255, 0, 255));
}

void CHackerUI::MouseOn()
{

}

void CHackerUI::MouseLbtnDown()
{

}

void CHackerUI::MouseLbtnUp()
{

}

void CHackerUI::MouseLbtnClicked()
{

}

