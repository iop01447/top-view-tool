#pragma once
// ���� ���ϴٷ�� ��ɸ� ������ ��ü 
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();
public:
	static CString ConvertRelativePath(const CString& rstrFullPath);
};

