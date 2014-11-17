#pragma once
#ifndef CElement_H_
#define CElement_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define SAFE_RELEASE(p) { 	if(p) 	p->Release() ; 	p = NULL ; }
#define SAFE_DELETE(p) { 	if(p) 	delete p ; 	p = NULL ; }
class CElement
{
protected:
	HWND m_hWnd;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	RECT m_ClientRect;						//客户区的矩形区域

	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_d3dii;
	UINT m_uiWidth , m_uiHeight;

	D3DXVECTOR2 m_vInitPos;	
	D3DXVECTOR2 m_vCurrentPos;	//图片的当前坐标
	D3DXVECTOR2 m_vPos;			//整个帧序列在客户区的位置

	UINT m_Rows;				//帧序列的行数
	UINT m_Cols;				//帧序列的列数

	UINT m_uiWidthPerFrame;		//每帧的宽度（像素为单位）
	UINT m_uiHeightPerFrame;		//每帧的高度（像素为单位）

	bool m_bIsShow;							//图片是否显示
	D3DXMATRIX m_Matrix;			//图片本身的矩阵变换信息

	RECT m_CurrentRect;					//物体当前在屏幕上的矩形区域
	float m_fFrameSpeed;
	
	UINT m_Move;//向左右移动0右,1左;

public:
	CElement(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite );
	~CElement(void);

	void InitElement( LPWSTR pFileName , 
		D3DXVECTOR2 vInitPos , bool bIsShow = true );	//初始化图片

	void Show(){ m_bIsShow = true ; }
	void Hide(){ m_bIsShow = false ; }

	RECT * GetCurrentRect(){ return &m_CurrentRect ; };

	virtual void Logic(float fElapsedTime);
	virtual void Render(float fElapsedTime);
	virtual void HandleMessage(HWND hWnd ,UINT uMsg , WPARAM wParam ,LPARAM lParam);
};
#endif
