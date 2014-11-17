#include "LoadImage.h"

CLoadImage::CLoadImage( LPDIRECT3DDEVICE9 pDevice )
{
	m_pDevcie = pDevice;
	ZeroMemory(&m_d3dii,sizeof(m_d3dii));
}

CLoadImage::~CLoadImage(void)
{
	if(m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CLoadImage::InitTexture(LPWSTR pFileName)
{
	D3DXCreateTextureFromFileEx( 
		m_pDevcie, pFileName , 
		D3DX_FROM_FILE , D3DX_FROM_FILE,
		D3DX_DEFAULT,0,D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,
		D3DX_FILTER_LINEAR,D3DCOLOR_RGBA(255,255,255,255),
		&m_d3dii,NULL,&m_pTexture
		);
}	

void CLoadImage::InitTexture(LPWSTR pFront , UINT iCount ,LPWSTR pBack )
{


}