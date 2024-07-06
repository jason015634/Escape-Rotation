#pragma once
#include "CUI.h"
#include "CResMgr.h"

class CRotateUI_E :
	public CUI
{
public:
	CRotateUI_E();
	~CRotateUI_E();

public:
	virtual void render(HDC _dc);
	void SetTexture(CTexture* _pTex) { m_pTex_RotateUI_E = _pTex; }

	CLONE(CRotateUI_E)
private:
	CTexture* m_pTex_RotateUI_E = nullptr;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

};

