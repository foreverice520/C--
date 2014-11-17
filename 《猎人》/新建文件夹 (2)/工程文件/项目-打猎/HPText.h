#pragma once
#ifndef      CHPText_H_
#define		CHPText_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include <string>
using namespace std;
#include"Hunter.h"
class CHPText
{
public:
	//LPDIRECT3DDEVICE9 m_pDevice;//���������豸ָ��
	//LPD3DXFONT m_pFont;					//��������Ľӿ�
	//float m_fTextPosX , m_fTextPosY;	//����������������Ļ�ϵ�����
	//RECT m_FontRect;							//������������λ�õľ�������
	//wstring m_Content;							//Ҫд������
	HDC hdc;						//�豸�����Ļ������
	PAINTSTRUCT ps;		//���ƽṹ���壬�����洢ϵͳ�豸��Ϣ

	HFONT hFont;			//�����������������ֶ�����һ������

	RECT rect;					//��������
	HBRUSH hBrush;			//һ����ˢ
	HWND m_hWnd;


public:
	CHPText(HWND hWnd);
	~CHPText(void);

	void InitHPText(float xPos, float yPos , wstring Content);	//��ʼ����������Ļ�ϵ������Լ�����
	void SetContent( wstring Content );	//��ȡ�û�������󣬽��û�����
	void Render(float fElapsedTime);

};
#endif