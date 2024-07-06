#pragma once
#include "CObject.h"

class CTexture;

class CLever :
    public CObject
{
private:
    bool m_isManipulable;
    bool m_isOn;
private:
    CTexture* m_pTex;
    int m_Idx;

    CTexture* pTex_Red_lever[4];
    CTexture* pTex_Blue_lever[4];

private:
   virtual void start();
   virtual void update();
   virtual void render(HDC _dc);

public:
    void SetIdx(int _idx) { m_Idx = _idx; }
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
    void SetOnOff(bool _isOn) { m_isOn = _isOn; }

    CTexture* GetTexture() { return m_pTex; }
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    void ChangeState(bool _b) { m_isManipulable = _b; }
    bool GetOnOff() { return m_isOn; }

    CLONE(CLever);
public:
    CLever();
    ~CLever();
};

