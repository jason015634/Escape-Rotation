#include "pch.h"
#include "CSpike.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CScene.h"
#include "CObject.h"

CSpike::CSpike()
	:m_pTex(nullptr)
	, m_imgIdx(4)
{
	CreateCollider();
}

CSpike::~CSpike()
{

}

void CSpike::start()
{
	m_pTexSpike[0] = CResMgr::GetInst()->LoadTexture(L"Spike", L"texture\\thorn.bmp");
	m_pTexSpike[1] = CResMgr::GetInst()->LoadTexture(L"Spike2", L"texture\\thorn2.bmp");
	m_pTexSpike[2] = CResMgr::GetInst()->LoadTexture(L"Spike3", L"texture\\thorn3.bmp");
	m_pTexSpike[3] = CResMgr::GetInst()->LoadTexture(L"Spike4", L"texture\\thorn4.bmp");
}

void CSpike::update()
{

}

void CSpike::render(HDC _dc)
{

	if (nullptr == m_pTex || -1 == m_imgIdx)
		return;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	// Spike img idx는 4~7

	int rotatestate = CSceneMgr::GetInst()->GetCurScene()->GetRotateState();

	// 현재 1씩 증가하는 값은 rotation값 뿐이니 ImgIdx 값을 0,1,2,3으로 만들어 준 후
	// rotation값을 더해 그걸 모듈러 연산을 해주면 pTexSpike값이 이미지 인덱스에 따라서 증가함
	BitBlt(_dc
		, vRenderPos.x - vScale.x / 2.f
		, vRenderPos.y - vScale.y / 2.f
		, vScale.x
		, vScale.y
		, m_pTexSpike[((m_imgIdx - 4) + rotatestate) % 4]->GetDC()
		, 0
		, 0
		, SRCCOPY);

	//component_render(_dc);

}
void CSpike::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		ChangeScene((SCENE_TYPE)(CSceneMgr::GetInst()->GetCurScene()->GetSceneIndex()));
	}
}

void CSpike::OnCollision(CCollider* _pOther)
{
}
