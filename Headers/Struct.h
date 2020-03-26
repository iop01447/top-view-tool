#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture; 
		// 너네가 예전에 썼던 hBitmap 역할을 할 com객체 
	// 그림한장을 관리 제어 하기 위한 컴객체. 

	D3DXIMAGE_INFO tImageInfo; 
		// 그림의 정보를 가지고 있을 구조체. 
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
	D3DXVECTOR2 vLine[2];
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
	int iAtt = 0; // 이 행위 자체가 이니셜라이져문법을 호출하는 행위이다. 
	int iDef = 0;
	BYTE byClass = 0;
	BYTE byItem =0 ;
}UNIT;

#endif



