#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"
#include "CTimeMgr.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	//
	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,
	//
	VK_LBUTTON,//��Ŭ��,
	VK_RBUTTON,
	//
	//LAST,
};

CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr()
{

}
void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	//������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();


	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)//Ű�� �����ִ�
			{
				if (m_vecKey[i].bPrevPush)//�������� �����־���
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else//������ �������� �ʾҴ�
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			else//Ű�� �ȴ����ִ�
			{
				if (m_vecKey[i].bPrevPush)//������ �����־���.
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else//������ �ȴ����־���.
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// Mouse ��ġ ���
		POINT ptPos = {};
		GetCursorPos(&ptPos);      // GetCursorPos �� ������ ��ü ����

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	else// �ش� �����찡 ��Ŀ�� �Ǿ����� ���� �� ������Ʈ�� �������� �ʰ� ����
	{
		for (size_t i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}


}


int CKeyMgr::CheckRotate()
{
	if (KEY_TAP(KEY::Q))
	{
		return -1;
	}

	if (KEY_TAP(KEY::E))
	{
		return 1;
	}

	return 0;
}

// KEY_STATE CKeyMgr::ClearKey()
// {
// 	return KEY_STATE::NONE;
// }