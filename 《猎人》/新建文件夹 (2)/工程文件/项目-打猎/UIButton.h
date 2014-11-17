#pragma once
#ifndef  CUIButton_H_
#define CUIButton_H_
#include "UIElement.h"

#include <list>
using namespace std;

class CUIButton : public CUIElement
{
public:
	list<CLoadImage *>  m_ListButton;			//存储图片的容器
	LPDIRECT3DTEXTURE9 m_pCurrentButton;		//当前显示的图片

	POINT m_ptMousePos;		//鼠标当前的位置
	RECT m_ButtonRect;			//按钮的区域

	enum ButtonType{ BT_LOGIN , BT_QUIT };		//枚举按钮的类型
	ButtonType m_ButtonType;		//当前按钮的类型

	bool m_bIsDown;			//该bool值用来描述当前按钮是否被按下

public:
	CUIButton(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CUIButton(void);

	//初始化UI控件的函数，参数1为前段路径及文件名，
	//参数2为图片数量，参数3为图片扩展名，参数4控件的x坐标，
	//参数5控件的y坐标，参数6控件是否显示
	void InitElement(LPWSTR pFront , UINT iCount ,
		LPWSTR pBack ,   float fxPos , float fyPos, bool bIsShow = true );	
	void SetButtonType(ButtonType type);		//设置按钮类型的函数

	bool IsInButton();		//用来判断鼠标是否在矩形区域内
	bool GetButtonState();//true代表当前按钮被按下，false为没有按下

	void UILogic(float fElapsedTime);		//逻辑循环
	void UIRender(float fElapsedTime);	//渲染循环
};

#endif