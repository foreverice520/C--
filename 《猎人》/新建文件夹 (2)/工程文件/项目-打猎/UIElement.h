#pragma once

#ifndef		CUIElement_H_
#define    CUIElement_H_
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "LoadImage.h"		//包含一下加载图片的类

class CUIElement
{
public:
	HWND m_hWnd;									//当前窗口句柄
	LPDIRECT3DDEVICE9 m_pDevice;	//设备指针
	LPD3DXSPRITE m_pSprite;					//精灵指针

	bool m_bIsShow;						//当前UI是否显示
	D3DXVECTOR2 m_vUIPos;		//描述UI在屏幕上的位置
	D3DXMATRIX m_matUIMatrix;	//UI的矩阵

	CLoadImage * m_pImage;		//图片的指针
	float m_fWidth;							//图片的宽
	float m_fHeight;						//图片的高

	RECT m_TexRect;					//图片的矩形区域，可以用来控制绘制整张图片的哪个部分
	RECT m_ClientRect;				//客户区的矩形区域信息

	float m_fXScale;			//图片在x方向上的缩放量
	float m_fYScale;			//图片在y方向上的缩放量
public:
	CUIElement(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CUIElement(void);

	void Show()//让UI显示出来
	{ 
		m_bIsShow = true ;
	}		
	void Hide()//让UI隐藏掉
	{ 
		m_bIsShow = false ;
	}		

	//初始化UI控件的函数，参数1控件图片的路径及文件名，参数2控件的x坐标，参数3控件的y坐标，参数4控件是否显示
	void InitElement( LPWSTR pFileName,   float fxPos , float fyPos, bool bIsShow = true );	

	//初始化UI控件的函数，参数1为前段路径及文件名，参数2为图片数量，参数3为图片扩展名，参数4控件的x坐标，参数5控件的y坐标，参数6控件是否显示
	void InitElement(LPWSTR pFront , UINT iCount ,LPWSTR pBack ,   float fxPos , float fyPos, bool bIsShow = true );	

	virtual void UILogic(float fElapsedTime);		//虚函数的UI逻辑循环
	virtual void UIRender(float fElapsedTime);	//虚函数的UI渲染循环

	//虚函数的消息处理函数
	virtual void HandleProc(HWND hWnd , UINT uMsg , WPARAM wParam, LPARAM lParam);

};
#endif