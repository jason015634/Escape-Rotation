#pragma once
#include "CScene.h"

class CScene_CutScene :
    public CScene
{
private:
	int m_sceneNum;
	int m_cutNum;

	vector<CTexture*> m_pTex[12];
	

public:


	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_CutScene();
	~CScene_CutScene();
};

