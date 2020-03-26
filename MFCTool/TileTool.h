#pragma once


// CTileTool 대화 상자입니다.

class CTileTool : public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTileTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CListBox m_ListBox;
	CStatic m_Picture;
	DWORD m_dwDrawID;

public:
	void HorizontalScroll();

public:
	afx_msg void OnLbnSelchangeTileList();
	afx_msg void OnDropFiles(HDROP hDropInfo);

	void ViewLButtonDown(UINT nFlags, CPoint point);
	void ViewMouseMove(UINT nFlags, CPoint point);

	int m_iTileY;
	int m_iTileX;
	afx_msg void OnBnClickedTileCntChange();
};
