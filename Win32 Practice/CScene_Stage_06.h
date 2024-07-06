#pragma once
#include "CScene.h"

class CUI;

class CScene_Stage_06 :
	public CScene
{
private:
	CUI* m_pUI;

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Stage_06();
	~CScene_Stage_06();
};

