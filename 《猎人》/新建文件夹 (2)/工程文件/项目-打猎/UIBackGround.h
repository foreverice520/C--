#pragma once
#ifndef  CUIBackGround_H_
#define CUIBackGround_H_

#include "UIElement.h"


class CUIBackGround : public CUIElement
{
public:
	CUIBackGround(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CUIBackGround(void);

	void SetScale();
	virtual void UIRender(float fElapsedTime);	//Ðéº¯ÊýµÄUIäÖÈ¾Ñ­»·

};
#endif