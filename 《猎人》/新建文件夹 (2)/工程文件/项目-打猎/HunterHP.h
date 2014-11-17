#pragma once
#ifndef		CHunterHP_H_
#define		CHunterHP_H_
#include"Element.h"
#include<vector>
#include"Hunter.h"
using namespace std;
class CHunterHP:public CElement
{
private:
	vector<RECT *> m_HPVector;
	vector<RECT *>::iterator m_HPIter;
	CHunter * m_pHunter;
public:
	CHunterHP(HWND hwnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite);
	~CHunterHP(void);
	void InitHunterHP(LPWSTR pFileName,D3DXVECTOR2 vPos);
	void HunterHPLogic(float fElapsedTime);
	void HunterHPRender(float fElapsedTime,CHunter * pHunter);
};
#endif