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

	D3DXMatrixIdentity(&m_Matrix);		//����λ��

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
	D3DXCreateTextureFromFileEx(		//��ȡ����ͼƬָ��
		m_pDevice,						//�豸ָ��
		pFileName,						//����·�����ļ���
		D3DX_FROM_FILE,			//��������ͼƬ�����ͬ
		D3DX_FROM_FILE,			//����߶���ͼƬ�߶���ͬ
		D3DX_DEFAULT,				//ͼƬ��ͼ�㣬һ����D3DX_DEFAULT
		0,										//�趨�����ʹ�÷���,Ĭ��Ϊ0�Ϳ���
		D3DFMT_A8R8G8B8,		//��ǰ����ĸ�ʽ
		D3DPOOL_MANAGED,	//�������ݴ洢λ�ã�MANAGEDΪϵͳ�Զ�����
		D3DX_FILTER_LINEAR,	//ͼ�����صĹ��˷�ʽ,���Թ��˼���
		D3DX_FILTER_LINEAR,	//�༶�����������ع��˷�ʽ,���Թ��˼���
		D3DCOLOR_RGBA(0,0,0,0),	
		&m_d3dii,							//��ǰ��������ͼƬ����ϸ��Ϣ
		NULL,								//�����ɫ����Ϣ��ΪNULL�ȿ�
		&m_pTexture					//���ص�����ָ��
		);
	m_uiWidth = m_d3dii.Width;
	m_uiHeight = m_d3dii.Height;

	m_vInitPos = vInitPos;
	m_vCurrentPos = vInitPos;

	m_bIsShow = bIsShow;

	//-----��ʼ����ǰ��������Ļ�ľ���λ����Ϣ-----
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
