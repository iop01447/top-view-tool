#pragma once
// 순수 파일다루는 기능만 제공할 객체 
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();
public:
	static CString ConvertRelativePath(const CString& rstrFullPath);
};

