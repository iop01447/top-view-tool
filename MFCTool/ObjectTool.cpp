// ObjectTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"


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
}

void CObjectTool::ViewLButtonDown(UINT nFlags, CPoint point)
{
}

void CObjectTool::ViewMouseMove(UINT nFlags, CPoint point)
{
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
END_MESSAGE_MAP()


// CObjectTool �޽��� ó�����Դϴ�.
