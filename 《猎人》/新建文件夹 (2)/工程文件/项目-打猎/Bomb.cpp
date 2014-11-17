#include "Bomb.h"

CBomb::CBomb(HWND hWnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite):CElement(hWnd,pDevice,pSprite)
{
	m_bIsShow=false;
	m_fVelocity=100.0f;			// 小球发射速度的初速度
	m_fGrivate=10.0f;			// 小球收到的重力


	m_BombState=BS_NONINTERSECT;		//小球的状态
	m_bIsHurt=false;
}

CBomb::~CBomb(void)
{
	SAFE_RELEASE(m_pTexture);
}
void CBomb::InitBombTexture(LPWSTR pFileName,UINT row,UINT col,CBird * pBird,float fFramSpeed)
{
	m_pBird=pBird;
	D3DXCreateTextureFromFileEx(m_pDevice,pFileName,D3DX_FROM_FILE,D3DX_FROM_FILE,D3DX_DEFAULT,0,D3DFMT_A8B8G8R8,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_ARGB(255,255,255,255),&m_d3dii,NULL,&m_pTexture);
	m_uiHeight=m_d3dii.Height;
	m_uiWidth=m_d3dii.Width;
	m_vCurrentPos=pBird->GetCurrentPos();
	m_fFrameSpeed=fFramSpeed;
	m_Rows=row;
	m_Cols=col;
	m_uiWidthPerFrame=m_uiWidth/m_Cols;
	m_uiHeightPerFrame=m_uiHeight/m_Rows;
	for (UINT i=0;i<row;++i)
	{
		for (UINT j=0;j<col;++j)
		{
			RECT * pRect=new RECT;
			SetRectEmpty(pRect);
			SetRect(pRect,m_uiWidthPerFrame*j,m_uiHeightPerFrame*i,m_uiWidthPerFrame*(j+1),m_uiHeightPerFrame*(i+1));
			m_FrameList.push_back(pRect);
		}	
	}
	m_iter=m_FrameList.begin();
}
void CBomb::BombLogic(float fElapsedTime)
{
	D3DXVECTOR2 TempPos;
	TempPos.x=100.0f+float(rand()%800);
	if (m_vCurrentPos.x<=(TempPos.x+5.0f)&&m_vCurrentPos.x>=(TempPos.x-5.0f))
	{
		m_bIsShow=true;
	}
	if (m_bIsShow)
	{
		switch(m_BombState)
		{
		case BS_NONINTERSECT:
			fElapsedTime *= 1.5f;
			if (m_vCurrentPos.y<580)
			{
				m_fVelocity=m_fVelocity+m_fGrivate*0.07f;
				m_vCurrentPos.y=m_vCurrentPos.y+m_fVelocity*0.07f;
			}
			else
			{
				m_BombState=BS_BLAST;
				m_fVelocity=100.0f;
			}
			break;
	   case BS_INTERSECT:
		   m_bIsShow=false;
		   m_BombState=BS_NONINTERSECT;
		   break;
		}

		SetRect(&m_CurrentRect,(int)m_vCurrentPos.x , (int)m_vCurrentPos.y , 
			int(m_vCurrentPos.x+m_uiWidthPerFrame) ,int(m_vCurrentPos.y+m_uiHeightPerFrame) );
		/*SetRect(&m_CurrentRect,(int)m_vCurrentPos.x+m_uiWidthPerFrame/4 , (int)m_vCurrentPos.y+m_uiHeightPerFrame/4 , 
			int(m_vCurrentPos.x+m_uiWidthPerFrame/2) ,int(m_vCurrentPos.y+m_uiHeightPerFrame/2) );*/
	}
	else
	{
		m_vCurrentPos=m_pBird->GetCurrentPos();
	}
}
void CBomb::BombRender(float fElapsedTime)
{
	/*static float fTime=0;
	fTime+=fElapsedTime;*/
	D3DXMatrixTransformation2D(&m_Matrix,&D3DXVECTOR2(0.0f,0.0f),0.0f,&D3DXVECTOR2(1.0f,1.0f),&D3DXVECTOR2(0.0f,0.0f),0.0f,&m_vCurrentPos);
	m_pSprite->SetTransform(&m_Matrix);
	if (m_bIsShow)
	{
		if (m_vCurrentPos.y<=400)
		{
			m_iter=m_FrameList.begin();
			m_pSprite->Draw(m_pTexture,(*m_iter),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
		}
		if (m_vCurrentPos.y<=500&&m_vCurrentPos.y>400)
		{
			m_iter=m_FrameList.begin();
			m_iter++;
			m_pSprite->Draw(m_pTexture,(*m_iter),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
			m_iter=m_FrameList.begin();
		}
		if (m_vCurrentPos.y<580&&m_vCurrentPos.y>500)
		{
			m_iter=m_FrameList.begin();
			m_iter++;
			m_iter++;
			m_pSprite->Draw(m_pTexture,(*m_iter),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
			m_iter=m_FrameList.begin();
			m_iter+=8;
		}
		if (m_BombState==BS_BLAST)
		{
			if (m_iter!=m_FrameList.end())
			{
				m_pSprite->Draw(m_pTexture,(*m_iter),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
				/*if (fTime>m_fFrameSpeed)
				{*/
					++m_iter;
					/*fTime=0;*/
				/*}*/
			} 
			else
			{
				m_bIsShow=false;
				m_bIsHurt=false;
				m_vCurrentPos=m_pBird->GetCurrentPos();
				m_BombState =BS_NONINTERSECT;
			}
		}
	}
}
void CBomb::BombHandleMessage(HWND hWnd ,UINT uMsg , WPARAM wParam ,LPARAM lParam)
{

}