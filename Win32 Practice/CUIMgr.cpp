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
    // 1. FocusedUI 확인
    m_pFocusedUI = GetFocusedUI(); 
    // 어떤 UI도 포커싱 되지 않은 경우
    if (m_pFocusedUI == nullptr)
        return; 

    // 2. FocuesUI 내에서 부모 ui 포함, 자식 ui들 중 실제 타겟팅 된 ui를 가져온다.
    CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

    bool bLBtnTap = KEY_TAP(KEY::LBTN);
    bool bLBtnAway = KEY_AWAY(KEY::LBTN);
    

    if (pTargetUI != nullptr)
    {
        pTargetUI->MouseOn(); 

        // 클릭 이벤트 호출
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

// 부모 UI 포커싱 강제변경(ex, I : 인벤토리 창)
void CUIMgr::SetFocusedUI(CUI* _pUI)
{
    // 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
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

    // 벡터 내에서 맨 뒤로 순번 교체
    vecUI.erase(iter);
    vecUI.push_back(m_pFocusedUI);
}

// 부모 UI 포커싱
CUI* CUIMgr::GetFocusedUI()
{
    // 현재 포커싱 된 ui를 부모 ui 벡터에서 가장 마지막으로 보내주면 렌더링 상에서 우선순위를 가짐
    // 원본 벡터를 수정해야 함, GetUIGroup() 추가
    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
    vector<CObject*>& vecUI = pCurScene->GetUIGroup();

    bool bLBtnTap = KEY_TAP(KEY::LBTN);

    // 기존 포커싱 ui를 받아두고 변경되었는지 확인
    CUI* pFocuesdUI = m_pFocusedUI;

    if (!bLBtnTap)
    {
        return pFocuesdUI;
    }

    // 왼쪽버튼 tap 발생 > 어떤 ui도 안 눌렸을 경우가 존재
    vector<CObject*>::iterator targetiter = vecUI.end();
    vector<CObject*>::iterator iter = vecUI.begin();

    for (; iter!=vecUI.end(); ++iter)
    {
        if (((CUI*)*iter)->IsMouseOn())
        {
            targetiter = iter;
        }
    }

    // 어떤 UI도 포커싱되지 않은 경우
    if (vecUI.end() == targetiter)
    {
        return nullptr;
    }

    pFocuesdUI = (CUI*)*targetiter;

    // 벡터 내에서 맨 뒤로 순번 교체
    vecUI.erase(targetiter);
    vecUI.push_back(pFocuesdUI);

    return pFocuesdUI;
}

// 포커싱 된 부모 UI 안에서 이벤트를 받을 자식 UI 찾기
CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
    // 1. 부모 UI 포함, 모든 자식들을 검사한다.
    //    얼마나 계층적으로 구성되어 있을지 알 수 없다. 재귀함수?
    // 
    // 2. 동시에 여러 개의 UI가 본인이 타겟팅 되었음을 알 수 있고,
    //    자식 UI의 이벤트 감지 우선순위가 가장 높다
    //
    // 3. 트리에서 계층별로 순회하는 방식, 레벨 순회로 진행한다.
    //    재귀함수로는 레벨 순회를 진행할 수 없다. 큐로 구현할 것
    // 
    // 4. 큐로 사용하면 가장 앞의 데이터가 계속 삭제된다. 리스트로 큐처럼 사용할 것

    CUI* pTargetUI = nullptr;

    bool bLBtnAway = KEY_AWAY(KEY::LBTN);

    static list<CUI*> queue;
    static vector<CUI*> vecNoneTarget;

    queue.clear();
    vecNoneTarget.clear();

    queue.push_back(_pParentUI);


    while (!queue.empty())
    {
        // 큐에서 데이터 하나 꺼내기
        CUI* pUI = queue.front();
        queue.pop_front();

        // 큐에서 꺼내온 ui가 target ui인지 확인
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

        // 자식 ui 큐에 포함
        const vector<CUI*>& vecChild = pUI->GetChildUI();
        for (size_t i = 0; i < vecChild.size(); i++)
        {
            queue.push_back(vecChild[i]);
        }

        // 왼쪽버튼을 떼면 눌렸던 체크를 다시 해제한다
        // 범위 안에서 down, 범위 밖에서 up하는 경우의 예외처리
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
