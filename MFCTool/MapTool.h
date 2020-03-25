#pragma once
#include "afxwin.h"


// CMapTool ��ȭ �����Դϴ�.

class CTileTool;
class CObjectTool;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CTileTool* m_pTileTool;
	CObjectTool* m_pObjectTool;

public:
	CComboBox m_cbTest;

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedTileTool();
	afx_msg void OnBnClickedButtonObjectTool();

	afx_msg void OnCbnSelchangeComboTest();

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButtonLoad();
};
