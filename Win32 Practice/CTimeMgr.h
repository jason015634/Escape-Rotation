#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;
	//FPS
	//1 �����Ӵ� �ð� (Delta Time)

	double m_dDT;//������ ���� �ð���(DeltaTime)
	double m_dAcc;//1�� üũ�� ���� �����ð�
	UINT m_iCallCount;
	UINT m_iFPS;//�ʴ� ȣ�� Ƚ��

	// test
	Vec2 m_playerPos;
	Vec2 m_cameraPos;
	Vec2 m_mousePos;
	Vec2 m_realPos;

public:
	void init();
	void update();
	bool CheckAcc();	// 1�� üũ�ϴ� �Լ��Դϴ�.
	void render();
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return(float)m_dDT; }
	UINT GetFPS() { return m_iFPS; }
};

