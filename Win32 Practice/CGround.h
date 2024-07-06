#pragma once

class CObject;
class CTexture;


class CGround :
    public CObject
{
private:
    CTexture* m_pTex;
    int m_imgIdx;

private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetImgIdx(int _idx) { m_imgIdx = _idx; }
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
    CLONE(CGround);

public:

    CGround();
    ~CGround();
};

