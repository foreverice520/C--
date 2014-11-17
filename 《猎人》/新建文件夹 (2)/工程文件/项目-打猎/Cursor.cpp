#include "Cursor.h"

CCursor::CCursor(HWND hWnd , LPDIRECT3DDEVICE9 pDevice):
CUIElement(hWnd,pDevice)
{
	m_alpha = 255;
}

CCursor::~CCursor(void)
{
}

void CCursor::SetCursorPos(short Amount )
{
	m_vUIPos.x+=Amount;
}

void CCursor::UILogic(float fElapsedTime)
{
	static float fTime = 0.0f;
	fTime+=fElapsedTime;
	m_alpha = (unsigned char)(127.0f*sin( 10.0f * fTime )+127.0f);
}

void CCursor::UIRender(float fElapsedTime)
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
			&D3DXVECTOR2(m_vUIPos.x,m_vUIPos.y)
			);

		m_pSprite->SetTransform(&m_matUIMatrix);
		m_pSprite->Draw(
			m_pImage->m_pTexture , 
			&m_TexRect,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(m_alpha,255,255,0)
			);

		m_pSprite->End();
	}
}