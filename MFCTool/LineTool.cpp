// LineTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "LineTool.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CLineTool 메시지 처리기입니다.
