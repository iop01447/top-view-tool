#include "stdafx.h"
#include "Device.h"
#include "MFCToolView.h"
#include "MainFrm.h"
CDevice* CDevice::m_pInstance = nullptr;
CDevice::CDevice()
	:m_p3D(nullptr)
	,m_pDevice(nullptr)
	,m_pSprite(nullptr)
	,m_pFont(nullptr)
	,m_pLine(nullptr)
	,bGridChack(false)
	, pLineM(nullptr)
{
}


CDevice::~CDevice()
{
	Release(); 
}

HRESULT CDevice::InitDevice()
{
	//1.��ġ�� �����ϴ� �İ�ü�� ���� �Ұ�. (m_p3D)
	//2.��ġ�� �����ϴ� �İ�ü(m_p3D)�� �̿��Ͽ� �׷��� ī���� ���� ������ �����Ѵ�. ������ ���� �ϴ���. 
	//3.m_p3D��ü�� �̿��Ͽ� ��ġ�� �����ϴ� �İ�ü�� ���� �� ��.(m_pDevice)

	//1.��ġ�� �����ϴ� �İ�ü�� ����. 
	D3DCAPS9 DeviceCaps; 
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT //�� ���ڴ� ���� ������ �ִ� �׷���ī���� ������ �����ϰڴٶ�� ��. 
		, D3DDEVTYPE_HAL // HAL�� ���� ���� ������ �����ڴ�. 
			//HAL - �ϵ���� �߻� ����, �׷��� ī�帶�� �����ϴ� ���� ��� �� �ٸ����� ���� �÷����� ���ư��� ����� �����͸� ������ �־�� �Ѵ�. 
			// �װ��� HAL�̶�� ������ ��Ƶд�. ���� ��û�ؼ�? ���Ұ� ��û�ؼ�. 
		, &DeviceCaps
	)))
	{
		AfxMessageBox(L"GetDeviceCaps Failed!");
		return E_FAIL; 
	}

	// ���ؽ� ���μ����� ������ �����ؾ� �Ѵ�. 
	// ������ȭ + ������ 
	DWORD vp = 0; 
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// ������� ����
	d3dpp.BackBufferWidth = WINCX;
	//������� ����
	d3dpp.BackBufferHeight = WINCY;
	// ����� � �Ѱ��� �츰 1�� 
	d3dpp.BackBufferCount = 1;

	// �⺻ �ȼ� ������ ��� ����� ���� �츮�� ���� 8��Ʈ, ���� 8��Ʈ �׸� 8��Ʈ ��� 8��Ʈ ����ϰڴ�. 
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// ��Ƽ���ø� - �̹����� ǥ���ϴµ� �־� ��Ÿ���� ��ģ �̹����� �ε巴�� ����� ���. 
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; 
	// ��Ƽ ���ø��� ����Ƽ�� ���Ѵ�. �Ⱦ��� 0
	d3dpp.MultiSampleQuality = 0;
	// _D3DSWAPEFFECT 3���� �̳Ѱ��� ����. 
	//D3DSWAPEFFECT_DISCARD - ����ü�� ����� ����ϰڴ�. ��������۸��� ����ȣȯ����. 
	// ���� ���ۿ� �ĸ� ���� �ΰ��� �ΰ� �ĸ�ο� �׸��� �׸��� ������ۿ� �ٲٴ� ����. 
	// �׸��� �̰� ������ �ϸ� ��ġ ü�θ���̶� �ؼ� ����ü��. 

	//D3DSWAPEFFECT_FLIP - �̰Ŵ� ���� ���� �ٽ� �����ؿ�. 

	//D3DSWAPEFFECT_COPY - �츮�� ����ϴ� ������۸�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.Windowed = TRUE; 
	// TRUE - â 
	// FALSE - ��ü 

	// ���̰��� ������ ���ۿ� ���׽� ���۸� �˾Ƽ� �ϰԲ� ����� �ٰ�. 
	d3dpp.EnableAutoDepthStencil = TRUE; 
	// ������ ���̹��۸� ����� ���� ����. �� ? ���ʿ� z���� ���� ����. 2D�ϱ�. 
	// ���ٽǵ� 3d �Ѿ�� ����. 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	// ���̰� 24��Ʈ ���, ���ٽ� 8��Ʈ ��� 

	// 
	// �ֻ��� ���ߴ� ����. 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; 

	// ���� �ٽ� �˾ƿ�. 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp,&d3dpp, &m_pDevice)))
	{
		AfxMessageBox(L"CreateDevice Func Failed!");
		return E_FAIL; 
	}
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		AfxMessageBox(L"CreateSprite Func Failed!"); 
		return E_FAIL; 
	}
	// ������ ��Ʈ�� ���� ������ ���� ����ü. 
	D3DXFONT_DESCW tFontInfo; 
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Width = 5; 
	tFontInfo.Height = 10; 
	tFontInfo.Weight = FW_NORMAL; // �β���. 
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");
	// D3DXCreateFontIndirect - ��Ʈ ����ü ������ ���� ��Ʈ ��ü�� �����ϴ� �Լ�. 
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo,&m_pFont)))
	{
		AfxMessageBox(L"CreateFont Failed!"); 
		return E_FAIL; 
	}




	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		AfxMessageBox(L"CreateLine Func Failed!");
		return E_FAIL;
	}


	GridSet();

	pLineM = new LINE;

	pLineM->vLine[0] = { -1.f,-1.f };
	pLineM->vLine[1] = { -1.f,-1.f };
	m_pLine->SetWidth(2); // ������


	return S_OK;
}

