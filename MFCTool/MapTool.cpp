// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapTool.h"
#include "FileInfo.h"
#include <assert.h>
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Terrain.h"
#include "TileTool.h"
#include "ObjectTool.h"

// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
	Safe_Delete(m_TileTool);
	Safe_Delete(m_ObjectTool);
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TEST, m_cbTest);

	m_cbTest.InsertString(0, L"1��°");
	m_cbTest.InsertString(1, L"2��°");
	m_cbTest.InsertString(2, L"3��°");

	m_cbTest.SetCurSel(0);
	DDX_Control(pDX, IDC_COMBO_BACK_GRUND, m_Backgrundlist);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSave)
	ON_CBN_SELCHANGE(IDC_COMBO_TEST, &CMapTool::OnCbnSelchangeComboTest)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedTileTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMapTool::OnBnClickedButtonObjectTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedButtonLoad)
	ON_CBN_SELCHANGE(IDC_COMBO_BACK_GRUND, &CMapTool::OnCbnSelchangeComboSelectField)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.

void CMapTool::OnBnClickedSave()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile|*.dat||", this);
	TCHAR szPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szPath);

	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString strPath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(strPath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
		vector<TILE*>& rvecTerrain = pView->m_pTerrain->Get_Tile();

		DWORD dwByte = 0;
		for (auto& pTile : rvecTerrain)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
	}
}


void CMapTool::OnCbnSelchangeComboTest()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//int iIndex;
	//iIndex = m_cbTest.GetCurSel();

	//if (CB_ERR != iIndex)
	//{
	//	CString sName;
	//	m_cbTest.GetLBText(iIndex, sName);
	//	SetDlgItemText(IDC_COMBO_TEST, sName);

	//	if (sName == L"1��°")
	//	{
	//		//���ϴ� ���1
	//	}
	//	else if (sName == L"2��°")
	//	{
	//		//2
	//	}
	//	else
	//	{
	//		//3
	//	}
	//}


}


BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_TileTool = new CTileTool;
	m_ObjectTool = new CObjectTool;

	if (m_TileTool->GetSafeHwnd() == nullptr)
		m_TileTool->Create(IDD_TILETOOL);
	if (m_ObjectTool->GetSafeHwnd() == nullptr)
		m_ObjectTool->Create(IDD_OBJECTTOOL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::OnBnClickedTileTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_TileTool->ShowWindow(SW_SHOW);
}


void CMapTool::OnBnClickedButtonObjectTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ObjectTool->ShowWindow(SW_SHOW);
}


void CMapTool::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapTool::OnCbnSelchangeComboSelectField()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex;
	iIndex = m_Backgrundlist.GetCurSel();
}
