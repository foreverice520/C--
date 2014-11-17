#include "Bird.h"

CBird::CBird(HWND hWnd,LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite,UINT move):CElement(hWnd,pDevice,pSprite)
{
	m_Move=move;
	m_fVelocity=10;

	m_bIsRota = false;								//是否旋转
	ZeroMemory(&m_vRotaCenter,sizeof(m_vRotaCenter));		//旋转中心
	m_fVelocityRota = 0.0f;
}

CBird::~CBird(void)
{
	SAFE_RELEASE(m_pTexture);
}
void CBird::InitBird(LPWSTR pFileName, UINT row, UINT col ,D3DXVECTOR2 vPos,float fFrameSpeed /* = 0.04f */ )
{
	D3DXCreateTextureFromFileEx(
		m_pDevice, pFileName , 
		D3DX_FROM_FILE , D3DX_FROM_FILE,
		D3DX_DEFAULT,0,D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,
		D3DX_FILTER_LINEAR,D3DCOLOR_RGBA(255,255,255,255),
		&m_d3dii,NULL,&m_pTexture
		);

	m_vPos = vPos;		//记录帧序列在客户区的位置
	m_fFrameSpeed = fFrameSpeed;

	m_uiWidth = m_d3dii.Width;
	m_uiHeight = m_d3dii.Height;

	m_Rows = row;	
	m_Cols = col;	

	m_uiWidthPerFrame = m_uiWidth/m_Cols;
	m_uiHeightPerFrame = m_uiHeight/m_Rows;	


	for (UINT i=0;i<4;++i)
	{
		RECT * pRect=new RECT;
		SetRectEmpty(pRect);
		SetRect(pRect,m_uiWidthPerFrame*i,0,m_uiWidthPerFrame*(i+1),m_uiHeightPerFrame);
		m_FrameListLeft.push_back(pRect);
	}
	for (UINT i=0;i<4;++i)
	{
		RECT * pRect=new RECT;
		SetRectEmpty(pRect);
		SetRect(pRect,m_uiWidthPerFrame*i,m_uiHeightPerFrame,m_uiWidthPerFrame*(i+1),m_uiHeightPerFrame*2);
		m_FrameListRight.push_back(pRect);
	}
	m_iterLeft=m_FrameListLeft.begin();
	m_iterRight=m_FrameListRight.begin();
}
void CBird::BirdLogic(float fElapsedTime)
{
	switch(m_Move)
	{
	case 0:
		if (m_vPos.x>1000)
		{
			m_vPos.x=float(rand()%150);
			m_vPos.y=float(rand()%300);

		}
		m_vPos.x+=rand()%10;
		break;
	case 1:
		if (m_vPos.x<0)
		{
			m_vPos.x=950+float(rand()%150);
			m_vPos.y=float(rand()%300);
		}
		m_vPos.x-=rand()%10;
		break;
	case 2:
		m_vPos.y+=10;
		if (m_vPos.y>580)
		{
			m_Move=rand()%2;
			m_bIsRota = false;
		}
		break;
	}
	SetRect(&m_CurrentRect,(int)m_vPos.x+m_uiWidthPerFrame/4 , (int)m_vPos.y+m_uiHeightPerFrame/4 , 
		int(m_vPos.x+m_uiWidthPerFrame/2) ,int(m_vPos.y+m_uiHeightPerFrame/2) );
}

void CBird::BirdRender(float fElapsedTime)
{
	if(m_bIsRota)		//如果旋转
	{
		m_fVelocityRota+= fElapsedTime*10;			//旋转角度的增量变化
		m_vRotaCenter.x = float(m_uiWidthPerFrame/2);		//确定旋转中心
		m_vRotaCenter.y = float(m_uiHeightPerFrame/2);
		if(m_bIsShow)
		{
			D3DXMatrixTransformation2D(&m_Matrix,
				NULL,		
				0.0f,			
				NULL,
				&m_vRotaCenter,
				m_fVelocityRota,
				&m_vPos
				);
			m_pSprite->SetTransform(&m_Matrix);
			m_iterRight=m_FrameListRight.begin();
			m_pSprite->Draw(m_pTexture,(*m_iterRight),
				&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DCOLOR_ARGB(255,255,255,255));
		}
	}
	else
	{
		static float fTime = 0.0f;
		fTime+=fElapsedTime;

		D3DXMatrixTransformation2D(	&m_Matrix,&D3DXVECTOR2(0.0f,0.0f),0.0f,&D3DXVECTOR2(1.0f,1.0f),&D3DXVECTOR2(0.0f,0.0f),0.0f,&m_vPos);
		m_pSprite->SetTransform(&m_Matrix);

		switch (m_Move)
		{
		case 0:
			if (m_iterRight!=m_FrameListRight.end()&&m_vPos.y<500)
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
				m_iterRight=m_FrameListRight.begin();
			}
			break;
		case 1:
			if (m_iterLeft!=m_FrameListLeft.end()&&m_vPos.y<500)
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
				m_iterLeft=m_FrameListLeft.begin();
			}
			break;
		case 2:
			m_pSprite->Draw(m_pTexture,(*m_iterLeft),&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_ARGB(255,255,255,255));
			break;
		}	

	}
	
}
void CBird::BirdHandleMessage(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{

}
