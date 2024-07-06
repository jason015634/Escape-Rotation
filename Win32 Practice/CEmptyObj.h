#pragma once

class CTexture;

class CEmptyObj
	: public CObject
{
private:
	CTexture* m_pTex;
	int m_imgIdx;

private:
	virtual void update();
	virtual void render(HDC _dc);
public:
	void SetImgIdx(int _idx) { m_imgIdx = _idx; }
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }


	CLONE(CEmptyObj);
public:
	CEmptyObj();
	~CEmptyObj();
};

