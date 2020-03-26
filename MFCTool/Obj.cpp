#include "stdafx.h"
#include "Obj.h"
#include "MFCToolView.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

bool CObj::Check_MousePt(const D3DXVECTOR3 & point)
{
	RECT rect = {
		m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f,
		m_tInfo.vPos.y - m_tInfo.vSize.x / 2.f,
		m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f,
		m_tInfo.vPos.y + m_tInfo.vSize.x / 2.f
	};

	POINT pt = { point.x, point.y };
	if(PtInRect(&rect, pt)) {
		return true;
	}

	return false;
}

void CObj::Initialize(int objID, const D3DXVECTOR3& point)
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Object", L"Object", objID);

	m_iObjID = objID;
	m_tInfo.vPos = point;
	m_tInfo.vSize.x = pTexInfo->tImageInfo.Width;
	m_tInfo.vSize.y = pTexInfo->tImageInfo.Height;
}

void CObj::Render(CView* pView)
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Object", L"Object", m_iObjID);
	assert(!(nullptr == pTexInfo));

	D3DXVECTOR3 vCenter;
	vCenter.x = pTexInfo->tImageInfo.Width / 2.f;
	vCenter.y = pTexInfo->tImageInfo.Height / 2.f;

	D3DXMATRIX matScale, matTrans, matWorld;
	float fX = WINCX / float(pTexInfo->tImageInfo.Width);
	float fY = WINCY / float(pTexInfo->tImageInfo.Height);

	D3DXMatrixScaling(&matScale, 1, 1, 0.f);
	D3DXMatrixTranslation(&matTrans, OFFSET + m_tInfo.vPos.x - pView->GetScrollPos(0),
		OFFSET + m_tInfo.vPos.y - pView->GetScrollPos(1), 0.f);
	matWorld = matScale * matTrans;

	RECT rc = {};
	pView->GetClientRect(&rc);
	fX = WINCX / float(rc.right - rc.left);
	fY = WINCY / float(rc.bottom - rc.top);
	SetRatio(&matWorld, fX, fY);

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr,
		&vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CObj::SetRatio(D3DXMATRIX * pOut, const float & fRatioX, const float & fRatioY)
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