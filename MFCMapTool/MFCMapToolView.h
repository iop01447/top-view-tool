
// MFCMapToolView.h : CMFCMapToolView Ŭ������ �������̽�
//

#pragma once


class CMFCMapToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCMapToolView();
	DECLARE_DYNCREATE(CMFCMapToolView)

// Ư���Դϴ�.
public:
	CMFCMapToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFCMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCMapToolView.cpp�� ����� ����
inline CMFCMapToolDoc* CMFCMapToolView::GetDocument() const
   { return reinterpret_cast<CMFCMapToolDoc*>(m_pDocument); }
#endif

