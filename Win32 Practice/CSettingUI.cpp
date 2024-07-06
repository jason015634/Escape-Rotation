#include "pch.h"
#include "CSettingUI.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CSettingUI::CSettingUI()
{
	m_pTex_SettingUI = CResMgr::GetInst()->LoadTexture(L"SettingUI", L"texture\\setting.bmp");
}


CSettingUI::~CSettingUI()
{
}

void CSettingUI::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// 	if (m_bCamAffected)
	// 	{
	// 		// ī�޶� ������ �޴´ٸ� ī�޶� ������ ������ �޾ƿͼ� �����������
	// 		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	// 	}


	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)this->GetScale().x
		, (int)this->GetScale().y
		, m_pTex_SettingUI->GetDC(), 0, 0
		, (int)this->GetScale().x
		, (int)this->GetScale().y, RGB(255, 0, 255));
}

void CSettingUI::MouseOn()
{

}

void CSettingUI::MouseLbtnDown()
{

}

void CSettingUI::MouseLbtnUp()
{

}

void CSettingUI::MouseLbtnClicked()
{

}

