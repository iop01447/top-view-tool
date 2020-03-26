
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "SingleTex.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "MyForm.h"
#include "TileTool.h"
#include "ObjectTool.h"
#include "LineTool.h"
#include "Line.h"
HWND g_hWND; 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_fAngle = 0.f;
	m_iChangeSpeed = 1;
	m_iColor = 0; 

}

CMFCToolView::~CMFCToolView()
{
	GET_INSTANCE(CTextureMgr)->Destroy_Instance();
	CDevice::Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

// �ݹ� �������� �Լ��� ȣ�� �ȴ�. 
//OnDraw��� �Լ��� WM_PAINT ��� �޽����� �߻������� ȣ��Ǵ� �Լ�. 
void CMFCToolView::OnDraw(CDC* pDC)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	GET_INSTANCE(CDevice)->Render_Begin(); 

	Draw_Background();

	if(m_pTerrain) m_pTerrain->Render();


	
	GET_INSTANCE(CDevice)->Render_End(); 

}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����

// ������ ȣ�� ���� ó�� ȣ��Ǵ� �Լ�. 
void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetTimer(0, 0, nullptr); 
	// SetScrollSizes ��ũ�� �����ϴ� �Լ� - 1.��ũ�� ������ �����ϴ� ����. MM_TEXT�ȼ������� ����ϰڴ�. 
	//2. ��ũ�� ��ü ũ��.  .
	SetScrollSizes(MM_TEXT, CSize(TILEX * TILECX + OFFSET * 2, TILEY * TILECY + OFFSET * 2));

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	/*
	���� ���� �ϰ��� �ϴ� ��. 
	MainFrame�� ũ�⸦ �����Ͽ� ��ü���� ���������� â ũ�⸦ ���� �ϴ� ��. 
	�ܼ� MainFrame�� ũ�⸦ WINCX, WINCY�� ���߰ԵǸ� �츮�� ���� �����ִ� view(Client)�� ũ��� WINCX, WINCY���� �۰� ���´�. �� ?
	�µθ� ũ����� WINCX, WINCY ���ԵǱ� ������. 

	*/
	// ���⼭ ���� MainFrame�� ũ�⸦ ������ �� ����. 
	//AfxGetApp - MainApp�� �����͸� ������ �Լ�. 
	// GetMainWnd - ���� ������ ������ ����Ʈ�� ������ �Լ�. 
	
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMain = {}; 
	// ���� ���� �������� ũ�⸦ ���´�. 
	// ���� �� ���� ��ũ�� ��ǥ ����. 
	// ex) 200, 200 ��ġ���� �����̵Ǹ� left, top �� 200, 200 �� �ȴٴ� �Ҹ�. 
	pMainFrame->GetWindowRect(&rcMain);
	// view�� ũ�⸦ ���� �ǵ� view�� ũ��� Ŭ���̾�Ʈ ��ǥ�� ����. �׷��� �ΰ��� ��ǥ�� ���� ����. 
	::SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top); 
	// rcMain = { 200, 200, 1200, 1200} 
	RECT rcView = {}; 
	GetClientRect(&rcView);
	int iWidth = rcMain.right - rcView.right ; 
	int iHeight = rcMain.bottom - rcView.bottom; 

	CSize tSize;
	GetScrollBarSizes(tSize);

	pMainFrame->SetWindowPos(nullptr, 0, 0, WINCX + iWidth , WINCY + iHeight , SWP_NOZORDER);
	/*
	SetWindowPos - ������â�� ũ�⸦ ���������ִ� �Լ�. 
	1. ��ġ�� �������� Z������ ���� ������. null�ϰ�� �ǵ帮�� �ʰڴ�. �׳� ���� �״�� ����ϰڴ� �� default 
	2.3. ��ġ. xy
	4,5. ���μ��� ũ�� 
	6. ���� ���� . ���� �־��� ���ڴ� ������ �ٲ��� �ʰڴ�. Ȥ�� �� ��ġ ���� �ɼ��̶���� �䷱ �͵� ��. 
	*/

	g_hWND = m_hWnd; 
	if (FAILED(GET_INSTANCE(CDevice)->InitDevice()))
	{
		AfxMessageBox(L"InitDevice Failed"); 
		return; 
	}

	// CDevice->InitDevice �� ������ �ؽ��� �־�� ��!! **************************
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::SINGLETEX, L"../Texture/Cube.png", L"Cube");
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Stage/Terrain/Tile2/Tile%d.png", L"Terrain", L"Tile", 9);
	GET_INSTANCE(CTextureMgr)->InsertTexture(CTextureMgr::MULTITEX, L"../Texture/Stage/Background/%d.png", L"Background", L"Background", 2);
	m_pBackgroundTex = CTextureMgr::Get_Instance()->Get_TexInfo(L"Background", L"Background", 0);




}


void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapTool& MapTool = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitterWnd.GetPane(1, 0))->m_MapTool;
	switch (m_eToolID)
	{
	case MAPTOOL::TILE:
		MapTool.m_pTileTool->ViewLButtonDown(nFlags, point);
		break;
	case MAPTOOL::OBJECT:
		MapTool.m_pObjectTool->ViewLButtonDown(nFlags, point);
		break;
	case MAPTOOL::LINE:
		MapTool.m_pLineTool->ViewLButtonDown(nFlags, point);
		break;
	case MAPTOOL::ID_END:
		break;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapTool& MapTool = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitterWnd.GetPane(1, 0))->m_MapTool;
	switch (m_eToolID)
	{
	case MAPTOOL::TILE:
		MapTool.m_pTileTool->ViewMouseMove(nFlags, point);
		break;
	case MAPTOOL::OBJECT:
		MapTool.m_pObjectTool->ViewMouseMove(nFlags, point);
		break;
	case MAPTOOL::LINE:
		MapTool.m_pLineTool->ViewMouseMove(nFlags, point);
		break;
	case MAPTOOL::ID_END:
		break;
	}
	
	if (GetAsyncKeyState(VK_RBUTTON)) {
		int x = GetScrollPos(0);
		int y = GetScrollPos(1);
		SetScrollPos(0, x + (m_tMouseOldPt.x-point.x));
		SetScrollPos(1, y + (m_tMouseOldPt.y-point.y));
		m_tMouseOldPt = point;
		//ScrollToPosition(point); // �̻�
	}

	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(0);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_SecondSplitterWnd.GetPane(0, 0));
	pMiniView->Invalidate(0);
	CScrollView::OnTimer(nIDEvent);
}


void CMFCToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_tMouseOldPt = point;

	CScrollView::OnRButtonDown(nFlags, point);
}

void CMFCToolView::Draw_Background()
{
	if (!m_pBackgroundTex) return;
	D3DXMATRIX matScale, matTrans, matWorld;

	float fCenterX = m_pBackgroundTex->tImageInfo.Width * 0.5f;
	float fCenterY = m_pBackgroundTex->tImageInfo.Height * 0.5f;
	
	float fScale = 0.3f;

	int width = m_pBackgroundTex->tImageInfo.Width * fScale;
	int height = m_pBackgroundTex->tImageInfo.Height * fScale;
	int x = WINCX / width + 2;
	int y = WINCY / height + 2;

	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			D3DXMatrixScaling(&matScale, fScale, fScale, 0.f);
			D3DXMatrixTranslation(&matTrans, j * width, i * height, 0.f);
			matWorld = matScale * matTrans;

			GET_INSTANCE(CDevice)->Get_Sprite()->SetTransform(&matWorld);
			GET_INSTANCE(CDevice)->Get_Sprite()->Draw(m_pBackgroundTex->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}
