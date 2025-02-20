#pragma once
// KeyManager가 필요한 이유
// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// tap. hold, away ex) 점프




enum class KEY_STATE
{
	NONE, // 눌리지 않고, 이전에도 눌리지 않은 상태
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE eState; // 키의 상태값
	bool bPrevPush; // 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;
	Vec2			 m_vCurMousePos;
public:
	void init();
	void update();

	int CheckRotate();
	// 	KEY_STATE ClearKey();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{  
		return m_vecKey[(int)_eKey].eState;
	}

	void SetKeyUnable(KEY _eKey)
	{
		m_vecKey[(int)_eKey].eState = KEY_STATE::NONE;
	}

	void SetAllKeyUnable()
	{
		for (UINT i = 0; i < (UINT)KEY::LAST; i++)
		{
			m_vecKey[(int)i].eState = KEY_STATE::NONE;
		}
	}
	Vec2 GetMousePos()
	{
		return m_vCurMousePos;
	}
};

