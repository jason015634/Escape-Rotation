#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    float m_fSpeed;
    Vec2 m_vCenterPos;
    float m_fMaxDistance;
    int m_iDir; // 1, -1
public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f){m_fSpeed = _f;}
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }

public:
    virtual void update();

public:
    CMonster();
    ~CMonster();
};


