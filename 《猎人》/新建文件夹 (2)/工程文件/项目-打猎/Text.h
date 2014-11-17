#pragma once
#ifndef      CText_H_
#define		CText_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include <string>
using namespace std;

class CText
{
public:
	LPDIRECT3DDEVICE9 m_pDevice;//���������豸ָ��
	LPD3DXFONT m_pFont;					//��������Ľӿ�
	float m_fTextPosX , m_fTextPosY;	//����������������Ļ�ϵ�����
	RECT m_FontRect;							//������������λ�õľ�������
	wstring m_Content;							//Ҫд������


public:
	CText(LPDIRECT3DDEVICE9 pDevice);
	~CText(void);

	void InitText(float xPos, float yPos , wstring Content);	//��ʼ����������Ļ�ϵ������Լ�����
	void SetContent( wstring Content );	//��ȡ�û�������󣬽��û�����
	//�����ݴ��ݸ����ڲ���m_Content
	//void Logic(float fElapsedTime);
	void Render(float fElapsedTime);

};
#endif