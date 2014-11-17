#include "Element.h"

CElement::CElement(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, 
				   LPD3DXSPRITE pSprite ):
m_pDevice(pDevice),
m_pSprite(pSprite)
{
	m_hWnd = hWnd;

	m_pTexture = NULL;
	ZeroMemory(&m_d3dii,sizeof(m_d3dii));
	m_uiWidth = 0;
	m_uiHeight = 0;
	m_vPos.x=0;
	m_vPos.y=0;
	m_vCurrentPos.x=0;
	m_vCurrentPos.y=0;

	m_Rows=0;
	m_Cols=0;	

	m_uiWidthPerFrame=0;
	m_uiHeightPerFrame=0;

	ZeroMemory(&m_vInitPos,sizeof(m_vInitPos));
	ZeroMemory(&m_vCurrentPos,sizeof(m_vCurrentPos));
	/*m_bIsShow = true;*/

	D3DXMatrixIdentity(&m_Matrix);		//矩阵单位化

	GetClientRect(m_hWnd,&m_ClientRect);

	SetRectEmpty(&m_CurrentRect);
	m_fFrameSpeed=0.0f;
	m_Move=0;
}

CElement::~CElement(void)
{
	SAFE_RELEASE(m_pTexture);
}

void CElement::InitElement( LPWSTR pFileName , D3DXVECTOR2 vInitPos , bool bIsShow /* = true */ )
{
	D3DXCreateTextureFromFileEx(		//获取纹理图片指针
		m_pDevice,						//设备指针
		pFileName,						//纹理路径及文件名
		D3DX_FROM_FILE,			//纹理宽度与图片宽度相同
		D3DX_FROM_FILE,			//纹理高度与图片高度相同
		D3DX_DEFAULT,				//图片的图层，一般用D3DX_DEFAULT
		0,										//设定纹理的使用方法,默认为0就可以
		D3DFMT_A8R8G8B8,		//当前纹理的格式
		D3DPOOL_MANAGED,	//纹理数据存储位置，MANAGED为系统自动管理
		D3DX_FILTER_LINEAR,	//图像像素的过滤方式,线性过滤即可
		D3DX_FILTER_LINEAR,	//多级渐进纹理像素过滤方式,线性过滤即可
		D3DCOLOR_RGBA(0,0,0,0),	
		&m_d3dii,							//当前这张纹理图片的详细信息
		NULL,								//纹理调色板信息，为NULL既可
		&m_pTexture					//返回的纹理指针
		);
	m_uiWidth = m_d3dii.Width;
	m_uiHeight = m_d3dii.Height;

	m_vInitPos = vInitPos;
	m_vCurrentPos = vInitPos;

	m_bIsShow = bIsShow;

	//-----初始化当前物体在屏幕的矩形位置信息-----
	/*SetRect(&m_CurrentRect,(int)m_vCurrentPos.x , (int)m_vCurrentPos.y , 
		int(m_vCurrentPos.x+m_uiWidth) ,int(m_vCurrentPos.y+m_uiHeight) );*/
}

void CElement::Logic(float fElapsedTime)
{

}

void CElement::Render(float fElapsedTime)
{
	if(m_bIsShow)
	{
		D3DXMatrixTransformation2D(&m_Matrix,
			NULL,		
			0.0f,			
			&D3DXVECTOR2(1.0f,1.0f),
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

void CElement::HandleMessage(HWND hWnd ,UINT uMsg , 
							 WPARAM wParam ,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	}
}
