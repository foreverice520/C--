#pragma once
#ifndef  CUIButton_H_
#define CUIButton_H_
#include "UIElement.h"

#include <list>
using namespace std;

class CUIButton : public CUIElement
{
public:
	list<CLoadImage *>  m_ListButton;			//�洢ͼƬ������
	LPDIRECT3DTEXTURE9 m_pCurrentButton;		//��ǰ��ʾ��ͼƬ

	POINT m_ptMousePos;		//��굱ǰ��λ��
	RECT m_ButtonRect;			//��ť������

	enum ButtonType{ BT_LOGIN , BT_QUIT };		//ö�ٰ�ť������
	ButtonType m_ButtonType;		//��ǰ��ť������

	bool m_bIsDown;			//��boolֵ����������ǰ��ť�Ƿ񱻰���

public:
	CUIButton(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CUIButton(void);

	//��ʼ��UI�ؼ��ĺ���������1Ϊǰ��·�����ļ�����
	//����2ΪͼƬ����������3ΪͼƬ��չ��������4�ؼ���x���꣬
	//����5�ؼ���y���꣬����6�ؼ��Ƿ���ʾ
	void InitElement(LPWSTR pFront , UINT iCount ,
		LPWSTR pBack ,   float fxPos , float fyPos, bool bIsShow = true );	
	void SetButtonType(ButtonType type);		//���ð�ť���͵ĺ���

	bool IsInButton();		//�����ж�����Ƿ��ھ���������
	bool GetButtonState();//true����ǰ��ť�����£�falseΪû�а���

	void UILogic(float fElapsedTime);		//�߼�ѭ��
	void UIRender(float fElapsedTime);	//��Ⱦѭ��
};

#endif