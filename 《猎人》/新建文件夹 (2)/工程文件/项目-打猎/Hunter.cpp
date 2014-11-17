#include "Hunter.h"

CHunter::CHunter(HWND hwnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite):CElement(hwnd,pDevice,pSprite)
{
	m_vCurrentPos.x=512;
	m_vCurrentPos.y=590;
	m_HunterHP=300;
	/*m_HunterState=1;*/
	
}

CHunter::~CHunter(void)
{
	SAFE_RELEASE(m_pTexture);
}
UINT CHunter::GetHP()
{
	return m_HunterHP;
}
void CHunter::InitTexture(LPWSTR pFileName,UINT row,UINT col,D3DXVECTOR2 vPos,float fFramSpeed/* =0.04f */)
{
	D3DXCreateTextureFromFileEx(m_pDevice,pFileName,D3DX_FROM_FILE,D3DX_FROM_FILE,D3DX_DEFAULT,0,D3DFMT_A8B8G8R8,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_ARGB(255,255,255,255),&m_d3dii,NULL,&m_pTexture);
	m_uiHeight=m_d3dii.Height;
	m_uiWidth=m_d3dii.Width;
	m_vCurrentPos=vPos;
	m_fFrameSpeed=fFramSpeed;
	m_Rows=row;
	m_Cols=col;
	m_uiWidthPerFrame=m_uiWidth/m_Cols;
	m_uiHeightPerFrame=m_uiHeight/m_Rows;
	for (UINT i=0;i<4;++i)
	{
		RECT * pRect=new RECT;
		SetRectEmpty(pRect);
		SetRect(pRect,m_uiWidthPerFrame*i,0,m_uiWidthPerFrame*(i+1),m_uiHeightPerFrame);
		m_FramListLeft.push_back(pRect);
	}
	for (UINT i=0;i<4;++i)
	{
		RECT * pRect=new RECT;
		SetRectEmpty(pRect);
		SetRect(pRect,m_uiWidthPerFrame*i,m_uiHeightPerFrame,m_uiWidthPerFrame*(i+1),m_uiHeightPerFrame*2);
		m_FramListRight.push_back(pRect);
	}
	for (UINT i=0;i<4;++i)
	{
		RECT * pRect=new RECT;
		SetRectEmpty(pRect);
		SetRect(pRect,m_uiWidthPerFrame*i,m_uiHeightPerFrame*2,m_uiWidthPerFrame*(i+1),m_uiHeightPerFrame*3);
		m_FramListUp.push_back(pRect);
	}
	m_iterUp=m_FramListUp.begin();
	m_iterLeft=m_FramListLeft.begin();
	m_iterRight=m_FramListRight.begin();
	/*m_pSprite->Draw(m_pTexture,(*m_iterUp),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));*/
}

bool CHunter::IsIntersect( CBomb * pBomb)
{
	static RECT temp = { 0,0,0,0 };
	if(		IntersectRect(&temp,&m_CurrentRect,pBomb->GetCurrentRect())	 )
		return true;		//·¢ÉúÅö×²
	else
		return false;

}
void CHunter::ComputeHP(/*CBomb * pBomb*/)
{
	/*static RECT temp = { 0,0,0,0 };
	IntersectRect(&temp,&m_CurrentRect, pBomb->GetCurrentRect())	; 
	UINT area=(temp.bottom-temp.top)*(temp.right-temp.left);
	m_HunterHP=m_HunterHP*(1-area/(m_uiWidthPerFrame*m_uiHeightPerFrame));*/
	m_HunterHP-=10;

}
void CHunter::HunterLogic(float fElapsedTime)
{
	if( (GetAsyncKeyState(VK_LEFT) & 0x8000) &&m_vCurrentPos.x>0)
	{
		m_vCurrentPos.x-=5;
	}
	if( (GetAsyncKeyState(VK_RIGHT) & 0x8000) && m_vCurrentPos.x<970 )
	{
		m_vCurrentPos.x+=5;
	}

	/*SetRect(&m_CurrentRect,(int)m_vCurrentPos.x+m_uiWidthPerFrame/4 , (int)m_vCurrentPos.y+m_uiHeightPerFrame/4 , 
		int(m_vCurrentPos.x+m_uiWidthPerFrame/2) ,int(m_vCurrentPos.y+m_uiHeightPerFrame/2) );*/

	SetRect(&m_CurrentRect,(int)m_vCurrentPos.x , (int)m_vCurrentPos.y , 
		int(m_vCurrentPos.x+m_uiWidthPerFrame) ,int(m_vCurrentPos.y+m_uiHeightPerFrame) );
}
void CHunter::HunterRender(float fElapsedTime)
{
	static float fTime=0;
	fTime+=fElapsedTime;
	D3DXMatrixTransformation2D(&m_Matrix,&D3DXVECTOR2(0.0f,0.0f),0.0f,&D3DXVECTOR2(1.0f,1.0f),&D3DXVECTOR2(0.0f,0.0f),0.0f,&m_vCurrentPos);
	m_pSprite->SetTransform(&m_Matrix);
	if (( GetAsyncKeyState(VK_DOWN) & 0x8000 )||(( GetAsyncKeyState(VK_UP) & 0x8000 )||!( GetAsyncKeyState(VK_LEFT) & 0x8000 )&!( GetAsyncKeyState(VK_RIGHT) & 0x8000 )))
	{
		m_pSprite->Draw(m_pTexture,(*m_iterUp),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
	} 
	else
	{
		if( GetAsyncKeyState(VK_LEFT) & 0x8000 )
		{

			if (m_iterLeft!=m_FramListLeft.end())
			{
				m_pSprite->Draw(m_pTexture,(*m_iterLeft),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
				if (fTime>m_fFrameSpeed)
				{
					++m_iterLeft;
					fTime=0;
				}
			} 
			else
			{
				m_iterLeft=m_FramListLeft.begin();
			}
		}

		if( GetAsyncKeyState(VK_RIGHT) & 0x8000 )
		{

			if (m_iterRight!=m_FramListRight.end())
			{
				m_pSprite->Draw(m_pTexture,(*m_iterRight),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
				if (fTime>m_fFrameSpeed)
				{
					++m_iterRight;
					fTime=0;
				}
			} 
			else
			{
				m_iterRight=m_FramListRight.begin();
			}
		}
	}
}
void CHunter::HandleMessage(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{

}
