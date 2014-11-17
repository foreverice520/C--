#include "HunterHP.h"

CHunterHP::CHunterHP(HWND hwnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite):CElement(hwnd,pDevice,pSprite)
{
}

CHunterHP::~CHunterHP(void)
{
}
void CHunterHP::InitHunterHP(LPWSTR pFileName,D3DXVECTOR2 vPos)
{
	D3DXCreateTextureFromFileEx(m_pDevice,pFileName,D3DX_FROM_FILE,D3DX_FROM_FILE,D3DX_DEFAULT,0,D3DFMT_A8B8G8R8,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_ARGB(255,255,255,255),&m_d3dii,NULL,&m_pTexture);
	m_uiHeight=m_d3dii.Height;
	m_uiWidth=m_d3dii.Width;
	m_vCurrentPos=vPos;
	m_uiWidthPerFrame=m_uiWidth/300;
	m_uiHeightPerFrame=m_uiHeight;
	for (UINT i=0;i<300;++i)
	{
		RECT * pRect=new RECT;
		SetRectEmpty(pRect);
		SetRect(pRect,0,0,m_uiWidthPerFrame*i,m_uiHeightPerFrame);
		m_HPVector.push_back(pRect);
	}
	m_HPIter=m_HPVector.begin();
}
void CHunterHP::HunterHPLogic(float fElapsedTime)
{

}
void CHunterHP::HunterHPRender(float fElapsedTime,CHunter * pHunter)
{
	D3DXMatrixTransformation2D(&m_Matrix,&D3DXVECTOR2(0.0f,0.0f),0.0f,&D3DXVECTOR2(1.0f,1.0f),&D3DXVECTOR2(0.0f,0.0f),0.0f,&m_vCurrentPos);
	m_pSprite->SetTransform(&m_Matrix);
	m_HPIter=m_HPVector.begin();
	m_HPIter+=pHunter->GetHP()-1;
	m_pSprite->Draw(m_pTexture,(*m_HPIter),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));	
	
}