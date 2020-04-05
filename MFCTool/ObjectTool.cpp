// ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Obj.h"


// CObjectTool 대화 상자입니다.

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


// CObjectTool 메시지 처리기입니다.


void CObjectTool::OnLbnSelchangeObjectList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	CString strFindName = L"";

	// GetCurSel - 커서의 인덱스를 반환해 주는 함수. 
	m_iObjectID = m_ObjectList.GetCurSel();
	if (-1 == m_iObjectID)
		return;
	//// GetText - 인덱스 번째 있는 문자열을 얻어오는 함수. 
	//m_ObjectList.GetText(iIndex, strFindName);

	//int iSize = strFindName.GetLength();
	//int i = 0;
	//for (; i < iSize; ++i)
	//{
	//	// isdigit - 0~ 9까지의 숫자인지 검사해주는 함수. 
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Init_ObjectList();

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CObjectTool::Init_ObjectList()
{
	//CString tpath = _T("../Texture/Stage/Object/*.*");

	////검색 클래스
	//CFileFind finder;

	////CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
	//BOOL bWorking = finder.FindFile(tpath); //

	//CString fileName;
	//CString DirName;

	//while (bWorking)
	//{
	//	//다음 파일 / 폴더 가 존재하면다면 TRUE 반환
	//	bWorking = finder.FindNextFile();
	//	//파일 일때
	//	if (finder.IsArchived())
	//	{
	//		//파일의 이름
	//		CString _fileName = finder.GetFileName();

	//		// 현재폴더 상위폴더 썸네일파일은 제외
	//		if (_fileName == _T(".") ||
	//			_fileName == _T("..") ||
	//			_fileName == _T("Thumbs.db")) continue;

	//		fileName = finder.GetFileTitle();
	//		m_ObjectList.AddString(fileName);
	//		//읽어온 파일 이름을 리스트박스에 넣음
	//	}
	//}

	m_ObjectList.AddString(L"닭");
	m_ObjectList.AddString(L"슬라임");
	m_ObjectList.AddString(L"킹슬라임");
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
