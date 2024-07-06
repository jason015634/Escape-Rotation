#pragma once
#include "CObject.h"



enum class PLAYER_STATE
{
    IDLE,
    WALK,
    JUMP
};




class CTexture;

class CPlayer :
    public CObject
{
private:
    vector<CObject*> m_vecCOlObj;

    PLAYER_STATE m_eCurState;
    PLAYER_STATE m_ePrevState;
    int m_iDir;
    int m_iPrevDir;

public:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);

    PLAYER_STATE GetCurState() { return m_eCurState; }

private:
    //void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

    virtual void OnCollisionEnter(CCollider* _pOther);
    void OnCollision(CCollider* _pOther);
    void update_sound();

    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();
};

