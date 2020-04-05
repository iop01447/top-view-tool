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
	// 뽑아낸 상대경로. 
	TCHAR szRelativePath[MAX_STR] = L""; 

	// 현재 프로젝트의 경로를 얻어올것. 
	TCHAR szCurDirectory[MAX_STR] = L""; 
	GetCurrentDirectory(MAX_STR, szCurDirectory);


	PathRelativePathTo(szRelativePath, szCurDirectory, FILE_ATTRIBUTE_DIRECTORY, rstrFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY); 
	//from에서 To로 찾아가는 상대경로를 반환 해줄것. 



	return CString(szRelativePath);
}
