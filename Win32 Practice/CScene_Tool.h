#pragma once
#include "CScene.h"
class CScene_Tool :
	public CScene
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
	//virtual void render(HDC _dc);
public:

	void SetTileIdx();
	
	void SaveTileData();
	void LoadTileData();
	void SaveTile(const wstring& _strFilePath);

public:
	CScene_Tool();
	~CScene_Tool();
};
