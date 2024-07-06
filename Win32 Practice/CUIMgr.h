#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusedUI;	// ���� ��Ŀ�� �� ui, �̺�Ʈ�� �޾ư�

public:
	void update();

	// Ŭ�� �̺�Ʈ�� �ƴ� ����Ű ������ ������ ��Ŀ�� ui�� �ٲٴ� �Լ�
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�

};
