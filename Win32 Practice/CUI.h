#pragma once
#include "CObject.h"

// ���� ����� UI
// UI�� ������ ������ ������.
// ��� UI�� �ش� Ŭ������ ��ӹ޴´�.
class CUI :
	public CObject
{
private:
	vector<CUI*> m_vecChildUI;	// �ڽ� UI
	CUI*		 m_pParentUI;	// �θ� UI

	Vec2		 m_vFinalPos;	// ���� ��ġ

	bool		 m_bCamAffected;	// UI�� ī�޶� ������ �޴���
	bool		 m_bMouseOn;		// UI ���� ���콺�� �ִ���
	bool		 m_bLbtnDown;		// UI�� ���� ��ư�� �������� �ִ���

public:
	Vec2 GetFinalPos() { return m_vFinalPos; }
	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }

	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

	void DeleteUI();

public:
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

private:
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);
	
	
	bool MouseCheck() const { return m_bMouseOn; }

private:
	void MouseOnCheck();

public:
	// ���콺 Ŭ�� �̺�Ʈ
	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	//CLONE(CUI);
	virtual CUI* Clone() = 0;

public:
	CUI(bool _bCamAff);
	CUI(const CUI& _origin);
	CUI();
	virtual ~CUI();

	friend class CUIMgr;
};
