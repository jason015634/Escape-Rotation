#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	CScene* m_pCurScene; // ���� ��

public:
	void init();
	void update();
	void render();

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);
	void ChangeScene(SCENE_TYPE _eNext, SCENE_TYPE _eNNext);
	friend class CEventMgr;
};

