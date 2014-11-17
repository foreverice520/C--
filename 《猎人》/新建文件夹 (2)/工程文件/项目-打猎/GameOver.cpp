#include "GameOver.h"

CGameOver::CGameOver(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, 
						 LPD3DXSPRITE pSprite ):
CElement(hWnd,pDevice,pSprite)
{
}

CGameOver::~CGameOver(void)
{
}
void CGameOver::Render(float fElapsedTime)
{
	if(m_bIsShow)
	{
		D3DXMatrixTransformation2D(&m_Matrix,
			NULL,		
			0.0f,			
			&D3DXVECTOR2(1.7f,1.5f),
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&m_vCurrentPos
			);

		m_pSprite->SetTransform(&m_Matrix);

		m_pSprite->Draw(m_pTexture,NULL,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(255,255,255,255));
	}
}