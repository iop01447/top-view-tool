
// MFCToolView.h : CMFCToolView 클래스의 인터페이스
//

#pragma once

class CMFCToolDoc; 
class CTerrain; 
class CLine;
class CMapTool;
class CObj;
class CMFCToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// 특성입니다.
public:
	CMFCToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	CTerrain* m_pTerrain; // 저장
	float m_fAngle;
	int m_iColor;
	int m_iChangeSpeed;




	MAPTOOL::ID m_eToolID{ MAPTOOL::ID_END };
	CPoint m_tMouseOldPt;

	int m_iBackgroundID{ 0 }; // 저장
	TEXINFO* m_pBackgroundTex{ nullptr };

	CMapTool* m_pMapTool{ nullptr };

	list<CObj*> m_ObjList; // 저장



public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

public:
	void Draw_Background();
};

#ifndef _DEBUG  // MFCToolView.cpp의 디버그 버전
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

