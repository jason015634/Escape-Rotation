#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CObject.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
{

}

CAnimation::~CAnimation()
{

}

void CAnimation::update()
{
	if (m_bFinish)
	{
		return;
	}
	m_fAccTime += fDT;

	// todo : 애니메이션 재생이 한 번 끝나고 다음 재생 이전에 버퍼링을 방지하기 위한 코드, 추가 설명 필요
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
	{
		return;
	}

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255)
	);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};

	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// 저장된 파일을 사용자가 수정하기 쉬워진다.	
	// Animation 의 이름을 저장한다.(데이터 직렬화)
	fprintf(pFile, "[Animation_Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// Animation 이 사용하는 텍스쳐
	fprintf(pFile, "[Texture_Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture_Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// 프레임 개수
	fprintf(pFile, "[Frame_Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	// 모든 프레임 정보
	for (int i = 0; i < (int)m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame_Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left_Top]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice_Size]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		//fprintf(pFile, "[Offset]\n");
		//fprintf(pFile, "%d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");
	}


	/*
	// 데이터를 조금 쓰는 대신에 저장된 텍스트파일을 수정할 수가 없다.
	// Animation 의 이름을 저장한다.(데이터 직렬화)
	SaveWString(m_pTex->GetKey(), pFile);

	// Animation 이 사용하는 텍스쳐
	SaveWString(m_pTex->GetKey(), pFile);
	SaveWString(m_pTex->GetRelativePath(), pFile);

	// 프레임 개수
	size_t iFrameCount = m_vecFrm.size();
	fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보
	fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);
	*/


	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);


	// Animation 의 이름을 읽어온다.
	string str;
	char szBuff[256] = {};

	fscanf_s(pFile, "%s", szBuff, 256);
	fscanf_s(pFile, "%s", szBuff, 256);
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());

	// 참조하는 텍스쳐 이름 및 경로
	fscanf_s(pFile, "%s", szBuff, 256);
	fscanf_s(pFile, "%s", szBuff, 256);
	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	fscanf_s(pFile, "%s", szBuff, 256);
	fscanf_s(pFile, "%s", szBuff, 256);
	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);

	// 프레임 개수
	fscanf_s(pFile, "%s", szBuff, 256);
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);

	// 모든 프레임 정보
	tAnimFrm frm = {};
	for (int i = 0; i < iFrameCount; ++i)
	{
		POINT pt = {};

		while (true)
		{
			fscanf_s(pFile, "%s", szBuff, 256);

			if (!strcmp("[Frame_Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left_Top]", szBuff))
			{
				fscanf_s(pFile, "%d, %d", &pt.x, &pt.y);

				frm.vLT = pt;
			}
			else if (!strcmp("[Slice_Size]", szBuff))
			{
				fscanf_s(pFile, "%d, %d", &pt.x, &pt.y);

				frm.vSlice = pt;
			}
			//else if (!strcmp("[Offset]", szBuff))
			//{
			//fscanf_s(pFile, "%d", &pt.x);
			//fscanf_s(pFile, "%d", &pt.y);
			// 
			//frm.vOffset = pt;
			//}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);
				break;
			}

			m_vecFrm.push_back(frm);
		}
	}


	/*
	// 적은 데이터량
	// Animation 이름 읽기
	LoadWString(m_strName, pFile);

	// 텍스쳐
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);

	// 프레임 개수
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보
	m_vecFrm.resize(iFrameCount);
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);
	*/


	fclose(pFile);
}

