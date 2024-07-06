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
	VK_LBUTTON,//좌클릭,
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
	//윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();


	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)//키가 눌려있다
			{
				if (m_vecKey[i].bPrevPush)//이전에도 눌려있었다
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else//이전에 눌려있지 않았다
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			else//키가 안눌려있다
			{
				if (m_vecKey[i].bPrevPush)//이전에 눌려있었다.
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else//이전에 안눌려있었다.
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// Mouse 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos);      // GetCursorPos 는 윈도우 전체 기준

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	else// 해당 윈도우가 포커싱 되어있지 않을 때 오브젝트가 움직이지 않게 해줌
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