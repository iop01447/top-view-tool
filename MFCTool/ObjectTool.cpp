// ObjectTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Obj.h"


// CObjectTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)

CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
{

}

CObjectTool::~CObjectTool()
{
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ObjectList);
	DDX_Control(pDX, IDC_PICTURE0, m_ObjectPicture);
}

void CObjectTool::ViewLButtonDown(UINT nFlags, CPoint point)
{
	D3DXVECTOR3 vMouse = { float(point.x - OFFSET + m_pView->GetScrollPos(0)), float(point.y - OFFSET + m_pView->GetScrollPos(1)), 0.f };

	list<CObj*>& list = m_pView->m_ObjList;
	for (auto iter = list.begin(); iter != list.end();) {
		if ((*iter)->Check_MousePt(vMouse)) {
			iter = list.erase(iter);
			return;
		}
		else
			++iter;
	}

	CObj* obj = new CObj;

	obj->Initialize(m_iObjectID, vMouse);
	m_pView->m_ObjList.push_back(obj);
}

void CObjectTool::ViewMouseMove(UINT nFlags, CPoint point)
{
	m_MousePt = point;
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectTool::OnLbnSelchangeObjectList)
END_MESSAGE_MAP()


// CObjectTool �޽��� ó�����Դϴ�.


void CObjectTool::OnLbnSelchangeObjectList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	CString strFindName = L"";

	// GetCurSel - Ŀ���� �ε����� ��ȯ�� �ִ� �Լ�. 
	m_iObjectID = m_ObjectList.GetCurSel();
	if (-1 == m_iObjectID)
		return;
	//// GetText - �ε��� ��° �ִ� ���ڿ��� ������ �Լ�. 
	//m_ObjectList.GetText(iIndex, strFindName);

	//int iSize = strFindName.GetLength();
	//int i = 0;
	//for (; i < iSize; ++i)
	//{
	//	// isdigit - 0~ 9������ �������� �˻����ִ� �Լ�. 
	//	if (isdigit(strFindName[i]))
	//		break;
	//}
	//// 01
	//strFindName.Delete(0, i);
	//int iObjectID = _ttoi(strFindName.GetString());

	GET_INSTANCE(CDevice)->Render_Begin();
	D3DXMATRIX matScale, matTrans, matWorld;
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Object", L"Object", m_iObjectID);
	assert(!(nullptr == pTexInfo));

	D3DXVECTOR3 vCenter;
	vCenter.x = pTexInfo->tImageInfo.Width / 2.f;
	vCenter.y = pTexInfo->tImageInfo.Height / 2.f;

	float fX = WINCX / float(pTexInfo->tImageInfo.Width);
	float fY = WINCY / float(pTexInfo->tImageInfo.Height);
	float fScale = min(fX, fY);
	D3DXMatrixScaling(&matScale, fScale, fScale, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX/2, WINCY/2, 0.f);
	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr,
		&vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	GET_INSTANCE(CDevice)->Render_End(m_ObjectPicture.m_hWnd);

	UpdateData(FALSE);
}


BOOL CObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	Init_ObjectList();

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CObjectTool::Init_ObjectList()
{
	//CString tpath = _T("../Texture/Stage/Object/*.*");

	////�˻� Ŭ����
	//CFileFind finder;

	////CFileFind�� ����, ���͸��� �����ϸ� TRUE �� ��ȯ��
	//BOOL bWorking = finder.FindFile(tpath); //

	//CString fileName;
	//CString DirName;

	//while (bWorking)
	//{
	//	//���� ���� / ���� �� �����ϸ�ٸ� TRUE ��ȯ
	//	bWorking = finder.FindNextFile();
	//	//���� �϶�
	//	if (finder.IsArchived())
	//	{
	//		//������ �̸�
	//		CString _fileName = finder.GetFileName();

	//		// �������� �������� ����������� ����
	//		if (_fileName == _T(".") ||
	//			_fileName == _T("..") ||
	//			_fileName == _T("Thumbs.db")) continue;

	//		fileName = finder.GetFileTitle();
	//		m_ObjectList.AddString(fileName);
	//		//�о�� ���� �̸��� ����Ʈ�ڽ��� ����
	//	}
	//}

	m_ObjectList.AddString(L"��");
	m_ObjectList.AddString(L"������");
	m_ObjectList.AddString(L"ŷ������");
}

void CObjectTool::DrawView()
{
	const TEXINFO* pTexInfo = GET_INSTANCE(CTextureMgr)->Get_TexInfo(L"Object", L"Object", m_iObjectID);
	assert(!(nullptr == pTexInfo));

	D3DXVECTOR3 vCenter;
	vCenter.x = pTexInfo->tImageInfo.Width / 2.f;
	vCenter.y = pTexInfo->tImageInfo.Height / 2.f;

	D3DXMATRIX matScale, matTrans, matWorld;
	float fX = WINCX / float(pTexInfo->tImageInfo.Width);
	float fY = WINCY / float(pTexInfo->tImageInfo.Height);

	D3DXMatrixScaling(&matScale, 1, 1, 0.f);
	D3DXMatrixTranslation(&matTrans, m_MousePt.x, m_MousePt.y, 0.f);
	matWorld = matScale * matTrans;

	GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
	GET_INSTANCE(CDevice)->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr,
		&vCenter, nullptr, D3DCOLOR_ARGB(125, 255, 255, 255));
}
