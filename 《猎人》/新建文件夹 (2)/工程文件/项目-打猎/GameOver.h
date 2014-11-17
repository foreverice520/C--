#pragma once
#ifndef		CGameOver_H_
#define		CGameOver_H_

#include "Element.h"

class CGameOver : public CElement
{

public:
	CGameOver(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite );
	~CGameOver(void);
	void Render(float fElapsedTime);
};
#endif