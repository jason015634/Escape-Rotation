#pragma once
#include "CUI.h"
#include "CResMgr.h"

class CHackerUI :
	public CUI
{
public:
    CHackerUI();
    ~CHackerUI();

public:
    virtual void render(HDC _dc);
	void SetTexture(CTexture* _pTex) { m_pTex_HackerUI = _pTex; }

    CLONE(CHackerUI)
private:
    CTexture* m_pTex_HackerUI = nullptr;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

};

