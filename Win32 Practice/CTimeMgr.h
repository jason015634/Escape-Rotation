#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;
	//FPS
	//1 프레임당 시간 (Delta Time)

	double m_dDT;//프레임 간의 시간값(DeltaTime)
	double m_dAcc;//1초 체크를 위한 누적시간
	UINT m_iCallCount;
	UINT m_iFPS;//초당 호출 횟수

	// test
	Vec2 m_playerPos;
	Vec2 m_cameraPos;
	Vec2 m_mousePos;
	Vec2 m_realPos;

public:
	void init();
	void update();
	bool CheckAcc();	// 1초 체크하는 함수입니다.
	void render();
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return(float)m_dDT; }
	UINT GetFPS() { return m_iFPS; }
};

