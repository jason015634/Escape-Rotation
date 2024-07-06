#pragma once
#include "CScene.h"

class CUI;

class CScene_Stage_01 :
	public CScene
{
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Stage_01();
	~CScene_Stage_01();

private:
	CUI* m_pUI;

};

