#pragma once
#ifndef CBird_H_
#define CBird_H_
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include<vector>
using namespace std;
#include"Element.h"
class CBird:public CElement
{
private:
	/*vector<RECT*> m_FrameList;
	vector<RECT*>::iterator m_iter;	*/

	vector<RECT *> m_FrameListRight;
	vector<RECT *>::iterator m_iterRight;

	vector<RECT *> m_FrameListLeft;
	vector<RECT *>::iterator m_iterLeft;

	float m_fVelocity;		//�ٶȣ���������С����ĵ�����ٶ�
	bool m_bIsRota;								//�Ƿ���ת
	D3DXVECTOR2 m_vRotaCenter;		//��ת����
	float m_fVelocityRota;						//��ת�ٶ�
public:
	CBird(HWND hWnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite,UINT m_Move=0);
	~CBird(void);
	void InitBird(LPWSTR pFileName, UINT row, UINT col ,D3DXVECTOR2 vPos,float fFrameSpeed  = 0.1f );
	void SetBirdState(){ m_Move = rand()%2; };
	UINT GetBirdMove(){return m_Move;}
	D3DXVECTOR2 GetCurrentPos(){return m_vPos;}
	void SetRota(){ m_bIsRota = true ; };
	void SetBirdStateDown(){m_Move=2;}
	void BirdLogic(float fElapsedTime);
	void BirdRender(float fElapsedTime);
	void BirdHandleMessage(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
};
#endif