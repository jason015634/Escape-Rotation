#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration;
};

class CAnimation
{
private:
	wstring m_strName;
	CAnimator* m_pAnimator;	
	CTexture* m_pTex;	// Animation 이 사용하는 텍스쳐
	vector<tAnimFrm> m_vecFrm;	// 모든 프레임 정보
	int m_iCurFrm; // 현재 프레임
	float m_fAccTime; // 시간


	bool m_bFinish; // 재생 끝에 도달여부

public:
	const wstring& GetName()
	{
		return m_strName;
	}
	bool IsFinish()
	{
		return m_bFinish;
	}
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx)
	{
		return m_vecFrm[_iIdx];
	}

private:
	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}


public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	
	// 애니메이션을 파일로 저장한다.
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

