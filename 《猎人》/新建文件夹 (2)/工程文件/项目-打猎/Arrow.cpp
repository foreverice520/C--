#include "Arrow.h"

CArrow::CArrow(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite ,float fVelocity,ArrowState state):
CElement(hWnd,pDevice,pSprite)
{
	ZeroMemory(&m_vRotaCenter,sizeof(m_vRotaCenter));
	m_fRotaAngle = 0.0f;

	m_fVelocity = fVelocity;			// 小球发射速度的初速度
	m_fVelocityX = 0.0f;			// 小球在X方向的速度
	m_fVelocityY = 0.0f;			// 小球在Y方向的速度
	m_fAngle = 0.0f;				// 小球发射瞬间的角度
	m_fGrivate = 2.0f;			// 小球收到的重力

	m_ArrowState = state;
	m_bIsRota = true;
}

CArrow::~CArrow(void)
{
	SAFE_RELEASE(m_pTexture);
}

bool CArrow::IsIntersect( CBird * pBird )
{
	static RECT temp = { 0,0,0,0 };
	if(		IntersectRect(&temp,&m_CurrentRect, pBird->GetCurrentRect())	 )
		return true;		//发生碰撞
	else
		return false;

}
void CArrow::ArrowLogic(float fElapsedTime, CHunter * pHunter)
{
	switch(m_ArrowState)
	{
	case AS_IDLE:
		if( GetAsyncKeyState(VK_SPACE) & 0x8000 )
		{
			m_fVelocityX = m_fVelocity * cos(m_fAngle);
			m_fVelocityY = m_fVelocity * sin(m_fAngle);
			m_ArrowState = AS_NONINTERSECT;
			m_bIsRota=false;
		}
		break;
	case AS_NONINTERSECT:
		fElapsedTime *= 10.0f;
		m_vCurrentPos.x = m_vCurrentPos.x + m_fVelocityX * fElapsedTime;
		m_fVelocityY = m_fVelocityY + m_fGrivate * fElapsedTime;
		m_vCurrentPos.y = m_vCurrentPos.y + m_fVelocityY * fElapsedTime;
		break;
	case AS_INTERSECT:
		/*m_fVelocityY = abs(m_fVelocityY) + 5.0f;
		m_vCurrentPos.y = m_vCurrentPos.y + m_fVelocityY * fElapsedTime;*/
		m_ArrowState=AS_IDLE;
		m_bIsRota=true;
		break;
	}

	//--------每次更新小球在屏幕上的矩形区域的信息--------
	SetRect(&m_CurrentRect,(int)m_vCurrentPos.x , (int)m_vCurrentPos.y , 
		int(m_vCurrentPos.x+m_uiWidth) ,int(m_vCurrentPos.y+m_uiHeight) );

	if(m_vCurrentPos.x >= m_ClientRect.right - m_ClientRect.left  || 
		m_vCurrentPos.y >= m_ClientRect.bottom - m_ClientRect.top||
		m_vCurrentPos.x + m_uiWidth<= m_ClientRect.left    ||
		m_vCurrentPos.y + m_uiHeight<= m_ClientRect.top )
	{
		m_vCurrentPos.x = (pHunter->GetCurrentpos()).x-10;
		m_vCurrentPos.y=(pHunter->GetCurrentpos()).y-50;
		m_ArrowState = AS_IDLE;
		m_bIsRota=true;
	}


	if( (GetAsyncKeyState(VK_UP) & 0x8000)&&m_bIsRota)
		m_fRotaAngle-=fElapsedTime;
	if( (GetAsyncKeyState(VK_DOWN) & 0x8000)&&m_bIsRota )
		m_fRotaAngle+=fElapsedTime;
	if( (GetAsyncKeyState(VK_LEFT) & 0x8000 )&&m_vCurrentPos.x>-10 )
		m_vCurrentPos.x-=5;
	if( (GetAsyncKeyState(VK_RIGHT) & 0x8000) &&m_vCurrentPos.x<955 )
		m_vCurrentPos.x+=5;
}

void CArrow::ArrowRender(float fElapsedTime)
{
	if(m_bIsShow)
	{
		D3DXMatrixTransformation2D(&m_Matrix,
			NULL,		
			0.0f,			
			&D3DXVECTOR2(1.0f,1.0f),
			&m_vRotaCenter,
			m_fRotaAngle,
			&m_vCurrentPos
			);

		m_pSprite->SetTransform(&m_Matrix);

		m_pSprite->Draw(m_pTexture,NULL,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(255,255,255,255));
	}

}
