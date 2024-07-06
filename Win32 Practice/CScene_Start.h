#pragma once
#include "CScene.h"

class CUI;
class CBtnUI;

class CScene_Start :
    public CScene
{
private:
    CUI* m_pUI;
    //bool m_settingOn = false;

public:

   virtual void update();
   virtual void Enter();
   virtual void Exit();
    
   
public:
    CScene_Start();
    ~CScene_Start();
};