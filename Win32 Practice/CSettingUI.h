#pragma once
#include "CUI.h"
#include "CResMgr.h"

class CSettingUI :
	public CUI
{
public:
	CSettingUI();
	~CSettingUI();

public:
	virtual void render(HDC _dc);
	void SetTexture(CTexture* _pTex) { m_pTex_SettingUI = _pTex; }

	CLONE(CSettingUI)
private:
	CTexture* m_pTex_SettingUI = nullptr;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

};

