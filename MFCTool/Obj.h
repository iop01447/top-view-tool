#pragma once
class CObj
{
public:
	CObj();
	~CObj();

public:
	bool Check_MousePt(const D3DXVECTOR3& point);
	void Initialize(int objID, const D3DXVECTOR3& point);
	void SetRatio(D3DXMATRIX * pOut, const float & fRatioX, const float & fRatioY);

public:
	void Render(CView* pView);

public:
	int m_iObjID{ 0 };
	INFO m_tInfo{};
};

