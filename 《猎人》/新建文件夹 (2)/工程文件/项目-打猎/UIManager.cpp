#include "UIManager.h"

CUIManager::CUIManager(void)
{
}

CUIManager::~CUIManager(void)
{
}

void CUIManager :: AddNewUIElement(CUIElement * pElement)
{
	m_UIelement.push_back(pElement);
}

void CUIManager::Logic(float fElapsedTime )
{
	list<CUIElement *>::iterator iter;
	for(iter = m_UIelement.begin() ; iter!= m_UIelement.end() ; ++iter )
	{
		(*iter)->UILogic(fElapsedTime);
	}
}

void CUIManager::Render(float fElapsedTime )
{
	list<CUIElement *>::iterator iter;
	for(iter = m_UIelement.begin() ; iter!= m_UIelement.end() ; ++iter )
	{
		(*iter)->UIRender(fElapsedTime);
	}
}

void CUIManager::HandleProc(HWND hWnd , UINT uMsg , WPARAM wParam ,LPARAM lParam)
{
	list<CUIElement *>::iterator iter;
	for(iter = m_UIelement.begin() ; iter!= m_UIelement.end() ; ++iter )
	{
		(*iter)->HandleProc(hWnd , uMsg,wParam,lParam);
	}
}