#pragma once
#ifndef		CBackGround_H_
#define		CBackGround_H_

#include "Element.h"

class CBackGround : public CElement
{

public:
	CBackGround(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite );
	~CBackGround(void);
};
#endif