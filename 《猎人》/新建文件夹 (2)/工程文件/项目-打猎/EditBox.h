#pragma once
#ifndef     CEditBox_H_
#define    CEditBox_H_
#include "UIElement.h"
#include "Text.h"
#include "Cursor.h"

class CEditBox : public CUIElement
{
public:
	CText * m_pText;			//�������ָ�룬���������������йص�����
	CCursor * m_pCursor;	//����ָ��
	wstring m_InputStr;		//��ȡ�û����������
	wstring m_Password;	//�����ַ����������桰*��
	UINT m_MaxCount;		//�涨��������������ַ���
	short m_state;				//0��ʶ��ǰ�༭��Ϊ��������༭�� ��
	//1��ʶ��ǰ�༭��Ϊ������༭�� 

public:
	CEditBox(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CEditBox(void);

	wstring GetContent(){ return m_InputStr ; };	//���ص�ǰ�༭���е�ʵ�ʵ�����
	void InitEditBoxText( UINT state );	//������ʼ��CEditBox���е�m_pTextָ�룬	
	//���涨��ǰCEditBox�����ͣ���
	void UILogic(float fElapsedTime);
	void UIRender(float fElapsedTime);
	void HandleProc(HWND hWnd , UINT uMsg , WPARAM wParam, LPARAM lParam);
};
#endif
