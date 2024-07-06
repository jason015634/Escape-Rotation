#pragma once
#include "CObject.h"

class CTexture;

class CTile :
	public CObject
{
private:
	CTexture*	m_pTileTex;
	int			m_iImgIdx;

public:
	void SetTexture(CTexture* _pTex)
	{
		m_pTileTex = _pTex;
	}

	void AddImgIdx()
	{
		++m_iImgIdx;
		if (m_iImgIdx > 19)
		{
			m_iImgIdx = 0;
		}
	}

	void SubImgIDx()
	{
		--m_iImgIdx;
		if (m_iImgIdx<0)
		{
			m_iImgIdx = 0;
		}
	}

	void SetImgIdx(int iImgIdx)
	{
		m_iImgIdx = iImgIdx;
	}

	int GetImgIdx()
	{
		return m_iImgIdx;
	}

private:
	virtual void update();
	virtual void render(HDC _dc);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CTile* Clone() { return new CTile(*this); }
public:
	CTile();
	~CTile();


};

