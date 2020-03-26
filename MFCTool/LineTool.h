#pragma once


// CLineTool 대화 상자입니다.

class CLineTool : public CDialog
{
	DECLARE_DYNAMIC(CLineTool)

public:
	CLineTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLineTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGrid();

public:
	void ViewLButtonDown(UINT nFlags, CPoint point);
	void ViewMouseMove(UINT nFlags, CPoint point);
};
