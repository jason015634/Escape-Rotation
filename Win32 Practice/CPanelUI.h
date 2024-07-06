#pragma once
#include "CUI.h"

class CTexture;

class CPanelUI :
    public CUI
{
private:
    CTexture* m_pTex;

public:
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    virtual void update();
    virtual void render(HDC _dc);

    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

    CLONE(CPanelUI)

public:
    CPanelUI();
    ~CPanelUI();
};

