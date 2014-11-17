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

	//���ù����ƶ���������������Ҳ�и�����
	void SetCursorPos(short Amount );	

	void UILogic(float fElapsedTime);
	void UIRender(float fElapsedTime);
};
#endif