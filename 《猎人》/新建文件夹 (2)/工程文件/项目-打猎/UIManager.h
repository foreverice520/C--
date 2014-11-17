#pragma once
#ifndef   CUIManager_H_
#define  CUIManager_H_
#include "UIElement.h"
#include <list>
using namespace std;

class CUIManager
{
public:
	list<CUIElement *> m_UIelement;		//存储所有UI控件的容器
public:
	CUIManager(void);
	~CUIManager(void);

	static CUIManager & GetManager()
	{
		static CUIManager manager;
		return manager;
	}

	void AddNewUIElement(CUIElement *);

	void Logic(float fElapsedTime );
	void Render(float fElapsedTime);

	void HandleProc(HWND hWnd , UINT uMsg , WPARAM wParam ,LPARAM lParam);

};
#endif