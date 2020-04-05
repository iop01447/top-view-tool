#pragma once
#include "afxwin.h"


// CObjectTool 대화 상자입니다.

class CMFCToolView;
class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void ViewLButtonDown(UINT nFlags, CPoint point);
	void ViewMouseMove(UINT nFlags, CPoint point);

	CListBox m_ObjectList;
	CStatic m_ObjectPicture;
	
	afx_msg void OnLbnSelchangeObjectList();
	virtual BOOL OnInitDialog();

	void Init_ObjectList();

	int m_iObjectID{ 0 };
	CMFCToolView* m_pView{ nullptr };

	void DrawView();

	CPoint m_MousePt;
};
