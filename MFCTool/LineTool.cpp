// LineTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "LineTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
// CLineTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLineTool, CDialog)

CLineTool::CLineTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LINETOOL, pParent)
{

}

CLineTool::~CLineTool()
{
}

void CLineTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLineTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CLineTool::OnBnClickedGrid)
END_MESSAGE_MAP()


// CLineTool �޽��� ó�����Դϴ�.


void CLineTool::OnBnClickedGrid()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));

	bGrid = GET_INSTANCE(CDevice)->Get_GridChack();

	if (!bGrid)
	{
		GET_INSTANCE(CDevice)->Set_GridChack(TRUE);
	}
	else
	{
		GET_INSTANCE(CDevice)->Set_GridChack(FALSE);
	}


}

void CLineTool::ViewLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));
	D3DXVECTOR2 vMouse = { float(point.x - OFFSET + pView->GetScrollPos(0)), float(point.y - OFFSET + pView->GetScrollPos(1))};

	GET_INSTANCE(CDevice)->Line_Set(vMouse);
}

void CLineTool::ViewMouseMove(UINT nFlags, CPoint point)
{
}
