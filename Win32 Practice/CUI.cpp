#include "pch.h"
#include "CUI.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	:m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)

{

}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); i++)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
	
}

CUI::CUI()
{

}

CUI::~CUI()
{
	// 자식 벡터 비우기
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::DeleteUI()
{
	
}

void CUI::update()
{
	

	//	자식 UI update
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();

	// UI의 최종 좌표를 구한다
	m_vFinalPos = GetPos();

	if (GetParent())
	{
		m_vFinalPos = m_vFinalPos + m_pParentUI->GetFinalPos();
	}

	MouseOnCheck();

	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		// 카메라 영향을 받는다면 카메라 렌더링 영역을 받아와서 렌더해줘야함
		vPos = CCamera::GetInst()->GetRenderPos(vPos);	
	}

	if(m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		SelectGDI select2(_dc, BRUSH_TYPE::HOLLOW);

		Rectangle(_dc,
			(int)vPos.x,
			(int)vPos.y,
			(int)vPos.x + (int)vScale.x,
			(int)vPos.y + (int)vScale.y);
	}
	else
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		SelectGDI select2(_dc, BRUSH_TYPE::HOLLOW);

		Rectangle(_dc,
			(int)vPos.x,
			(int)vPos.y,
			(int)vPos.x + (int)vScale.x,
			(int)vPos.y + (int)vScale.y);
	}

	// 자식 UI 렌더링
	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}
