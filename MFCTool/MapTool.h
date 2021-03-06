#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.

class CTerrain;
class CTileTool;
class CObjectTool;
class CLineTool;

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CTileTool* m_pTileTool;
	CObjectTool* m_pObjectTool;
	CLineTool* m_pLineTool;

public:
	CComboBox m_LayerList;
	CComboBox m_Backgrundlist;

	CTerrain* m_pTerrainArr[LAYER::ID_END];

public:
	void Init_Terrain();
	void Init_Background();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedTileTool();
	afx_msg void OnBnClickedButtonObjectTool();

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	
	afx_msg void OnCbnLayerSelchange();
	afx_msg void OnCbnBackgroundSelchange();

	afx_msg void OnBnClickedLineTool();
};
