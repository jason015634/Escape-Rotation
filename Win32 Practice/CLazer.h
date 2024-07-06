#pragma once
#include "CGround.h"

class CLever;
class CGround;

class CLazer :
    public CObject
{
private:
    CTexture* m_pTex;
    int m_Idx;
private:
    CLever* m_pOwnerLever;
    CObject* m_pOwnerGround;
public:
    virtual void render(HDC _dc);
    virtual void update();
    virtual void start();

public:
    CObject* GetOwnerGround() { return m_pOwnerGround; }
    CLever* GetOwnerLever() { return m_pOwnerLever; }

    void SetIdx(int _idx) { m_Idx = _idx; }
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    void SetOwnerGround(CObject* OwnerName) { m_pOwnerGround = OwnerName; }
    void SetOwnerLever(CLever* OwnerName) { m_pOwnerLever = OwnerName; }
    
    CLONE(CLazer)
public:
    CLazer();
    ~CLazer();
};

