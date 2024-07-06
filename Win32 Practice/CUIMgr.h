#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusedUI;	// 현재 포커싱 된 ui, 이벤트를 받아감

public:
	void update();

	// 클릭 이벤트가 아닌 단축키 등으로 강제로 포커스 ui를 바꾸는 함수
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환한다

};
