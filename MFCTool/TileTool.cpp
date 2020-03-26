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
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileTool::OnLbnSelchangeTileList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CTileTool::OnBnClickedTileXYChange)
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

	m_pView->m_pTerrain->TileChange(vMouse, BYTE(m_dwDrawID));
}

void CTileTool::ViewMouseMove(UINT nFlags, CPoint point)
{
	D3DXVECTOR3 vMouse = { float(point.x - OFFSET + m_pView->GetScrollPos(0)), float(point.y - OFFSET + m_pView->GetScrollPos(1)), 0.f };

	if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState('Z'))
		m_pView->m_pTerrain->TileChange(vMouse, BYTE(m_dwDrawID));
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
