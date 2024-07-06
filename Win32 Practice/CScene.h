#pragma once

//전방선언
class CObject;
class CTexture;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName;
	
	UINT			 m_iTileX;		//타일 가로 개수
	UINT			 m_iTileY;		//타일 세로 개수
	UINT			 m_CurSceneIndex;
	const int        m_gridX = 64;
	const int        m_gridY = 64;
	
	CTexture*		 m_pBackTex;

	int			 m_rotateState;
	Vec2 m_rotatePoint[3];

	UINT m_nextScene;

	// 회전용 여분 memDC
	HBITMAP m_hTempBit;
	HDC m_hTempDC;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; };
	UINT GetTileY() { return m_iTileY; };

	int GetArrX() { return m_gridX; };
	int GetArrY() { return m_gridY; };

	void SetBackTexture(CTexture* _pTex) { m_pBackTex = _pTex; }
	CTexture* GetBackTexture() { return m_pBackTex; }

	void SetRotatePoint(Vec2 _point0, Vec2 _point1, Vec2 _point2)
	{
		m_rotatePoint[0] = _point0;
		m_rotatePoint[1] = _point1;
		m_rotatePoint[2] = _point2;
	}


	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render();
	bool clear();


public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	void PopObject(GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].pop_back(); }
	

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	CObject* GetPlayer() { return m_arrObj[(UINT)GROUP_TYPE::PLAYER][0]; }

	int GetRotateState() { return m_rotateState; }
	void SetRotateState(int rotatestate) { m_rotateState = rotatestate; }

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	void CreateTileClick();
	void CreateTile(UINT _iXCount, UINT i_YCount);
	//void render_tile(HDC _dc);
	void CreateGrid(HDC _dc);

	void SetSceneIndex(SCENE_TYPE SceneIndex) {	m_CurSceneIndex = (UINT)SceneIndex;	}
	UINT GetSceneIndex() { return m_CurSceneIndex; }
	void SetNextScene(SCENE_TYPE _eNext) { m_nextScene = (UINT)_eNext; }
	UINT GetNextScene() { return m_nextScene; }

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }
	vector<CObject*>& GetTileGroup() { return m_arrObj[(UINT)GROUP_TYPE::TILE]; }

	void LoadTile(const wstring& _strFilePath);
	void LoadTileData();

	void RotateRight();
	void RotateLeft();

	void RenderRotation(float radian, Vec2 playerPosition);

public:
	CScene();
	virtual ~CScene();
};

