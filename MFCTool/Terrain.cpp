#include "stdafx.h"
#include "Terrain.h"
#include "MFCToolView.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release(); 

}

void CTerrain::TileChange(const D3DXVECTOR3 & rMouse, const BYTE & rbyDrawID, const BYTE & rbyOption/*=0*/)
{
	int iIndex = Get_Index(rMouse);

	if (-1 == iIndex)
		return; 

	m_vecTile[iIndex]->byDrawID = rbyDrawID; 
	m_vecTile[iIndex]->byOption = rbyOption; 
}

int CTerrain::Get_Index(const D3DXVECTOR3 & rPos)
{
	size_t iSize = m_vecTile.size(); 
	for (size_t i = 0; i < iSize ; ++i)
	{
		if (IsPicking(rPos, i))
			return i; 
	}
	return -1;
}

bool CTerrain::IsPicking(const D3DXVECTOR3 & rPos, const int & iIndex)
{
	// ㅇㅋ? 
	// 12, 3, 6, 9 순으로 마름모꼴 꼭지점 구하기. 
 	D3DXVECTOR3 vPoint[4] = 
 	{
		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f) , m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f }
 	};
	// 시계방향으로 각각 방향벡터 구할 것. 
	D3DXVECTOR3 vDir[4] = 
	{
		// 목적지 - 출발지 
		vPoint[1] - vPoint[0], 
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3 vNormal[4] = {}; 
	for (int i = 0; i < 4; ++i)
		vNormal[i] = { -vDir[i].y, vDir[i].x, 0.f };

	D3DXVECTOR3 vMouseDir[4] = 
	{
		rPos - vPoint[0],
		rPos - vPoint[1],
		rPos - vPoint[2],
		rPos - vPoint[3],
	};

	for (int i = 0 ; i < 4 ; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);

		if (0 < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;

	}
	return true; 
}

void CTerrain::SetRatio(D3DXMATRIX * pOut, const float & fRatioX, const float & fRatioY)
{
	/*
	11	12	13	14
	21	22	23	24
	31	32	33	34
	41	42	43	44
	*/
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;

}

HRESULT CTerrain::Initialize(int iTileX, int iTileY, BYTE byDrawID, E_TILE::OPTION eOption)
{
	m_iTileX = iTileX;
	m_iTileY = iTileY;
	float fX = 0.f, fY = 0.f; 
	TILE* pTile = nullptr; 
	for (int i = 0 ; i < iTileY; ++i)
	{
		for (int j = 0 ; j < iTileX; ++j)
		{
			fX = float((j * TILECX) + (TILECX >> 1));
			fY = float((i * TILECY) + (TILECY >> 1));
			pTile = new TILE;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f, 1.f, 0.f };
			pTile->byDrawID = byDrawID;
			pTile->byOption = eOption;
			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	RECT rc = {}; 
	m_pView->GetClientRect(&rc);
	float fX = WINCX / float(rc.right - rc.left);
	float fY = WINCY / float(rc.bottom - rc.top);
	int iIndex = 0; 
	TCHAR szBuf[64] = L""; 
	for (auto& pTile : m_vecTile)
	{
		swprintf_s(szBuf, L"%d", iIndex);
		const TEXINFO* pTexInfo  = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile", pTile->byDrawID);
		if (nullptr == pTexInfo)
			return; 
		float fCenterX = pTexInfo->tImageInfo.Width * 0.5f; 
		float fCenterY = pTexInfo->tImageInfo.Height * 0.5f; 

		//GetScrollPos - 스크롤 얻어오는 함수. 0일경우 x , 1일경우 y 

		D3DXMatrixScaling(&matScale, pTile->vSize.x, pTile->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, OFFSET + pTile->vPos.x - m_pView->GetScrollPos(0), OFFSET + pTile->vPos.y - m_pView->GetScrollPos(1), 0.f);
		matWorld = matScale * matTrans; 
		SetRatio(&matWorld, fX, fY);
		// 크, 자, 이, 공, 부 
		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
		GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
		GET_INSTANCE(CDevice)->Get_Font()->DrawTextW(GET_INSTANCE(CDevice)->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0,0,0));


		++iIndex; 
	}
	// 2D에서 직교백터를 뽑아내는 방법. 
	// X와 Y를 바꾸고 X에 -만 붙여주면 끝! 
	// 
}

void CTerrain::MiniRender()
{
	D3DXMATRIX matScale, matTrans, matWorld; 

	size_t iSize = m_vecTile.size(); 
	for (size_t i = 0 ; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		if (nullptr == pTexInfo)
			return; 

		float fCenterX = pTexInfo->tImageInfo.Width * 0.5f; 
		float fCenterY = pTexInfo->tImageInfo.Height *0.5f; 

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x, m_vecTile[i]->vPos.y, 0.f); 
		matWorld = matScale * matTrans; 

		float fScaleX = WINCX / float(m_iTileX * TILECX);
		float fScaleY = WINCY / float(m_iTileY * TILECY);
		float fMinScale = min(fScaleX, fScaleY);

		SetRatio(&matWorld, fMinScale, fMinScale);

		GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld); 
		GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>); 

	m_vecTile.clear(); 
	m_vecTile.shrink_to_fit();
}
