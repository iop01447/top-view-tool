#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"


// CTileTool 대화 상자입니다.

class CMFCToolView;
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
	BYTE m_byOptionID{ 0 };
	CMFCToolView* m_pView;

public:
	void HorizontalScroll();
	
	void Init_TileList();

public:
	afx_msg void OnLbnSelchangeTileList();
	afx_msg void OnDropFiles(HDROP hDropInfo);

	void ViewLButtonDown(UINT nFlags, CPoint point);
	void ViewMouseMove(UINT nFlags, CPoint point);

	int m_iTileY;
	int m_iTileX;
	afx_msg void OnBnClickedTileXYChange();

	virtual BOOL OnInitDialog();

	CComboBox m_TileOptionList;
	map<int, D3DCOLORVALUE> m_mapTileOptionColor;

	CMFCColorButton m_ColorButton;
	afx_msg void OnCbnSelchangeTileOption();

	afx_msg void OnBnClickedMfcColorButton();

	CButton m_CheckTileOption;
	afx_msg void OnBnClickedCheckTileOption();
};
