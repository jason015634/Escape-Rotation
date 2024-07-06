#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
    :m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
    // 1. FocusedUI Ȯ��
    m_pFocusedUI = GetFocusedUI(); 
    // � UI�� ��Ŀ�� ���� ���� ���
    if (m_pFocusedUI == nullptr)
        return; 

    // 2. FocuesUI ������ �θ� ui ����, �ڽ� ui�� �� ���� Ÿ���� �� ui�� �����´�.
    CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

    bool bLBtnTap = KEY_TAP(KEY::LBTN);
    bool bLBtnAway = KEY_AWAY(KEY::LBTN);
    

    if (pTargetUI != nullptr)
    {
        pTargetUI->MouseOn(); 

        // Ŭ�� �̺�Ʈ ȣ��
        if (bLBtnTap)
        {
            pTargetUI->MouseLbtnDown();
            pTargetUI->m_bLbtnDown = true;
        }
        else if (bLBtnAway)
        {
            pTargetUI->MouseLbtnUp();

            if (pTargetUI->m_bLbtnDown)
            {
                pTargetUI->MouseLbtnClicked();
            }

            pTargetUI->m_bLbtnDown = false;
        }
    }
}

// �θ� UI ��Ŀ�� ��������(ex, I : �κ��丮 â)
void CUIMgr::SetFocusedUI(CUI* _pUI)
{
    // �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
    if (m_pFocusedUI == _pUI || nullptr == _pUI)
    {
        m_pFocusedUI = _pUI;
        return;
    }

    m_pFocusedUI = _pUI;

    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
    vector<CObject*>& vecUI = pCurScene->GetUIGroup();

    vector<CObject*>::iterator iter = vecUI. begin();

    for (; iter != vecUI.end(); ++iter)
    {
        if (m_pFocusedUI == *iter)
        {
            break;
        }
    }

    // ���� ������ �� �ڷ� ���� ��ü
    vecUI.erase(iter);
    vecUI.push_back(m_pFocusedUI);
}

// �θ� UI ��Ŀ��
CUI* CUIMgr::GetFocusedUI()
{
    // ���� ��Ŀ�� �� ui�� �θ� ui ���Ϳ��� ���� ���������� �����ָ� ������ �󿡼� �켱������ ����
    // ���� ���͸� �����ؾ� ��, GetUIGroup() �߰�
    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
    vector<CObject*>& vecUI = pCurScene->GetUIGroup();

    bool bLBtnTap = KEY_TAP(KEY::LBTN);

    // ���� ��Ŀ�� ui�� �޾Ƶΰ� ����Ǿ����� Ȯ��
    CUI* pFocuesdUI = m_pFocusedUI;

    if (!bLBtnTap)
    {
        return pFocuesdUI;
    }

    // ���ʹ�ư tap �߻� > � ui�� �� ������ ��찡 ����
    vector<CObject*>::iterator targetiter = vecUI.end();
    vector<CObject*>::iterator iter = vecUI.begin();

    for (; iter!=vecUI.end(); ++iter)
    {
        if (((CUI*)*iter)->IsMouseOn())
        {
            targetiter = iter;
        }
    }

    // � UI�� ��Ŀ�̵��� ���� ���
    if (vecUI.end() == targetiter)
    {
        return nullptr;
    }

    pFocuesdUI = (CUI*)*targetiter;

    // ���� ������ �� �ڷ� ���� ��ü
    vecUI.erase(targetiter);
    vecUI.push_back(pFocuesdUI);

    return pFocuesdUI;
}

// ��Ŀ�� �� �θ� UI �ȿ��� �̺�Ʈ�� ���� �ڽ� UI ã��
CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
    // 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
    //    �󸶳� ���������� �����Ǿ� ������ �� �� ����. ����Լ�?
    // 
    // 2. ���ÿ� ���� ���� UI�� ������ Ÿ���� �Ǿ����� �� �� �ְ�,
    //    �ڽ� UI�� �̺�Ʈ ���� �켱������ ���� ����
    //
    // 3. Ʈ������ �������� ��ȸ�ϴ� ���, ���� ��ȸ�� �����Ѵ�.
    //    ����Լ��δ� ���� ��ȸ�� ������ �� ����. ť�� ������ ��
    // 
    // 4. ť�� ����ϸ� ���� ���� �����Ͱ� ��� �����ȴ�. ����Ʈ�� ťó�� ����� ��

    CUI* pTargetUI = nullptr;

    bool bLBtnAway = KEY_AWAY(KEY::LBTN);

    static list<CUI*> queue;
    static vector<CUI*> vecNoneTarget;

    queue.clear();
    vecNoneTarget.clear();

    queue.push_back(_pParentUI);


    while (!queue.empty())
    {
        // ť���� ������ �ϳ� ������
        CUI* pUI = queue.front();
        queue.pop_front();

        // ť���� ������ ui�� target ui���� Ȯ��
        if (pUI->IsMouseOn())
        {
            if (pTargetUI != nullptr)
            {
                vecNoneTarget.push_back(pTargetUI);
            }
            pTargetUI = pUI;
        }
        else
        {
            vecNoneTarget.push_back(pUI);
        }

        // �ڽ� ui ť�� ����
        const vector<CUI*>& vecChild = pUI->GetChildUI();
        for (size_t i = 0; i < vecChild.size(); i++)
        {
            queue.push_back(vecChild[i]);
        }

        // ���ʹ�ư�� ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
        // ���� �ȿ��� down, ���� �ۿ��� up�ϴ� ����� ����ó��
        if (bLBtnAway)
        {
            for (size_t i = 0; i < vecNoneTarget.size(); i++)
            {
                vecNoneTarget[i]->m_bLbtnDown = false;
            }
        }
    }


    return pTargetUI;
}
