
// MFCMapTool.h : MFCMapTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCMapToolApp:
// �� Ŭ������ ������ ���ؼ��� MFCMapTool.cpp�� �����Ͻʽÿ�.
//

class CMFCMapToolApp : public CWinAppEx
{
public:
	CMFCMapToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCMapToolApp theApp;
