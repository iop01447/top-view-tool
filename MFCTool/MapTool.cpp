// MapTool.cpp : 구현 파일입니다.
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

// CMapTool 대화 상자입니다.

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


// CMapTool 메시지 처리기입니다.

void CMapTool::OnBnClickedSave()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//int iIndex;
	//iIndex = m_cbTest.GetCurSel();

	//if (CB_ERR != iIndex)
	//{
	//	CString sName;
	//	m_cbTest.GetLBText(iIndex, sName);
	//	SetDlgItemText(IDC_COMBO_TEST, sName);

	//	if (sName == L"1번째")
	//	{
	//		//원하는 명령1
	//	}
	//	else if (sName == L"2번째")
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

	// 여기서 하면 텍스쳐가 안들어가진다. 디바이스 Init을 안해서..
	//GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Cube.png", L"Cube");
	//GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Stage/Terrain/Tile2/Tile%d.png", L"Terrain", L"Tile", 9);

	for (int i = 0; i < MAPTOOL::ID_END; ++i) {
		if (nullptr == m_pTerrainArr[i])
		{
			m_pTerrainArr[i] = new CTerrain;
			if (FAILED(m_pTerrainArr[i]->Initialize((i+1) * TILEX, (i + 1) * TILEY, i, E_TILE::OPTION_END)))
				AfxMessageBox(L"Terrain Initialize Failed");
			m_pTerrainArr[i]->Set_View(pView);
		}
	}
	pView->m_pTerrain = m_pTerrainArr[0];
}

void CMapTool::Init_Background()
{
	CString tpath = _T("../Texture/Stage/Background/*.*");

	//검색 클래스
	CFileFind finder;

	//CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
	BOOL bWorking = finder.FindFile(tpath); //

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//다음 파일 / 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();
		//파일 일때
		if (finder.IsArchived())
		{
			//파일의 이름
			CString _fileName = finder.GetFileName();

			// 현재폴더 상위폴더 썸네일파일은 제외
			if (_fileName == _T(".") ||
				_fileName == _T("..") ||
				_fileName == _T("Thumbs.db")) continue;

			fileName = finder.GetFileTitle();
			m_Backgrundlist.AddString(fileName);
			//읽어온 파일 이름을 리스트박스에 넣음
		}
	}

	m_Backgrundlist.SetCurSel(0);
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapTool::OnBnClickedTileTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pTileTool->ShowWindow(SW_SHOW);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_eToolID = MAPTOOL::TILE;
}


void CMapTool::OnBnClickedButtonObjectTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pObjectTool->ShowWindow(SW_SHOW);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_eToolID = MAPTOOL::OBJECT;
}

void CMapTool::OnBnClickedLineTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pLineTool->ShowWindow(SW_SHOW);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_eToolID = MAPTOOL::LINE;
}
void CMapTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapTool::OnCbnLayerSelchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int index = m_LayerList.GetCurSel();
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	pView->m_pTerrain = m_pTerrainArr[index];

	pView->SetScrollSizes(MM_TEXT, 
		CSize(m_pTerrainArr[index]->m_iTileX * TILECX,
			m_pTerrainArr[index]->m_iTileY * TILECY));

}

void CMapTool::OnCbnBackgroundSelchange()
{
}


