#pragma once
#ifndef CHunter_H_
#define CHunter_H_
//#include<d3d9.h>
//#include<d3dx9.h>
//#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
#include"Element.h"
#include"Bomb.h"
#include<vector>
using namespace std;
class CHunter:public CElement
{
private:
	vector<RECT *> m_FramListLeft;
	vector<RECT *> m_FramListRight;
	vector<RECT *> m_FramListUp;
	vector<RECT *>::iterator m_iterLeft;
	vector<RECT *>::iterator m_iterRight;
	vector<RECT *>::iterator m_iterUp;
	UINT m_HunterHP;
	/*UINT m_HunterState;*/
public:
	CHunter(HWND hwnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite);
	~CHunter(void);
	void InitTexture(LPWSTR pFileName,UINT row,UINT col,D3DXVECTOR2 vPos,float fFramSpeed=0.01f);
	void HunterLogic(float fElapsedTime);
	bool IsIntersect( CBomb * pBomb );
	void ComputeHP(/*CBomb * pBomb*/);
	UINT GetHP();
	/*UINT GetHunterState(){return m_HunterState;}
	void SetHunterState(){m_HunterState=0;}*/
	D3DXVECTOR2 GetCurrentpos(){return m_vCurrentPos;};
	void HunterRender(float fElapsedTime);
	void HandleMessage(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
};
#endif;