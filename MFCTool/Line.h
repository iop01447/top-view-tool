#pragma once
class CMFCToolView;
class CLine
{
public:
	CLine();
	~CLine();
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }

public:
	HRESULT Initialize();
	void Render();
	void Release();

public:
	void GridRender();
	void Load_Line();

private:
	vector<LINE*> m_vecLine;
	CMFCToolView* m_pView;
};

