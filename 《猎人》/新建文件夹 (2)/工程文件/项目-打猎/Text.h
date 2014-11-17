#pragma once
#ifndef      CText_H_
#define		CText_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include <string>
using namespace std;

class CText
{
public:
	LPDIRECT3DDEVICE9 m_pDevice;//传进来的设备指针
	LPD3DXFONT m_pFont;					//处理字体的接口
	float m_fTextPosX , m_fTextPosY;	//用来控制字体在屏幕上的坐标
	RECT m_FontRect;							//用来控制字体位置的矩形区域
	wstring m_Content;							//要写的内容


public:
	CText(LPDIRECT3DDEVICE9 pDevice);
	~CText(void);

	void InitText(float xPos, float yPos , wstring Content);	//初始化字体在屏幕上的坐标以及内容
	void SetContent( wstring Content );	//获取用户的输入后，将用户输入
	//的内容传递给类内部的m_Content
	//void Logic(float fElapsedTime);
	void Render(float fElapsedTime);

};
#endif