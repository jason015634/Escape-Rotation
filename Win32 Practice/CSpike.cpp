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
	// Spike img idx�� 4~7

	int rotatestate = CSceneMgr::GetInst()->GetCurScene()->GetRotateState();

	// ���� 1�� �����ϴ� ���� rotation�� ���̴� ImgIdx ���� 0,1,2,3���� ����� �� ��
	// rotation���� ���� �װ� ��ⷯ ������ ���ָ� pTexSpike���� �̹��� �ε����� ���� ������
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
