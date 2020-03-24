#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(const CString & rstrFullPath)
{
	// �̾Ƴ� �����. 
	TCHAR szRelativePath[MAX_STR] = L""; 

	// ���� ������Ʈ�� ��θ� ���ð�. 
	TCHAR szCurDirectory[MAX_STR] = L""; 
	GetCurrentDirectory(MAX_STR, szCurDirectory);


	PathRelativePathTo(szRelativePath, szCurDirectory, FILE_ATTRIBUTE_DIRECTORY, rstrFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY); 
	//from���� To�� ã�ư��� ����θ� ��ȯ ���ٰ�. 



	return CString(szRelativePath);
}
