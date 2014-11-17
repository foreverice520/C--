#pragma once

#ifndef		CUIElement_H_
#define    CUIElement_H_
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "LoadImage.h"		//����һ�¼���ͼƬ����

class CUIElement
{
public:
	HWND m_hWnd;									//��ǰ���ھ��
	LPDIRECT3DDEVICE9 m_pDevice;	//�豸ָ��
	LPD3DXSPRITE m_pSprite;					//����ָ��

	bool m_bIsShow;						//��ǰUI�Ƿ���ʾ
	D3DXVECTOR2 m_vUIPos;		//����UI����Ļ�ϵ�λ��
	D3DXMATRIX m_matUIMatrix;	//UI�ľ���

	CLoadImage * m_pImage;		//ͼƬ��ָ��
	float m_fWidth;							//ͼƬ�Ŀ�
	float m_fHeight;						//ͼƬ�ĸ�

	RECT m_TexRect;					//ͼƬ�ľ������򣬿����������ƻ�������ͼƬ���ĸ�����
	RECT m_ClientRect;				//�ͻ����ľ���������Ϣ

	float m_fXScale;			//ͼƬ��x�����ϵ�������
	float m_fYScale;			//ͼƬ��y�����ϵ�������
public:
	CUIElement(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CUIElement(void);

	void Show()//��UI��ʾ����
	{ 
		m_bIsShow = true ;
	}		
	void Hide()//��UI���ص�
	{ 
		m_bIsShow = false ;
	}		

	//��ʼ��UI�ؼ��ĺ���������1�ؼ�ͼƬ��·�����ļ���������2�ؼ���x���꣬����3�ؼ���y���꣬����4�ؼ��Ƿ���ʾ
	void InitElement( LPWSTR pFileName,   float fxPos , float fyPos, bool bIsShow = true );	

	//��ʼ��UI�ؼ��ĺ���������1Ϊǰ��·�����ļ���������2ΪͼƬ����������3ΪͼƬ��չ��������4�ؼ���x���꣬����5�ؼ���y���꣬����6�ؼ��Ƿ���ʾ
	void InitElement(LPWSTR pFront , UINT iCount ,LPWSTR pBack ,   float fxPos , float fyPos, bool bIsShow = true );	

	virtual void UILogic(float fElapsedTime);		//�麯����UI�߼�ѭ��
	virtual void UIRender(float fElapsedTime);	//�麯����UI��Ⱦѭ��

	//�麯������Ϣ������
	virtual void HandleProc(HWND hWnd , UINT uMsg , WPARAM wParam, LPARAM lParam);

};
#endif