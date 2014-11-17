#pragma once
#ifndef      CHPText_H_
#define		CHPText_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include <string>
using namespace std;
#include"Hunter.h"
class CHPText
{
public:
	//LPDIRECT3DDEVICE9 m_pDevice;//传进来的设备指针
	//LPD3DXFONT m_pFont;					//处理字体的接口
	//float m_fTextPosX , m_fTextPosY;	//用来控制字体在屏幕上的坐标
	//RECT m_FontRect;							//用来控制字体位置的矩形区域
	//wstring m_Content;							//要写的内容
	HDC hdc;						//设备上下文环境句柄
	PAINTSTRUCT ps;		//绘制结构体体，用来存储系统设备信息

	HFONT hFont;			//定义字体句柄，用来手动创建一个字体

	RECT rect;					//矩形区域
	HBRUSH hBrush;			//一个画刷
	HWND m_hWnd;


public:
	CHPText(HWND hWnd);
	~CHPText(void);

	void InitHPText(float xPos, float yPos , wstring Content);	//初始化字体在屏幕上的坐标以及内容
	void SetContent( wstring Content );	//获取用户的输入后，将用户输入
	void Render(float fElapsedTime);

};
#endif