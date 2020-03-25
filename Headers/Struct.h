#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture; 
		// �ʳװ� ������ ��� hBitmap ������ �� com��ü 
	// �׸������� ���� ���� �ϱ� ���� �İ�ü. 

	D3DXIMAGE_INFO tImageInfo; 
		// �׸��� ������ ������ ���� ����ü. 
}TEXINFO;
typedef struct tagInfo
{
	D3DXVECTOR3 vPos; 
	D3DXVECTOR3 vSize; 
	D3DXVECTOR3 vLook; 
	D3DXVECTOR3 vDir; 
	D3DXMATRIX matWorld; 

}INFO;
typedef struct tagTile
{
	D3DXVECTOR3 vPos; 
	D3DXVECTOR3 vSize; 
	BYTE		byDrawID; 
	BYTE		byOption;
}TILE;
typedef struct tagLine
{
	D3DXVECTOR3 vLPos;
	D3DXVECTOR3 vRPos;
	BYTE		byOption;
}LINE;

typedef struct tagUnitInfo
{
	tagUnitInfo() 
		:iAtt(10)
	{}
#ifdef _AFX
	CString strName; 
#else 
	wstring strName;
#endif
	int iAtt = 0; // �� ���� ��ü�� �̴ϼȶ����������� ȣ���ϴ� �����̴�. 
	int iDef = 0;
	BYTE byClass = 0;
	BYTE byItem =0 ;
}UNIT;

#endif



