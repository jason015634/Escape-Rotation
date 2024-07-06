#pragma once
#include "CUI.h"
#include "CResMgr.h"

class CRotateUI_Q :
	public CUI
{
public:
	CRotateUI_Q();
	~CRotateUI_Q();

public:
	virtual void render(HDC _dc);
	void SetTexture(CTexture* _pTex) { m_pTex_RotateUI_Q = _pTex; }

	CLONE(CRotateUI_Q)
private:
	CTexture* m_pTex_RotateUI_Q = nullptr;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

};

