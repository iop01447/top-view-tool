// TileTool.cpp : ���� �����Դϴ�.
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


// CTileTool ��ȭ �����Դϴ�.

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
	DDX_Control(pDX, IDC_COMBO3, m_TileOptionList);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorButton);
	DDX_Control(pDX, IDC_CHECK2, m_CheckTileOption);
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileTool::OnLbnSelchangeTileList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CTileTool::OnBnClickedTileXYChange)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTileTool::OnCbnSelchangeTileOption)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CTileTool::OnBnClickedMfcColorButton)
	ON_BN_CLICKED(IDC_CHECK2, &CTileTool::OnBnClickedCheckTileOption)
END_MESSAGE_MAP()


// CTileTool �޽��� ó�����Դϴ�.


void CTileTool::OnLbnSelchangeTileList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strFindName = L""; 

	// GetCurSel - Ŀ���� �ε����� ��ȯ�� �ִ� �Լ�. 
	int iIndex = m_ListBox.GetCurSel(); 
	if (-1 == iIndex)
		return; 
	// GetText - �ε��� ��° �ִ� ���ڿ��� ������ �Լ�. 
	m_ListBox.GetText(iIndex, strFindName);

	int iSize = strFindName.GetLength(); 
	int i = 0; 
	for (; i < iSize; ++i)
	{
		// isdigit - 0~ 9������ �������� �˻����ִ� �Լ�. 
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE); 
	CDialog::OnDropFiles(hDropInfo);
	TCHAR szFilePath[MAX_STR] = L""; 
	//DragQueryFile - ����ü �ڵ� - �Լ��� ���ڷ� �޾ƿ��� �ֱ� ������ �ǵ� �ʿ� ����. 
	// 1. �ε����� �޴´�. �巡���ؼ� ��� �� �� ������ ���° ��������. 
	// �� ���ڸ� -1�� �ٰ�� ������ ��ü���� ������ ��ȯ���ش�. 
	// 2. �����̸� ���� ����, 
	// 3. ���ڿ��� ���� 
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
	D3DXVECTOR3 vMouse = { float(point.x - OFFSET + m_pView->GetScrollPos(0)), float(point.y - OFFSET + m_pView->GetScrollPos(1)), 0.f };

	m_pView->m_pTerrain->TileChange(vMouse, BYTE(m_dwDrawID), m_byOptionID);
}

void CTileTool::ViewMouseMove(UINT nFlags, CPoint point)
{
	D3DXVECTOR3 vMouse = { float(point.x - OFFSET + m_pView->GetScrollPos(0)), float(point.y - OFFSET + m_pView->GetScrollPos(1)), 0.f };

	if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState('Z'))
		m_pView->m_pTerrain->TileChange(vMouse, BYTE(m_dwDrawID), m_byOptionID);
}


void CTileTool::HorizontalScroll()
{
	CString strFileName; 
	CSize tSize; 
	int iCX = 0; 
	// ����Ʈ �ڽ��� �𾾱���̱⶧���� �ϴ� �� ����. 
	CDC* pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		// ����Ʈ�ڽ��� �ִ� ���ڿ��� ����°���� ���´�. 
		m_ListBox.GetText(i, strFileName); 
		// ���� ���ڿ� ���̸� �ȼ������� ��ȯ. ���ִ� �Լ� GetTextExtent
		tSize = pDC->GetTextExtent(strFileName); 
		if (tSize.cx > iCX)
			iCX = tSize.cx; 
	}

	m_ListBox.ReleaseDC(pDC); 
	//GetHorizontalExtent - ���� ��ũ�� ũ�⸦ ������ �Լ�. �ִ� ������ ����� �Լ� 
	if (iCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iCX);
}

void CTileTool::Init_TileList()
{
	CString tpath = _T("../Texture/Stage/Terrain/Tile2/*.*");

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
			m_ListBox.AddString(fileName);
			//�о�� ���� �̸��� ����Ʈ�ڽ��� ����
		}
	}
}



void CTileTool::OnBnClickedTileXYChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_pView->m_pTerrain->ChangeTileXY(m_iTileX, m_iTileY);
	m_pView->SetScrollSizes(MM_TEXT,
		CSize(m_iTileX * TILECX + OFFSET * 2, m_iTileY * TILECY + OFFSET * 2));
}


BOOL CTileTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	m_pView = dynamic_cast<CMFCToolView*>(pMainFrm->m_MainSplitterWnd.GetPane(0, 1));

	for (int i = 0; i < E_TILE::OPTION_END; ++i) {
		m_mapTileOptionColor.emplace(i, D3DCOLORVALUE{ 0, 0, 0, 0 });
	}

	for (int i = 0; i < E_TILE::OPTION_END; ++i) {
		m_TileOptionList.InsertString(i, E_TILE::str[i].c_str());
	}

	m_TileOptionList.SetCurSel(0);

	Init_TileList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTileTool::OnCbnSelchangeTileOption()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int index = m_TileOptionList.GetCurSel();
	D3DCOLORVALUE color = m_mapTileOptionColor[index];
	m_ColorButton.SetColor(RGB(color.r, color.g, color.b));
	m_byOptionID = index;
}

void CTileTool::OnBnClickedMfcColorButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	int index = m_TileOptionList.GetCurSel();
	COLORREF color = m_ColorButton.GetColor();
	m_mapTileOptionColor[index].r = (color & RGB(255, 0, 0));
	m_mapTileOptionColor[index].g = (color & RGB(0, 255, 0)) >> 8;
	m_mapTileOptionColor[index].b = (color & RGB(0, 0, 255)) >> 16;
}


void CTileTool::OnBnClickedCheckTileOption()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_pView->m_pTerrain->m_bDrawOption = m_CheckTileOption.GetCheck();
}
