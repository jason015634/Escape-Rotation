#include "pch.h"
#include "CTile.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CScene.h"

CTile::CTile()
	:m_pTileTex(nullptr)
	,m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if(CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Tool Scene")
	{
		if (nullptr == m_pTileTex || -1 == m_iImgIdx)
			return;

		UINT iWidth = m_pTileTex->Width();
		UINT iHeight = m_pTileTex->Height();

		UINT iMaxCol = iWidth / TILE_SIZE;
		UINT iMaxRow = iHeight / TILE_SIZE;

		UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
		UINT iCurCol = (UINT)m_iImgIdx / iMaxRow;

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
				, vRenderPos.x
				, vRenderPos.y
				, vScale.x
				, vScale.y
				, m_pTileTex->GetDC()
				, iCurCol * TILE_SIZE
				, iCurRow * TILE_SIZE
				, SRCCOPY);
		//}
	}
	/*Rectangle(_dc, 
		int(vRenderPos.x),
		int(vRenderPos.y),
		int(vRenderPos.x + vScale.x),
		int(vRenderPos.y + vScale.y));*/


}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
