// TileTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "TileTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "MyForm.h"
#include "Terrain.h"
#include "MFCToolView.h"


// CTileTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTileTool, CDialog)

CTileTool::CTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent)
	, m_iTileY(false)
	, m_iTileX(0)
{

}

CTileTool::~CTileTool()
{
}

void CTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT3, m_iTileY);
	DDX_Text(pDX, IDC_EDIT4, m_iTileX);
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileTool::OnLbnSelchangeTileList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CTileTool::OnBnClickedTileCntChange)
END_MESSAGE_MAP()


// CTileTool 메시지 처리기입니다.


void CTileTool::OnLbnSelchangeTileList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strFindName = L""; 

	// GetCurSel - 커서의 인덱스를 반환해 주는 함수. 
	int iIndex = m_ListBox.GetCurSel(); 
	if (-1 == iIndex)
		return; 
	// GetText - 인덱스 번째 있는 문자열을 얻어오는 함수. 
	m_ListBox.GetText(iIndex, strFindName);

	int iSize = strFindName.GetLength(); 
	int i = 0; 
	for (; i < iSize; ++i)
	{
		// isdigit - 0~ 9까지의 숫자인지 검사해주는 함수. 
		if(isdigit(strFindName[i]))
			break;
	}
	// 01
	strFindName.Delete(0, i);
	m_dwDrawID = _ttoi(strFindName.GetString()); 

	GET_INSTANCE(CDevice)->Render_Begin();
	D3DXMATRIX matScale, matTrans, matWorld; 
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile", m_dwDrawID); 
	assert(!(nullptr == pTexInfo));
	float fX = WINCX / float(TILECX); 
	float fY = WINCY / float(TILECY); 
	D3DXMatrixScaling(&matScale, fX, fY, 0.f);
	D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f); 
	matWorld = matScale * matTrans; 

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld); 
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 


	GET_INSTANCE(CDevice)->Render_End(m_Picture.m_hWnd); 

	UpdateData(FALSE); 
}


void CTileTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE); 
	CDialog::OnDropFiles(hDropInfo);
	TCHAR szFilePath[MAX_STR] = L""; 
	//DragQueryFile - 구조체 핸들 - 함수의 인자로 받아오고 있기 때문에 건들 필요 없음. 
	// 1. 인덱스를 받는다. 드래그해서 드롭 할 때 폴더에 몇번째 파일인지. 
	// 이 인자를 -1로 줄경우 파일의 전체적인 갯수를 반환해준다. 
	// 2. 파일이름 넣을 공간, 
	// 3. 문자열의 길이 
	int iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);
	TCHAR szFileName[MIN_STR] = L""; 

	for (int i = 0 ; i < iFileCnt ; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_STR);
		CString strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);
		CString strFileNameAndExtension = PathFindFileName(strRelativePath);
		lstrcpy(szFileName, strFileNameAndExtension.GetString()); 
		PathRemoveExtension(szFileName); 
		m_ListBox.AddString(szFileName);
	}
	HorizontalScroll();
	UpdateData(FALSE); 
}

void CTileTool::ViewLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitterWnd.GetPane(1, 0));
	CTileTool* pTileTool = pMyForm->m_MapTool.m_pTileTool;
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMainFrm->m_MainSplitterWnd.GetPane(0, 1));

	D3DXVECTOR3 vMouse = { float(point.x + pView->GetScrollPos(0)), float(point.y + pView->GetScrollPos(1)), 0.f };
	pView->m_pTerrain->TileChange(vMouse, BYTE(pTileTool->m_dwDrawID));
}

void CTileTool::ViewMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMainFrm->m_MainSplitterWnd.GetPane(0, 1));
	D3DXVECTOR3 vMouse = { float(point.x + pView->GetScrollPos(0)), float(point.y + pView->GetScrollPos(1)), 0.f };
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitterWnd.GetPane(1, 0));
	CTileTool* pTileTool = pMyForm->m_MapTool.m_pTileTool;

	if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState('Z'))
		pView->m_pTerrain->TileChange(vMouse, BYTE(pTileTool->m_dwDrawID));
}


void CTileTool::HorizontalScroll()
{
	CString strFileName; 
	CSize tSize; 
	int iCX = 0; 
	// 리스트 박스도 디씨기반이기때문에 일단 디씨 얻어옴. 
	CDC* pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		// 리스트박스에 있는 문자열을 영번째부터 얻어온다. 
		m_ListBox.GetText(i, strFileName); 
		// 얻어옷 문자열 길이를 픽셀단위로 변환. 해주는 함수 GetTextExtent
		tSize = pDC->GetTextExtent(strFileName); 
		if (tSize.cx > iCX)
			iCX = tSize.cx; 
	}

	m_ListBox.ReleaseDC(pDC); 
	//GetHorizontalExtent - 가로 스크롤 크기를 얻어오는 함수. 최대 범위를 얻오은 함수 
	if (iCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iCX);
}



void CTileTool::OnBnClickedTileCntChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	/* // 잘 되는지 테스트 
	int tmp = m_iTileX;
	m_iTileX = m_iTileY;
	m_iTileY = tmp;
	UpdateData(FALSE); */
}
