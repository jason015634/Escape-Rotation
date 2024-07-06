#pragma once
class CTexture;

class CSpike : public CObject
{
private:
	CTexture* m_pTex;
	CTexture* m_pTexSpike[4];
	int m_imgIdx;

private:
	virtual void start();
	virtual void update();
	virtual void render(HDC _dc);

public:

	void SetImgIdx(int _idx) { m_imgIdx = _idx; }
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);

	CTexture* GetTexture() { return m_pTex; }
	CLONE(CSpike);

public:
	CSpike();
	~CSpike();
};