void CDevice::Release()
{
	if (m_pFont)
		m_pFont->Release(); 

	if (m_pSprite)
		m_pSprite->Release();

	// LPDIRECT3DDEVICE9 �ȿ��� ���������� LPDIRECT3D9�� �����ϰ� �ֱ� ������ m_pDevice���� ���� ��� �Ѵ�. 
	if (m_pDevice)
		m_pDevice->Release();

	if (m_p3D)
		m_p3D->Release();

	if (m_pLine)
		m_pLine->Release();


	



	for_each(m_vGrid.begin(), m_vGrid.end(), Safe_Delete<LINE*>);

	m_vGrid.clear();
	m_vGrid.shrink_to_fit();

	for_each(m_vGrid_Per.begin(), m_vGrid_Per.end(), Safe_Delete<LINE*>);

	m_vGrid_Per.clear();
	m_vGrid_Per.shrink_to_fit();

	for_each(m_vLine.begin(), m_vLine.end(), Safe_Delete<LINE*>);

	m_vLine.clear();
	m_vLine.shrink_to_fit();

	Safe_Delete(pLineM);
	// ���� �߿� ! ���۸� �����͸� �����ϱ� ���� ���۷��� ī��Ʈ ��� ����� ����ϰ� ����. 

}

void CDevice::Render_Begin()
{
	// �츮�� ���� �׸��� �׸��� ��� �Ұų� . 
	// �׸��׸��� ���� - �ĸ���۸� ����� -> �ĸ���ۿ� �׸��� �׸��� -> �ĸ���ۿ� ���� ���۸� ��ü�Ѵ�. 

	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 0), 0, 0);
	m_pDevice->BeginScene();
	// ��������Ʈ ��ü�� ����ؼ� �׸��� �׸��ڴ� ��� ���� �־���� �Ѵ�. 
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CDevice::Render_End(HWND hWnd /*= nullptr*/)
{
	m_pSprite->End();

	m_pLine->Begin();
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	if (nullptr == pMain)
		return;
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitterWnd.GetPane(0, 1));

	D3DXVECTOR2 Scroll[2] =
	{ D3DXVECTOR2((float)(pView->GetScrollPos(0)),(float)(pView->GetScrollPos(1))),
		D3DXVECTOR2((float)(pView->GetScrollPos(0)),(float)(pView->GetScrollPos(1))) };

	if (bGridChack)
	{
		for (auto& iter : m_vGrid)
		{

			D3DXVECTOR2 LineS[2] = {
				D3DXVECTOR2((*iter).vLine[0].x - Scroll[0].x,(*iter).vLine[0].y - Scroll[0].y),
				D3DXVECTOR2((*iter).vLine[1].x - Scroll[1].x,(*iter).vLine[1].y - Scroll[1].y)
			};

			m_pLine->Draw(LineS, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		for (auto& iter : m_vGrid_Per)
		{
			D3DXVECTOR2 LineS[2] = {
				D3DXVECTOR2((*iter).vLine[0].x - Scroll[0].x,(*iter).vLine[0].y - Scroll[0].y),
				D3DXVECTOR2((*iter).vLine[1].x - Scroll[1].x,(*iter).vLine[1].y - Scroll[1].y)
			};


			m_pLine->Draw(LineS, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}


	if (!(m_vLine.empty()))
	{
		for (LINE* iter : m_vLine)
		{
			/*D3DXVECTOR2 LineS[2] = {
				D3DXVECTOR2((*iter).vLine[0].x - Scroll[0].x,(*iter).vLine[0].y - Scroll[0].y),
				D3DXVECTOR2((*iter).vLine[1].x - Scroll[1].x,(*iter).vLine[1].y - Scroll[1].y)
			};*/
			m_pLine->Draw((*iter).vLine, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	m_pLine->End();

	m_pDevice->EndScene();
	// ������۷� ��ü! 
	// 3��° ���ڸ� �������. 
	// 3��° ���ڴ� ��� ������â�� �׸� ���ΰ�. 
	// ���� nullptr �־��ٸ� �츮�� ������ �־��� g_hWND�� ����Ʈ�� ������. 
	// ���� �ٸ� ������ â�� �׸��� �׸��� �ʹٸ�!? 3��° ���ڿ� ���� �׸����� �ϴ� ������ â�� �ڵ��� �־��ָ� �ȴ�. 
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}


void CDevice::GridSet()
{
	
	float fX = 0.f, fY = 0.f;
	LINE* pLine = nullptr;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{

			fX = float((j * TILECX))+OFFSET;
			fY = float((i * TILECY))+ OFFSET;
			pLine = new LINE;
			pLine->vLine[0] = { fX,fY };
			pLine->vLine[1] = {fX+ TILECX ,fY };
			m_vGrid.emplace_back(pLine);
		}

	}
	LINE* pLine_per = nullptr;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			fX = float((j * TILECX)) + OFFSET;
			fY = float((i * TILECY)) + OFFSET;
			pLine_per = new LINE;
			pLine_per->vLine[0] = { fX,fY };
			pLine_per->vLine[1] = { fX  ,fY+ TILECY };
			m_vGrid_Per.emplace_back(pLine_per);
		}

	}


}

void CDevice::Line_Set(D3DXVECTOR2 & rMouse)
{


	if ((pLineM->vLine[0]) == D3DXVECTOR2(-1.f,-1.f))
	{
		pLineM->vLine[0] = { rMouse.x,rMouse.y };
	}
	else
	{
		pLineM->vLine[1] = { rMouse.x,rMouse.y };

		LINE* line = new LINE;
		*line = *pLineM;
		m_vLine.emplace_back(line);

		pLineM->vLine[0] = { -1.f,-1.f };
		pLineM->vLine[1] = { -1.f,-1.f };
	}

}

