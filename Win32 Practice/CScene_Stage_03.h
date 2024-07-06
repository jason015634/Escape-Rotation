#pragma once
#include "CScene.h"

class CUI;

class CScene_Stage_03 :
	public CScene
{
private:
	CUI* m_pUI;

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Stage_03();
	~CScene_Stage_03();
};

