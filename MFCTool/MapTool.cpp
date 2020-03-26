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
#include "LineTool.h"

// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{
}

CMapTool::~CMapTool()
{
	Safe_Delete(m_pTileTool);
	Safe_Delete(m_pObjectTool);

	for(int i=0; i<MAPTOOL::ID_END; ++i)
		Safe_Delete(m_pTerrainArr[i]);
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TEST, m_LayerList);

	for (int i = 0; i < LAYER::ID_END; ++i) {
		m_LayerList.InsertString(i, LAYER::str[i].c_str());
	}

	m_LayerList.SetCurSel(0);
	DDX_Control(pDX, IDC_COMBO_BACK_GRUND, m_Backgrundlist);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSave)
	ON_CBN_SELCHANGE(IDC_COMBO_TEST, &CMapTool::OnCbnLayerSelchange)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedTileTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMapTool::OnBnClickedButtonObjectTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedLoad)
	ON_CBN_SELCHANGE(IDC_COMBO_BACK_GRUND, &CMapTool::OnCbnBackgroundSelchange)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnBnClickedLineTool)
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

	if (IDOK != Dlg.DoModal()) return;
	
	CString strPath = Dlg.GetPathName();

	HANDLE hFile = CreateFile(strPath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	
	for (int i = 0; i < LAYER::ID_END; ++i) {
		vector<TILE*>& rvecTerrain = m_pTerrainArr[i]->Get_Tile();

		DWORD dwByte = 0;
		for (auto& pTile : rvecTerrain)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	
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


void CMapTool::Init_Terrain()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));

	// ���⼭ �ϸ� �ؽ��İ� �ȵ�����. ����̽� Init�� ���ؼ�..
	//GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Cube.png", L"Cube");
	//GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Stage/Terrain/Tile2/Tile%d.png", L"Terrain", L"Tile", 9);

	for (int i = 0; i < MAPTOOL::ID_END; ++i) {
		if (nullptr == m_pTerrainArr[i])
		{
			m_pTerrainArr[i] = new CTerrain;
			if (FAILED(m_pTerrainArr[i]->Initialize(TILEX, TILEY, 0, E_TILE::OPTION_END)))
				AfxMessageBox(L"Terrain Initialize Failed");
			m_pTerrainArr[i]->Set_View(pView);
		}
	}
	pView->m_pTerrain = m_pTerrainArr[0];
}

void CMapTool::Init_Background()
{
	CString tpath = _T("../Texture/Stage/Background/*.*");

	//�˻� Ŭ����
	CFileFind finder;

	//CFileFind�� ����, ���͸��� �����ϸ� TRUE �� ��ȯ��
	BOOL bWorking = finder.FindFile(tpath); //

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//���� ���� / ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();
		//���� �϶�
		if (finder.IsArchived())
		{
			//������ �̸�
			CString _fileName = finder.GetFileName();

			// �������� �������� ����������� ����
			if (_fileName == _T(".") ||
				_fileName == _T("..") ||
				_fileName == _T("Thumbs.db")) continue;

			fileName = finder.GetFileTitle();
			m_Backgrundlist.AddString(fileName);
			//�о�� ���� �̸��� ����Ʈ�ڽ��� ����
		}
	}

	m_Backgrundlist.SetCurSel(0);
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_pTileTool = new CTileTool;
	m_pObjectTool = new CObjectTool;
	m_pLineTool = new CLineTool;
	if (m_pTileTool->GetSafeHwnd() == nullptr)
		m_pTileTool->Create(IDD_TILETOOL);
	if (m_pObjectTool->GetSafeHwnd() == nullptr)
		m_pObjectTool->Create(IDD_OBJECTTOOL);

	Init_Terrain();
	Init_Background();

	if (m_pLineTool->GetSafeHwnd() == nullptr)
		m_pLineTool->Create(IDD_LINETOOL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::OnBnClickedTileTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pTileTool->ShowWindow(SW_SHOW);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_eToolID = MAPTOOL::TILE;
}


void CMapTool::OnBnClickedButtonObjectTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pObjectTool->ShowWindow(SW_SHOW);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_eToolID = MAPTOOL::OBJECT;
}

void CMapTool::OnBnClickedLineTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pLineTool->ShowWindow(SW_SHOW);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_eToolID = MAPTOOL::LINE;
}
void CMapTool::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapTool::OnCbnLayerSelchange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int index = m_LayerList.GetCurSel();
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_pTerrain = m_pTerrainArr[index];

	pView->SetScrollSizes(MM_TEXT, 
		CSize(m_pTerrainArr[index]->m_iTileX * TILECX + OFFSET * 2,
			m_pTerrainArr[index]->m_iTileY * TILECY + OFFSET * 2));

}

void CMapTool::OnCbnBackgroundSelchange()
{
	int index = m_Backgrundlist.GetCurSel();
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_pBackgroundTex = CTextureMgr::Get_Instance()->Get_TexInfo(L"Background", L"Background", index);

}


