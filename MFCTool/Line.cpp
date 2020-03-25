#include "stdafx.h"
#include "Line.h"
#include "MFCToolView.h"
#include "afxdialogex.h"
CLine::CLine()
{
}

CLine::~CLine()
{
	Release();
}

HRESULT CLine::Initialize()
{
	return S_OK;
}

void CLine::Render()
{ 
	CDC* pDC = m_pView->GetDC();
	size_t iSize = m_vecLine.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		pDC->MoveTo(m_vecLine[i]->vLPos.x - m_pView->GetScrollPos(0), m_vecLine[i]->vLPos.y - m_pView->GetScrollPos(1));
		pDC->LineTo(m_vecLine[i]->vRPos.x - m_pView->GetScrollPos(0), m_vecLine[i]->vRPos.y - m_pView->GetScrollPos(1));
	}

	m_pView->ReleaseDC(pDC);

}

void CLine::Release()
{
	for_each(m_vecLine.begin(), m_vecLine.end(), Safe_Delete<LINE*>);

	m_vecLine.clear();
 
	m_vecLine.shrink_to_fit();
}

void CLine::GridRender()
{
	CDC* pDC = m_pView->GetDC();

	for (int i = 0; i < 1000 + 1; i++)
	{
		pDC->MoveTo(i * 32 - m_pView->GetScrollPos(0), 0);
		pDC->LineTo(i * 32 - m_pView->GetScrollPos(0), 20 * 32);
	}
	for (int i = 0; i < 20 + 1; i++)
	{
		pDC->MoveTo( - m_pView->GetScrollPos(0), i * 32);
		pDC->LineTo((int)(1000 * 32 - m_pView->GetScrollPos(0)), i * 32);
	}
	m_pView->ReleaseDC(pDC);
}

void CLine::Load_Line()
{
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"DataFile(*.dat)|*.dat||");
	
	TCHAR szFilePath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Save Failed");
			return;
		}

		CloseHandle(hFile);
	}
}
