// LineTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "LineTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Device.h"
#include "Terrain.h"
// CLineTool 대화 상자입니다.

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


// CLineTool 메시지 처리기입니다.


void CLineTool::OnBnClickedGrid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));

	bGrid = GET_INSTANCE(CDevice)->Get_GridChack();
	CDevice::Get_Instance()->GridSet(pView->m_pTerrain->m_iTileX, pView->m_pTerrain->m_iTileY);

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
