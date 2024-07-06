#pragma once
// KeyManager�� �ʿ��� ����
// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��
// tap. hold, away ex) ����




enum class KEY_STATE
{
	NONE, // ������ �ʰ�, �������� ������ ���� ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
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
	KEY_STATE eState; // Ű�� ���°�
	bool bPrevPush; // ���� �����ӿ��� ���ȴ��� ����
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

