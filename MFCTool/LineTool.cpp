// LineTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "LineTool.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CLineTool �޽��� ó�����Դϴ�.
