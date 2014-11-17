#pragma once
#ifndef _CBomb_H_
#define _CBomb_H_
#include<vector>
using namespace std;
#include"Element.h"
#include"Bird.h"
enum BombState{BS_BLAST , BS_NONINTERSECT , BS_INTERSECT};
class CBomb:public CElement
{
private:
	CBird * m_pBird;
	float m_fVelocity;			// С�����ٶȵĳ��ٶ�
	float m_fGrivate;			// С���յ�������

	BombState m_BombState;		//С���״̬
	bool m_bIsHurt;


	vector<RECT *> m_FrameList;
	vector<RECT *>::iterator m_iter;
public:
	CBomb(HWND hWnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite);
	~CBomb(void);
	void SetBombShow(){m_bIsShow=true;}
	void InitBombTexture(LPWSTR pFileName,UINT row,UINT col,CBird * pBird,float fFramSpeed=0.1f);
	RECT * GetCurrentRect(){return & m_CurrentRect;}
	BombState GetBombState(){return m_BombState;}
	void SetIsHurtTrue(){m_bIsHurt=true;}
	void SetIsHurtFalse(){m_bIsHurt=false;}
	bool GetIsHurt(){return m_bIsHurt;}
	void BombLogic(float fElapsedTime);
	void BombRender(float fElapsedTime);
	void BombHandleMessage(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
};
#endif