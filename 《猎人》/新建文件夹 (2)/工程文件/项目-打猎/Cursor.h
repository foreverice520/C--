#pragma once
#ifndef   CCursor_H_
#define  CCursor_H_
#include "UIElement.h"

class CCursor : public CUIElement
{
private:
	unsigned char m_alpha;	
public:
	CCursor(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CCursor(void);

	//设置光标的移动量，既有正方向，也有负方向
	void SetCursorPos(short Amount );	

	void UILogic(float fElapsedTime);
	void UIRender(float fElapsedTime);
};
#endif