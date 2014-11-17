#pragma once
#ifndef     CEditBox_H_
#define    CEditBox_H_
#include "UIElement.h"
#include "Text.h"
#include "Cursor.h"

class CEditBox : public CUIElement
{
public:
	CText * m_pText;			//字体类的指针，用来处理与文字有关的内容
	CCursor * m_pCursor;	//光标的指针
	wstring m_InputStr;		//获取用户输入的数据
	wstring m_Password;	//密码字符串，用来存“*”
	UINT m_MaxCount;		//规定所能输入的最大的字符数
	short m_state;				//0标识当前编辑框为“非密码编辑框” ，
	//1标识当前编辑框为“密码编辑框” 

public:
	CEditBox(HWND hWnd , LPDIRECT3DDEVICE9 pDevice);
	~CEditBox(void);

	wstring GetContent(){ return m_InputStr ; };	//返回当前编辑框中的实际的内容
	void InitEditBoxText( UINT state );	//用来初始化CEditBox类中的m_pText指针，	
	//并规定当前CEditBox的类型（）
	void UILogic(float fElapsedTime);
	void UIRender(float fElapsedTime);
	void HandleProc(HWND hWnd , UINT uMsg , WPARAM wParam, LPARAM lParam);
};
#endif
