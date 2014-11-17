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
	wstring m_Account;			//�����Լ��趨���˺���
	wstring m_Password;		//�����Լ��趨������

	CUIButton * m_pLoginButton;	//��½��ť
	CUIButton * m_pQuitButton;		//�˳���ť

	CEditBox * m_pAccount;		//�û������˺����ı༭��
	CEditBox * m_pPassWord;	//�û���������ı༭��
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
