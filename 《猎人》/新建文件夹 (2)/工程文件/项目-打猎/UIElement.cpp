#include "UIElement.h"

CUIElement::CUIElement(HWND hWnd , LPDIRECT3DDEVICE9 pDevice)
{
	m_hWnd = hWnd;
	m_pDevice = pDevice;
	D3DXCreateSprite(m_pDevice,&m_pSprite);
	m_bIsShow = true;
	m_vUIPos.x = 0.0f;
	m_vUIPos.y = 0.0f;
	D3DXMatrixIdentity(&m_matUIMatrix);

	m_pImage = NULL;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;

	SetRectEmpty(&m_TexRect);		
	GetClientRect(m_hWnd,&m_ClientRect);

	m_fXScale = 1.0f;		//UI的缩放系数，初始值应该为1.0f
	m_fYScale = 1.0f;		//UI的缩放系数，初始值应该为1.0f
}

CUIElement::~CUIElement(void)
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if(m_pSprite)
	{
		m_pSprite->Release();
		m_pSprite = NULL;
	}
}

void CUIElement::InitElement( LPWSTR pFileName, float fxPos , float fyPos,
							 bool bIsShow /* = true */ )
{
	m_pImage = new CLoadImage(m_pDevice);		//new一个CLoadImage类的指针
	m_pImage->InitTexture(pFileName);						//加载图片

	m_vUIPos.x = fxPos;			//给图片的x坐标赋值
	m_vUIPos.y = fyPos;			//给图片的y坐标赋值

	m_fWidth = (float)m_pImage->m_d3dii.Width;		//获取图片的宽
	m_fHeight = (float)m_pImage->m_d3dii.Height;		//获取图片的高

	SetRect(&m_TexRect,0,0,(int)m_fWidth,(int)m_fHeight);
}


void CUIElement::InitElement(LPWSTR pFront , UINT iCount ,LPWSTR pBack ,
							 float fxPos , float fyPos, bool bIsShow /* = true */ )
{
	m_pImage = new CLoadImage(m_pDevice);		//new一个CLoadImage类的指针
	m_pImage->InitTexture(pFront,iCount,pBack);		//加载一组图片

	m_vUIPos.x = fxPos;			//给图片的x坐标赋值
	m_vUIPos.y = fyPos;			//给图片的y坐标赋值

	m_fWidth = (float)m_pImage->m_d3dii.Width;		//获取图片的宽
	m_fHeight = (float)m_pImage->m_d3dii.Height;		//获取图片的高

	SetRect(&m_TexRect,0,0,(int)m_fWidth,(int)m_fHeight);
}

void CUIElement::UILogic(float fElapsedTime)
{

}

void CUIElement::UIRender(float fElapsedTime)
{
	if(m_bIsShow)
	{
		D3DXMatrixTransformation2D(
			&m_matUIMatrix,
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(m_fXScale,m_fYScale),
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(10.0f,0.0f)
			);

		m_pSprite->SetTransform(&m_matUIMatrix);
		m_pSprite->Draw(
			m_pImage->m_pTexture , 
			&m_TexRect,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(123,123,123,234)
			);
	}
}

void CUIElement::HandleProc(HWND hWnd , UINT uMsg , 
							WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_SIZE:
		GetClientRect(m_hWnd,&m_ClientRect);
		m_fXScale =   (float)m_ClientRect.right / m_fWidth ;
		m_fYScale =   (float)m_ClientRect.bottom / m_fHeight ;
		break;
	}

}