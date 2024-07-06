#pragma once
#include "CScene.h"
class CScene_Level :
    public CScene
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Level();
    ~CScene_Level();
};

