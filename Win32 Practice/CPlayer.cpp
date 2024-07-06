#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CSoundMgr.h"
#include "CGravity.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
{

	CreateRigidBody();

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));


	//Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Sprite.bmp");


	CreateAnimator();
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 0.f), Vec2(500.f, 500.f), Vec2(500.f, 0.f), 0.1f, 8);
	//GetAnimator()->Play(L"WALK_RIGHT", true);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 0.f), Vec2(500.f, 500.f), Vec2(500.f, 0.f), 0.1f, 8);
   // GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 500.f), Vec2(500.f, 500.f), Vec2(500.f, 0.f), 0.1f, 8);
	//GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vec2(80.f, 162.5f), Vec2(80.f, 83.25f), Vec2(0.f, 0.f), 0.5f, 2);
	//
	CreateGravity();

	//// 저장된 Animation 로드	// error : 한 프레임에 들어가야 할 스프라이트가 여러장 들어가는 버그있음
	//GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_run_right.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_run_left.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");



	// Animation 저장하기 
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 160.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 240.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"RUN_RIGHT", pTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 0.08f, 8);
	GetAnimator()->CreateAnimation(L"RUN_LEFT", pTex, Vec2(560.f, 80.0f), Vec2(80.f, 80.f), Vec2(-80.f, 0.f), 0.08f, 8);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pTex, Vec2(0.f, 320.0f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vec2(80.f, 320.0f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), 0.5f, 2);
	//Animation 저장하기
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"RUN_RIGHT")->Save(L"animation\\player_run_right.anim");
	//GetAnimator()->FindAnimation(L"RUN_LEFT")->Save(L"animation\\player_run_left.anim");
	//GetAnimator()->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\player_jump_right.anim");
	//GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player_jump_left.anim");

// 	CPathMgr::GetInst()->init();
// 	CSoundMgr::GetInst()->init();
	//GetAnimator()->Play(L"RUN_RIGHT", true);
	//GetAnimator()->Play(L"IDLE_RIGHT", true);
}

CPlayer::~CPlayer()
{
}

void CPlayer::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CPlayer::update()
{
	//Vec2 vPos = GetPos();
	//float playerSpeed = 200.f;   // playerObject의 이동속도
	//CRigidBody* pRigid = GetRigidBody();  
	update_move();
	update_state();

	update_animation();
	update_sound();

	if (KEY_HOLD(KEY::UP))
	{
		//CreateMissile();      // 상호작용
  //        CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Portal);
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;


}

void CPlayer::render(HDC _dc)
{

	//컴포넌트(충돌체, etc...)가 있는 경우 렌더
	component_render(_dc);
}

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::LEFT))
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
	}
	if (!(KEY_HOLD(KEY::RIGHT)) && !(KEY_HOLD(KEY::LEFT)))
	{
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_HOLD(KEY::RIGHT) && KEY_HOLD(KEY::LEFT))
	{
		if (m_iPrevDir == 1)
		{
			m_iDir = 1;
		}
		else
		{
			m_iDir = -1;
		}
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::IDLE;
	}

	//     if (0.f == GetRigidBody()->GetSpeed())
	//     {
	//         m_eCurState = PLAYER_STATE::IDLE;
	//     }

	if (GetRigidBody()->GetSpeed() == 0.f && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		if (GetGravity()->isGround())
			m_eCurState = PLAYER_STATE::JUMP;
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::LEFT))
	{
		//vPos.x -= playerSpeed * fDT;
		pRigid->SetVelocity(Vec2(-300.f, pRigid->GetVelocity().y));
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		//vPos.x += playerSpeed * fDT;
		pRigid->SetVelocity(Vec2(300.f, pRigid->GetVelocity().y));
	}

	if (KEY_TAP(KEY::LEFT))
	{
		pRigid->SetVelocity(Vec2(-300.f, pRigid->GetVelocity().y));
		if (KEY_HOLD(KEY::RIGHT))
		{
			pRigid->SetVelocity(Vec2(0.f, pRigid->GetVelocity().y));
		}
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		pRigid->SetVelocity(Vec2(300.f, pRigid->GetVelocity().y));
		if (KEY_HOLD(KEY::LEFT))
		{
			pRigid->SetVelocity(Vec2(0.f, pRigid->GetVelocity().y));
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		if (GetRigidBody() && !(m_eCurState == PLAYER_STATE::JUMP) && GetGravity()->isGround())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -1000.f));
		}
	}

	if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
	{
		pRigid->SetVelocity(Vec2(0.f, pRigid->GetVelocity().y));
	}

	if (KEY_HOLD(KEY::LEFT) && KEY_HOLD(KEY::RIGHT))
	{
		pRigid->SetVelocity(Vec2(0.f, pRigid->GetVelocity().y));
	}


}

void CPlayer::update_animation()
{
	/*if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
	{
		return;
	}*/
	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"IDLE_RIGHT", true);

	}

	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"RUN_LEFT", true);
		else
			GetAnimator()->Play(L"RUN_RIGHT", true);


	}
	break;
	case PLAYER_STATE::JUMP:
		if (m_iDir == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);


		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground" || pOtherObj->GetName() == L"Lazer")
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		if (vPos.y + vScale.y / 2.f <= pOtherObj->GetPos().y - pOtherObj->GetScale().y / 2.f)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}
void CPlayer::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground" || pOtherObj->GetName() == L"Lazer")
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		if (vPos.y + vScale.y / 2.f <= pOtherObj->GetPos().y - pOtherObj->GetScale().y / 2.f)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}


void CPlayer::update_sound()
{
	if (m_ePrevState == PLAYER_STATE::IDLE || m_ePrevState == PLAYER_STATE::WALK)
	{
		if (m_eCurState == PLAYER_STATE::JUMP)
		{
			CSoundMgr::GetInst()->PlaySFX(SFX_SOUND::Player_Jump);
		}
	}
}
