#include "UIButton.h"

CUIButton::CUIButton(HWND hWnd , LPDIRECT3DDEVICE9 pDevice):
CUIElement(hWnd,pDevice)
{
	m_ptMousePos.x = 0;
	m_ptMousePos.y = 0;

	SetRectEmpty(&m_ButtonRect);
	m_bIsDown = false;			//按钮没有被按下
}

CUIButton::~CUIButton(void)
{
}

void CUIButton::InitElement(LPWSTR pFront , UINT iCount ,LPWSTR pBack , 
							float fxPos , float fyPos, bool bIsShow /* = true */ )
{
	//new一个CLoadImage类的指针
	WCHAR str[100];
	memset(str,0,sizeof(str));

	for( UINT i = 0 ; i < iCount ; ++i )
	{	
		CLoadImage * pTempImage = new CLoadImage(m_pDevice);	
		swprintf_s(str,L"%s%d%s",pFront,i,pBack);
		pTempImage->InitTexture(str);
		m_ListButton.push_back(pTempImage);

		m_fWidth = (float)pTempImage->m_d3dii.Width;		//获取图片的宽
		m_fHeight = (float)pTempImage->m_d3dii.Height;		//获取图片的高

	}

	m_vUIPos.x = fxPos;			//给图片的x坐标赋值
	m_vUIPos.y = fyPos;			//给图片的y坐标赋值

	SetRect(&m_TexRect,0,0,(int)m_fWidth,(int)m_fHeight);

	list<CLoadImage*>::iterator iter = m_ListButton.begin();	//取得容器中的第一个元素的迭代器
	m_pCurrentButton =(*iter)->m_pTexture;	//获取当前显示的图片

	m_fXScale =    m_fWidth  / (float)m_ClientRect.right;
	m_fYScale =   m_fHeight / (float)m_ClientRect.bottom;

	SetRect(
		&m_ButtonRect,m_vUIPos.x,m_vUIPos.y,
		m_vUIPos.x+m_fWidth, m_vUIPos.y+m_fHeight
		);

}

void CUIButton::SetButtonType(ButtonType type)
{
	m_ButtonType = type;
}

bool CUIButton::IsInButton()
{
	if(PtInRect(&m_ButtonRect,m_ptMousePos))
		return true;
	else
		return false;
}

void CUIButton::UILogic(float fElapsedTime)
{
	GetCursorPos(&m_ptMousePos);	//获取光标的位置（相对于屏幕左上角）
	ScreenToClient(m_hWnd,&m_ptMousePos);	//转换为相对于客户区

	list<CLoadImage*>::iterator iter = m_ListButton.begin();
	if(IsInButton())		//悬停
	{
		iter++;
		m_pCurrentButton = (*iter)->m_pTexture;
	}

	if(IsInButton() && GetAsyncKeyState(VK_LBUTTON))  //按下
	{
		iter++;
		m_pCurrentButton = (*iter)->m_pTexture;
		if(m_ButtonType == BT_QUIT )
			PostQuitMessage(0);

		m_bIsDown = true;		//修改类内部的标记，通知当前按钮已经被按下
	}

	if(m_pCurrentButton !=  (*iter)->m_pTexture )		//正常状态
		m_pCurrentButton = (*iter)->m_pTexture;

	//m_bIsDown = false;	//修改为非按下状态
}

bool CUIButton::GetButtonState()
{
	return m_bIsDown;
}

void CUIButton::UIRender(float fElapsedTime)
{
	if(m_bIsShow)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMatrixTransformation2D(
			&m_matUIMatrix,
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(1.0f,1.0f),
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&m_vUIPos
			);

		m_pSprite->SetTransform(&m_matUIMatrix);
		m_pSprite->Draw(
			m_pCurrentButton, 
			&m_TexRect,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(255,255,255,255)
			);

		m_pSprite->End();
	}
}