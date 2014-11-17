#pragma once
#pragma once

#ifndef CGame_H_
#define CGame_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#define SAFE_RELEASE(p) { 	if(p) 	p->Release() ; 	p = NULL ; }
#define SAFE_DELETE(p) { 	if(p) 	delete p ; 	p = NULL ; }

#include <iostream>
using namespace std;
#include"BackGround.h"
#include"Bird.h"
#include"Arrow.h"
#include<vector>
#include"Hunter.h"
#include"Bomb.h"
#include "UIBackGround.h"
#include "UIButton.h"
#include "UIManager.h"
#include "Text.h"
#include "EditBox.h"
#include "Cursor.h"
#include"GameOver.h"
#include"HunterHP.h"
#include"MyFMod.h"
using namespace std;
class CGame
{
private:
	HWND m_hWnd;
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	CBackGround  * m_pBackGround;
	vector<CBird *> m_pBirdVector;
	vector<CBird *>::iterator m_BirdIter;
	CArrow * m_pArrow;
	CHunter * m_pHunter;
	CHunterHP * m_pHunterHP;
	vector<CBomb *> m_pBombVector;
	vector<CBomb *>::iterator m_BombIter;
	wstring m_Account;			//我们自己设定的账号名
	wstring m_Password;		//我们自己设定的密码

	CUIButton * m_pLoginButton;	//登陆按钮
	CUIButton * m_pQuitButton;		//退出按钮

	CEditBox * m_pAccount;		//用户输入账号名的编辑框
	CEditBox * m_pPassWord;	//用户输入密码的编辑框
	CGameOver * pGameOver;
	UINT m_GameState;
	MyFMod * pFmod;
public:
	CGame(HWND hWnd);
	~CGame(void);
	void InitD3D();
	void InitGame();
	void GameLogic(float fElapsedTime);
	void GameRender(float fElapsedTime);

	void HandleMessage(HWND hWnd ,UINT uMsg,WPARAM wParam ,LPARAM lParam);
};
#endif
