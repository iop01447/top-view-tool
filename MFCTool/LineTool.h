#pragma once


// CLineTool ��ȭ �����Դϴ�.

class CLineTool : public CDialog
{
	DECLARE_DYNAMIC(CLineTool)

public:
	CLineTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLineTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
