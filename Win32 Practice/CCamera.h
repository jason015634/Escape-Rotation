#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);

private:
	Vec2		m_vLookAt;		//카메라가 보는 위치
	CObject*	m_pTargetObj;	//카메라가 잡는 타켓 오브젝트

	Vec2		m_vDiff;		//해상도 중심위치와, 현재 보고 있는 좌표값 간의 차이 값

public:
	void SetLookAt(Vec2 _vLook) { 
		m_vLookAt = _vLook; 
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	//void SetRenderPos(Vec2 )
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	Vec2 GetLookAt()
	{
		return m_vLookAt;
	}
public:
	void init();

	void update();
	


private:
	void CalDiff();
};

