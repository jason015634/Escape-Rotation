#include "pch.h"
#include "CPanelUI.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	:CUI(false)
	, m_pTex(nullptr)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::update()
{
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

// 	TransparentBlt(_dc
// 		, (int)vPos.x
// 		, (int)vPos.y
// 		, (int)this->GetScale().x
// 		, (int)this->GetScale().y
// 		, m_pTex->GetDC(), 0, 0	
// 		, (int)this->GetScale().x
// 		, (int)this->GetScale().y, RGB(255, 0, 255));

	if (m_pTex)
	{
		BitBlt(_dc
			, (int)vPos.x
			, (int)vPos.y
			, (int)vScale.x
			, (int)vScale.y
			, m_pTex->GetDC()
			, 0
			, 0, SRCCOPY);

	}
}

void CPanelUI::MouseOn()
{
	// 드래그 기능 필요시 주석 해제
	//if (IsLbtnDown())
	//{
	//	Vec2 vDiff = MOUSE_POS - m_vDragStart;

	//	Vec2 vCurPos = GetPos();
	//	vCurPos = vCurPos + vDiff;
	//	SetPos(vCurPos);

	//	m_vDragStart = MOUSE_POS;
	//}
}

void CPanelUI::MouseLbtnDown()
{
// 	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}

void CPanelUI::MouseLbtnClicked()
{

}

