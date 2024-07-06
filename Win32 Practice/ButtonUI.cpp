#include "pch.h"
#include "ButtonUI.h"
#include "CCore.h"

void ButtonUI::CreateButton()
{
	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();


	
	//HWND btn = CreateWindowW(L"button", L"¹öÆ°", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	//	pos.x, pos.y, scale.x, scale.y, CCore::GetInst()->GetMainHwnd(), (HMENU)0x1001, hInst, nullptr);

}
