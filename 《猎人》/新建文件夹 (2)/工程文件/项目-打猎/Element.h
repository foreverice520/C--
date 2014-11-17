#pragma once
#ifndef CElement_H_
#define CElement_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define SAFE_RELEASE(p) { 	if(p) 	p->Release() ; 	p = NULL ; }
#define SAFE_DELETE(p) { 	if(p) 	delete p ; 	p = NULL ; }
class CElement
{
protected:
	HWND m_hWnd;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	RECT m_ClientRect;						//�ͻ����ľ�������

	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_d3dii;
	UINT m_uiWidth , m_uiHeight;

	D3DXVECTOR2 m_vInitPos;	
	D3DXVECTOR2 m_vCurrentPos;	//ͼƬ�ĵ�ǰ����
	D3DXVECTOR2 m_vPos;			//����֡�����ڿͻ�����λ��

	UINT m_Rows;				//֡���е�����
	UINT m_Cols;				//֡���е�����

	UINT m_uiWidthPerFrame;		//ÿ֡�Ŀ�ȣ�����Ϊ��λ��
	UINT m_uiHeightPerFrame;		//ÿ֡�ĸ߶ȣ�����Ϊ��λ��

	bool m_bIsShow;							//ͼƬ�Ƿ���ʾ
	D3DXMATRIX m_Matrix;			//ͼƬ����ľ���任��Ϣ

	RECT m_CurrentRect;					//���嵱ǰ����Ļ�ϵľ�������
	float m_fFrameSpeed;
	
	UINT m_Move;//�������ƶ�0��,1��;

public:
	CElement(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite );
	~CElement(void);

	void InitElement( LPWSTR pFileName , 
		D3DXVECTOR2 vInitPos , bool bIsShow = true );	//��ʼ��ͼƬ

	void Show(){ m_bIsShow = true ; }
	void Hide(){ m_bIsShow = false ; }

	RECT * GetCurrentRect(){ return &m_CurrentRect ; };

	virtual void Logic(float fElapsedTime);
	virtual void Render(float fElapsedTime);
	virtual void HandleMessage(HWND hWnd ,UINT uMsg , WPARAM wParam ,LPARAM lParam);
};
#endif
