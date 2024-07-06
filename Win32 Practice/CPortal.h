#pragma once
#include "CObject.h"

class CTexture;

class CPortal :
    public CObject
{
private:
    CTexture* m_pTex;
    int m_imgIdx;
    bool m_bClear;

private:
    bool m_isManipulable;
private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);
public:
    void SetImgIdx(int _idx) { m_imgIdx = _idx; }
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CTexture* GetTexture() { return m_pTex; }
    void ChangeState(bool _b) { m_isManipulable = _b; }
    CLONE(CPortal);
public:
    CPortal();
    ~CPortal();
};

