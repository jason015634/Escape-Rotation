#include "pch.h"
#include "CEmptyObj.h"
#include "CTexture.h"

void CEmptyObj::update()
{
}

void CEmptyObj::render(HDC _dc)
{
	if (nullptr == m_pTex || -1 == m_imgIdx)
		return;

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = (UINT)m_imgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_imgIdx / iMaxRow;

	if (iMaxRow < iCurRow)
		assert(nullptr);

	//Vec2 vPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();


	/*if (m_iImgIdx == 0)
	{
		TransparentBlt(_dc
			, vRenderPos.x
			, vRenderPos.y
			, vScale.x
			, vScale.y
			, m_pTileTex->GetDC()
			, iCurCol * TILE_SIZE
			, iCurRow * TILE_SIZE
			, TILE_SIZE
			, TILE_SIZE
			, RGB(255,0,255));
	}
	else
	{*/

	BitBlt(_dc
		, vRenderPos.x - vScale.x / 2.f
		, vRenderPos.y - vScale.y / 2.f
		, vScale.x
		, vScale.y
		, m_pTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
	//}
}

CEmptyObj::CEmptyObj()
{
}

CEmptyObj::~CEmptyObj()
{
}
