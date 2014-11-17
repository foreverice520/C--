#include "UIBackGround.h"

CUIBackGround::CUIBackGround(HWND hWnd ,LPDIRECT3DDEVICE9 pDevice):
CUIElement( hWnd , pDevice )
{
}

CUIBackGround::~CUIBackGround(void)
{
}

void CUIBackGround::SetScale()
{
	m_fXScale =   (float)m_ClientRect.right / m_fWidth ;
	m_fYScale =   (float)m_ClientRect.bottom / m_fHeight ;
}

void CUIBackGround::UIRender(float fElapsedTime)
{
	if(m_bIsShow)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMatrixTransformation2D(
			&m_matUIMatrix,
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(m_fXScale,m_fYScale),
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(0.0f,0.0f)
			);

		m_pSprite->SetTransform(&m_matUIMatrix);
		m_pSprite->Draw(
			m_pImage->m_pTexture , 
			&m_TexRect,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(255,123,123,234)
			);
		m_pSprite->End();
	}
}

