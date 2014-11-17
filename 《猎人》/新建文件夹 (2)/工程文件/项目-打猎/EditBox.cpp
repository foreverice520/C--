#include "EditBox.h"

CEditBox::CEditBox(HWND hWnd , LPDIRECT3DDEVICE9 pDevice):
CUIElement(hWnd,pDevice)
{
	m_pText = new CText(pDevice);	//创建字体类的指针
	m_pCursor = new CCursor(hWnd,pDevice);		//创建光标类的指针
	m_InputStr.clear();		//清空变量中的内容
	m_Password.clear();	//清空变量中的内容
	m_MaxCount = 15;		//最多支持15个字符
	m_state = -1	;				//由于该变量0、1都有特定的含义，所以初始化为-1
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
	//====加载光标所对应的图片====
	m_pCursor->InitElement(L"res\\UI\\Cursor.jpg",m_vUIPos.x+3,m_vUIPos.y+4);	
	m_state = state;		//获取当前编辑框的类型
	if( m_state == 1 )	//密码状态
	{
		m_pCursor->Hide();					//隐藏光标
		wstring str = L"请输入密码";	//设置编辑框初始的内容
		m_pText->InitText(m_vUIPos.x+5 , m_vUIPos.y+2 ,str  );	
	}
	else	if( m_state == 0 )	//非密码状态
	{
		wstring str = L"请输入账号名";
		m_pText->InitText(m_vUIPos.x+5 , m_vUIPos.y+2 ,str  );	
	}
}

void CEditBox::UILogic(float fElapsedTime)
{
	m_pCursor->UILogic(fElapsedTime);		//由于CCursor类对象已经作为CEditBox类的
	//成员,我们要手动调用CCursor类的逻辑循环
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
			&D3DXVECTOR2(1.0f,1.0f),								//控制缩放
			&D3DXVECTOR2(0.0f,0.0f),
			0.0f,
			&D3DXVECTOR2(m_vUIPos.x,m_vUIPos.y)		//控制平移
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

		//============实现光标的绘制===================
		m_pCursor->UIRender(fElapsedTime);

		//============实现字体的绘制===================
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
		case VK_TAB:		//消息的拦截，防止按下tab键，它的ASCII码
			//被添加到m_InputStr中
			break;
		case VK_BACK:				//退格键
			//如果 m_InputStr不为空 &&		当前编辑框为激活状态
			if(   !m_InputStr.empty()   &&	m_pCursor->m_bIsShow)
			{
				m_InputStr.erase(m_InputStr.end()-1);	//移除m_InputStr中的最后一个字符

				if(m_state==0)			//按下退格键时账号的删除方法
				{
					m_pText->SetContent(m_InputStr);	//将修改后的m_InputStr中的内容显示出来
				}
				else if(m_state == 1)	//按下退格键时密码的删除方法
				{
					if( !m_Password.empty() )	//判断m_Password不为空，才能删除一个“*”
					{
						m_Password.erase(m_Password.end()-1);	//移除一个“*”
						m_pText->SetContent(m_Password);	//显示剩下的“*”
					}
				}
				m_pCursor->SetCursorPos(-8);	//将当前光标左移8个像素
			}
			break;		
		case VK_LEFT:				//左箭头
			break;
		case VK_RIGHT:				//右箭头
			break;
		default:								//其他键
			//如果当前光标是“显示”状态 && 字符串长度<=可容纳字符的最大个数
			if( m_pCursor->m_bIsShow && m_InputStr.length()<=m_MaxCount )		//账号输入框
			{
				m_InputStr += (WCHAR)wParam;			//获取用户的输入
				if(m_state == 0)									//如果当前编辑框是账号编辑框
				{
					m_pText->SetContent(m_InputStr);		//将用户的输入传递到CText类中，
					//修改要显示的内容
				}
				else if(m_state == 1)		//如果当前编辑框是密码编辑框
				{
					m_Password.append(L"*");//每按下一个键，向m_Password中添加一个“*”
					m_pText->SetContent(m_Password);	//设置显示的内容
				}
				m_pCursor->SetCursorPos(8);		//修改光标的位置，参数为8个像素
			}
		}
	}

}