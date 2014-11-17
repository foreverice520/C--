#include "EditBox.h"

CEditBox::CEditBox(HWND hWnd , LPDIRECT3DDEVICE9 pDevice):
CUIElement(hWnd,pDevice)
{
	m_pText = new CText(pDevice);	//�����������ָ��
	m_pCursor = new CCursor(hWnd,pDevice);		//����������ָ��
	m_InputStr.clear();		//��ձ����е�����
	m_Password.clear();	//��ձ����е�����
	m_MaxCount = 15;		//���֧��15���ַ�
	m_state = -1	;				//���ڸñ���0��1�����ض��ĺ��壬���Գ�ʼ��Ϊ-1
}


CEditBox::~CEditBox(void)
{
	if(m_pCursor)
	{
		delete m_pCursor;
		m_pCursor = NULL;
	}
	if(m_pText)
	{
		delete m_pText;
		m_pText = NULL;
	}
}
void CEditBox::InitEditBoxText( UINT state )
{
	//====���ع������Ӧ��ͼƬ====
	m_pCursor->InitElement(L"res\\UI\\Cursor.jpg",m_vUIPos.x+3,m_vUIPos.y+4);	
	m_state = state;		//��ȡ��ǰ�༭�������
	if( m_state == 1 )	//����״̬
	{
		m_pCursor->Hide();					//���ع��
		wstring str = L"����������";	//���ñ༭���ʼ������
		m_pText->InitText(m_vUIPos.x+5 , m_vUIPos.y+2 ,str  );	
	}
	else	if( m_state == 0 )	//������״̬
	{
		wstring str = L"�������˺���";
		m_pText->InitText(m_vUIPos.x+5 , m_vUIPos.y+2 ,str  );	
	}
}

void CEditBox::UILogic(float fElapsedTime)
{
	m_pCursor->UILogic(fElapsedTime);		//����CCursor������Ѿ���ΪCEditBox���
	//��Ա,����Ҫ�ֶ�����CCursor����߼�ѭ��
}

void CEditBox::UIRender(float fElapsedTime)
{
	if(m_bIsShow)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMatrixTransformation2D(
			&m_matUIMatrix,
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(1.0f,1.0f),								//��������
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(m_vUIPos.x,m_vUIPos.y)		//����ƽ��
			);

		m_pSprite->SetTransform(&m_matUIMatrix);
		m_pSprite->Draw(
			m_pImage->m_pTexture , 
			&m_TexRect,
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			&D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DCOLOR_ARGB(255,255,255,255)
			);

		m_pSprite->End();

		//============ʵ�ֹ��Ļ���===================
		m_pCursor->UIRender(fElapsedTime);

		//============ʵ������Ļ���===================
		m_pText->Render(fElapsedTime);
	}
}

void CEditBox::HandleProc( HWND hWnd , UINT uMsg , 
						  WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CHAR:
		switch(wParam)
		{
		case VK_RETURN:
			break;
		case VK_TAB:		//��Ϣ�����أ���ֹ����tab��������ASCII��
			//����ӵ�m_InputStr��
			break;
		case VK_BACK:				//�˸��
			//��� m_InputStr��Ϊ�� &&		��ǰ�༭��Ϊ����״̬
			if(   !m_InputStr.empty()   &&	m_pCursor->m_bIsShow)
			{
				m_InputStr.erase(m_InputStr.end()-1);	//�Ƴ�m_InputStr�е����һ���ַ�

				if(m_state==0)			//�����˸��ʱ�˺ŵ�ɾ������
				{
					m_pText->SetContent(m_InputStr);	//���޸ĺ��m_InputStr�е�������ʾ����
				}
				else if(m_state == 1)	//�����˸��ʱ�����ɾ������
				{
					if( !m_Password.empty() )	//�ж�m_Password��Ϊ�գ�����ɾ��һ����*��
					{
						m_Password.erase(m_Password.end()-1);	//�Ƴ�һ����*��
						m_pText->SetContent(m_Password);	//��ʾʣ�µġ�*��
					}
				}
				m_pCursor->SetCursorPos(-8);	//����ǰ�������8������
			}
			break;		
		case VK_LEFT:				//���ͷ
			break;
		case VK_RIGHT:				//�Ҽ�ͷ
			break;
		default:								//������
			//�����ǰ����ǡ���ʾ��״̬ && �ַ�������<=�������ַ���������
			if( m_pCursor->m_bIsShow && m_InputStr.length()<=m_MaxCount )		//�˺������
			{
				m_InputStr += (WCHAR)wParam;			//��ȡ�û�������
				if(m_state == 0)									//�����ǰ�༭�����˺ű༭��
				{
					m_pText->SetContent(m_InputStr);		//���û������봫�ݵ�CText���У�
					//�޸�Ҫ��ʾ������
				}
				else if(m_state == 1)		//�����ǰ�༭��������༭��
				{
					m_Password.append(L"*");//ÿ����һ��������m_Password�����һ����*��
					m_pText->SetContent(m_Password);	//������ʾ������
				}
				m_pCursor->SetCursorPos(8);		//�޸Ĺ���λ�ã�����Ϊ8������
			}
		}
	}

}