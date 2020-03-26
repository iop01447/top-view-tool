#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"


// CTileTool ��ȭ �����Դϴ�.

class CMFCToolView;
class CTileTool : public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTileTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
