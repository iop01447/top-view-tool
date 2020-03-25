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

// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	//	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_COMBO_TEST, m_cbTest);

	m_cbTest.InsertString(0, L"1��°");
	m_cbTest.InsertString(1, L"2��°");
	m_cbTest.InsertString(2, L"3��°");

	m_cbTest.SetCurSel(0);
	DDX_Control(pDX, IDC_COMBO_BACK_GRUND, m_Backgrundlist);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangeListBox)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSave)
	ON_CBN_SELCHANGE(IDC_COMBO_TEST, &CMapTool::OnCbnSelchangeComboTest)
	ON_CBN_SELCHANGE(IDC_COMBO_BACK_GRUND, &CMapTool::OnCbnSelchangeComboSelectField)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.



void CMapTool::OnLbnSelchangeListBox()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//UpdateData(TRUE);
	//CString strFindName = L""; 

	//// GetCurSel - Ŀ���� �ε����� ��ȯ�� �ִ� �Լ�. 
	//int iIndex = m_ListBox.GetCurSel(); 
	//if (-1 == iIndex)
	//	return; 
	//// GetText - �ε��� ��° �ִ� ���ڿ��� ������ �Լ�. 
	//m_ListBox.GetText(iIndex, strFindName);

	//int iSize = strFindName.GetLength(); 
	//int i = 0; 
	//for (; i < iSize; ++i)
	//{
	//	// isdigit - 0~ 9������ �������� �˻����ִ� �Լ�. 
	//	if(isdigit(strFindName[i]))
	//		break;
	//}
	//// 01
	//strFindName.Delete(0, i);
	//m_dwDrawID = _ttoi(strFindName.GetString()); 

	//GET_INSTANCE(CDevice)->Render_Begin();
	//D3DXMATRIX matScale, matTrans, matWorld; 
	//const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Terrain", L"Tile", m_dwDrawID); 
	//assert(!(nullptr == pTexInfo));
	//float fX = WINCX / float(TILECX); 
	//float fY = WINCY / float(TILECY); 
	//D3DXMatrixScaling(&matScale, fX, fY, 0.f);
	//D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f); 
	//matWorld = matScale * matTrans; 

	//GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld); 
	//GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 


	//GET_INSTANCE(CDevice)->Render_End(m_Picture.m_hWnd); 

	//UpdateData(FALSE); 

}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	//// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//UpdateData(TRUE); 
	//CDialog::OnDropFiles(hDropInfo);
	//TCHAR szFilePath[MAX_STR] = L""; 
	////DragQueryFile - ����ü �ڵ� - �Լ��� ���ڷ� �޾ƿ��� �ֱ� ������ �ǵ� �ʿ� ����. 
	//// 1. �ε����� �޴´�. �巡���ؼ� ��� �� �� ������ ���° ��������. 
	//// �� ���ڸ� -1�� �ٰ�� ������ ��ü���� ������ ��ȯ���ش�. 
	//// 2. �����̸� ���� ����, 
	//// 3. ���ڿ��� ���� 
	//int iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);
	//TCHAR szFileName[MIN_STR] = L""; 

	//for (int i = 0 ; i < iFileCnt ; ++i)
	//{
	//	DragQueryFile(hDropInfo, i, szFilePath, MAX_STR);
	//	CString strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);
	//	CString strFileNameAndExtension = PathFindFileName(strRelativePath);
	//	lstrcpy(szFileName, strFileNameAndExtension.GetString()); 
	//	PathRemoveExtension(szFileName); 
	//	m_ListBox.AddString(szFileName);
	//}
	//HorizontalScroll();
	//UpdateData(FALSE); 
}



void CMapTool::HorizontalScroll()
{
	//CString strFileName; 
	//CSize tSize; 
	//int iCX = 0; 
	//// ����Ʈ �ڽ��� �𾾱���̱⶧���� �ϴ� �� ����. 
	//CDC* pDC = m_ListBox.GetDC();

	//for (int i = 0; i < m_ListBox.GetCount(); ++i)
	//{
	//	// ����Ʈ�ڽ��� �ִ� ���ڿ��� ����°���� ���´�. 
	//	m_ListBox.GetText(i, strFileName); 
	//	// ���� ���ڿ� ���̸� �ȼ������� ��ȯ. ���ִ� �Լ� GetTextExtent
	//	tSize = pDC->GetTextExtent(strFileName); 
	//	if (tSize.cx > iCX)
	//		iCX = tSize.cx; 
	//}

	//m_ListBox.ReleaseDC(pDC); 
	////GetHorizontalExtent - ���� ��ũ�� ũ�⸦ ������ �Լ�. �ִ� ������ ����� �Լ� 
	//if (iCX > m_ListBox.GetHorizontalExtent())
	//	m_ListBox.SetHorizontalExtent(iCX);


}


void CMapTool::OnBnClickedSave()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile|*.dat||", this);
	//TCHAR szPath[MAX_STR] = L"";
	//GetCurrentDirectory(MAX_STR, szPath);

	//PathRemoveFileSpec(szPath);
	//lstrcat(szPath, L"\\Data");
	//Dlg.m_ofn.lpstrInitialDir = szPath;

	//if (IDOK == Dlg.DoModal())
	//{
	//	CString strPath = Dlg.GetPathName();

	//	HANDLE hFile = CreateFile(strPath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	//	if (INVALID_HANDLE_VALUE == hFile)
	//		return;

	//	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	//	vector<TILE*>& rvecTerrain = pView->m_pTerrain->Get_Tile();

	//	DWORD dwByte = 0;
	//	for (auto& pTile : rvecTerrain)
	//		WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

	//	CloseHandle(hFile);
	//}
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


void CMapTool::OnCbnSelchangeComboSelectField()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex;
	iIndex = m_Backgrundlist.GetCurSel();
}
