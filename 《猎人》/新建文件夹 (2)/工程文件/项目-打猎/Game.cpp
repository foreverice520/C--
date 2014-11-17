#include "Game.h"

CGame::CGame(HWND hWnd):m_hWnd(hWnd)
{
	m_pD3D = NULL;
	m_pDevice = NULL;
	m_pSprite = NULL;

	m_pAccount = NULL;
	m_pPassWord = NULL;
	m_Account = L"1";
	m_Password= L"1";
	m_GameState=1;
}

CGame::~CGame(void)
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D);
}
void CGame::InitD3D()
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE d3ddm;
	ZeroMemory(&d3ddm,sizeof(d3ddm));
	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
		m_hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,&m_pDevice);

	D3DXCreateSprite(m_pDevice,&m_pSprite);
}
void CGame::InitGame()
{
	if (m_GameState==1)
	{
		//===========创建背景==================
		CUIBackGround * pTemp = new CUIBackGround(m_hWnd, m_pDevice);
		pTemp->InitElement(L"res\\UI\\katong_deskTX-1024-768.jpg",0.0f,0.0f);
		pTemp->SetScale();
		CUIManager::GetManager().AddNewUIElement(pTemp);

		//===========创建登陆按钮==================
		m_pLoginButton = new CUIButton(m_hWnd,m_pDevice);
		m_pLoginButton->InitElement(L"res\\UI\\LoginButton",3,L".jpg",320,435);	//加载按钮图片
		m_pLoginButton->SetButtonType(CUIButton::BT_LOGIN);	//设置按钮的类型
		CUIManager::GetManager().AddNewUIElement(m_pLoginButton);

		//===========创建退出按钮==================
		m_pQuitButton = new CUIButton(m_hWnd,m_pDevice);
		m_pQuitButton->InitElement(L"res\\UI\\QuitButton",3,L".jpg",680,550);
		m_pQuitButton->SetButtonType(CUIButton::BT_QUIT);
		CUIManager::GetManager().AddNewUIElement(m_pQuitButton);

		//===========创建账号名编辑框=================
		m_pAccount = new CEditBox(m_hWnd,m_pDevice);
		m_pAccount->InitElement(L"res\\UI\\EditBox.jpg",316.0f,300.0f);
		m_pAccount->InitEditBoxText(0);//  0为"非密码状态”，1为“密码状态”
		CUIManager::GetManager().AddNewUIElement(m_pAccount);

		//===========创建密码编辑框=================
		m_pPassWord= new CEditBox(m_hWnd,m_pDevice);
		m_pPassWord->InitElement(L"res\\UI\\EditBox.jpg",316,355);
		m_pPassWord->InitEditBoxText(1);//  0为"非密码状态”，1为“密码状态”
		CUIManager::GetManager().AddNewUIElement(m_pPassWord);
	}
	if (m_GameState==2)
	{
		//--------------------初始化声音播放系统------------------------
		pFmod = new MyFMod();
		pFmod->InitFMod();

		//-----------------------播放mp3背景音乐-------------------------
		pFmod->LoadStream("res\\031-Castle01.mid");
		pFmod->SetStreamVolume(1.0f);
		pFmod->SetStreamLooping(true);
		pFmod->PlayStream(false);

		/*pFmod->LoadSound("res\\boss_explode.ogg");
		pFmod->SetSoundVolume(0,1.0f);
		pFmod->SetSoundLooping(0,true);
		pFmod->PlaySound(0,false);*/


		m_pBackGround= new CBackGround(m_hWnd,m_pDevice,m_pSprite);
		m_pBackGround->InitElement(L"res\\texture\\katong_deskTX-1024-768.jpg",D3DXVECTOR2(0.0f,0.0f));

		m_pHunterHP=new CHunterHP(m_hWnd,m_pDevice,m_pSprite);
		m_pHunterHP->InitHunterHP(L"res\\texture\\hunterHP.png",D3DXVECTOR2(10,0));

		for (int i=0;i<4;++i)
		{
			CBird * m_pBird1=new CBird(m_hWnd,m_pDevice,m_pSprite,1);
			CBird * m_pBird2=new CBird(m_hWnd,m_pDevice,m_pSprite,0);
			m_pBirdVector.push_back(m_pBird1);
			m_pBirdVector.push_back(m_pBird2);
		}

		for (int i=0;i<8;++i)
		{
			CBomb * m_pBomb=new CBomb(m_hWnd,m_pDevice,m_pSprite);
			m_pBombVector.push_back(m_pBomb);
		}
		m_BirdIter=m_pBirdVector.begin();
		m_BombIter=m_pBombVector.begin();
		for (m_BirdIter;m_BirdIter!=m_pBirdVector.end();++m_BirdIter)
		{
			(*m_BirdIter)->InitBird(L"res\\texture\\074-Bird04.png",2,4,D3DXVECTOR2(float(rand()%999),float(rand()%300)));
			(*m_BombIter)->InitBombTexture(L"res\\texture\\fireblast09anim2.png",4,8,(*m_BirdIter));
			m_BombIter++;
		}

		m_pArrow=new CArrow(m_hWnd,m_pDevice,m_pSprite,100.0f);
		m_pArrow->InitElement(L"res\\texture\\010-Weapon05.png",D3DXVECTOR2(500,550));
		m_pArrow->SetRotationCenter();

		m_pHunter=new CHunter(m_hWnd,m_pDevice,m_pSprite);
		m_pHunter->InitTexture(L"res\\texture\\023-Gunner01.png",3,4,D3DXVECTOR2(512.0f,590.0f),0.05f);
	}
	if (m_GameState==3)
	{
		pGameOver=new CGameOver(m_hWnd,m_pDevice,m_pSprite);
		pGameOver->InitElement(L"res\\texture\\001-Gameover01.jpg",D3DXVECTOR2(0.0f,0.0f));
	}
}
void CGame::GameLogic(float fElapsedTime)
{
	if (m_GameState==1)
	{
		CUIManager::GetManager().Logic(fElapsedTime);

		//==========将用户的账号及密码信息与程序中的进行比对===========
		if( 
			m_pLoginButton->GetButtonState() &&		//登陆按钮是否按下，true为按下
			m_pAccount->GetContent() ==m_Account&&	//比对账号名
			m_pPassWord->GetContent() == m_Password	//比对密码
			)
		{
			MessageBox(NULL,L"恭喜您，登陆成功！",L"",MB_OK);		//说明账号、密码匹配
			m_pLoginButton->m_bIsDown = false;		//修改按钮状态标记为false
			m_GameState=2;
			InitGame();
		}
		else if( m_pLoginButton->GetButtonState() )
		{
			MessageBox(NULL,L"登陆信息错误",L"",MB_OK);
			m_pLoginButton->m_bIsDown = false;		//修改按钮状态标记为false
		}
	} 
	if (m_GameState==2)
	{
		m_BirdIter=m_pBirdVector.begin();
		m_BombIter=m_pBombVector.begin();
		for (m_BirdIter;m_BirdIter!=m_pBirdVector.end();++m_BirdIter)
		{
			(*m_BirdIter)->BirdLogic(fElapsedTime);
			(*m_BombIter)->BombLogic(fElapsedTime);
			m_BombIter++;
		}
		m_BirdIter=m_pBirdVector.begin();
		for( m_BirdIter ; m_BirdIter!= m_pBirdVector.end(); ++m_BirdIter )
		{

			if(( m_pArrow->IsIntersect( (CBird *)(*m_BirdIter) ) )&&((*m_BirdIter)->GetBirdMove()!=2))
			{
				m_pArrow->SetState(AS_INTERSECT);
				m_pArrow->SetPos(m_pHunter);

				(/*(CBird *)*/(*m_BirdIter))->SetBirdStateDown();
				(/*(CBird *)*/(*m_BirdIter))->SetRota();
				break;
			}
		}

		m_pArrow->GetAngle(m_pArrow->GetRotaAngle()+4.7f);
		m_pArrow->ArrowLogic(fElapsedTime,m_pHunter);

		m_pHunter->HunterLogic(fElapsedTime);

		m_BombIter=m_pBombVector.begin();
		for (m_BombIter;m_BombIter!=m_pBombVector.end();++m_BombIter)
		{
			//if ((*m_BombIter)->GetCurrentRect()->bottom>580)
			//{
			//	//-----------------------播放ogg音效---------------------------------
			//	pFmod->LoadSound("res\\boss_explode.ogg");
			//	pFmod->SetSoundVolume(0,1.0f);
			//	pFmod->SetSoundLooping(0,true);
			//	pFmod->PlaySound(0,false);
			//}
			if (m_pHunter->IsIntersect(*m_BombIter)&&((*m_BombIter)->GetBombState()==BS_BLAST)&&!((*m_BombIter)->GetIsHurt()))
			{
				m_pHunter->ComputeHP();
				(*m_BombIter)->SetIsHurtTrue();
				if (m_pHunter->GetHP()<=0)
				{
					MessageBox(m_hWnd,L"猎人被炸死,你输了!",L"",MB_OK);
					m_GameState=3;
					InitGame();
					break;
				}
			}
		}
	}
}
void CGame::GameRender(float fElapsedTime)
{
	m_BirdIter=m_pBirdVector.begin();
	m_BombIter=m_pBombVector.begin();
	m_pDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(234,123,234),1.0f,0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (m_GameState==1)
	{
		CUIManager::GetManager().Render(fElapsedTime);
	}
	if (m_GameState==2)
	{
		m_pBackGround->Render(fElapsedTime);
		m_pHunterHP->HunterHPRender(fElapsedTime,m_pHunter);

		for (m_BirdIter;m_BirdIter!=m_pBirdVector.end();++m_BirdIter)
		{
			(*m_BirdIter)->BirdRender(fElapsedTime);
			(*m_BombIter)->BombRender(fElapsedTime);
			m_BombIter++;
		}

		m_pArrow->ArrowRender(fElapsedTime);
		m_pHunter->HunterRender(fElapsedTime);
	}
	if (m_GameState==3)
	{
		pGameOver->Render(fElapsedTime);
	}

	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(NULL,NULL,NULL,NULL);
}
void CGame::HandleMessage(HWND hWnd ,UINT uMsg,WPARAM wParam ,LPARAM lParam)
{
	if (m_GameState)
	{
		CUIManager::GetManager().HandleProc(hWnd,uMsg,wParam,lParam);
		switch(uMsg)
		{
		case WM_CHAR:
			switch(wParam)
			{
			case VK_TAB:
				m_pAccount->m_pCursor->m_bIsShow = !m_pAccount->m_pCursor->m_bIsShow;	//按下TAB时修改账号名编辑框光标的状态
				m_pPassWord->m_pCursor->m_bIsShow = !m_pPassWord->m_pCursor->m_bIsShow;	//按下TAB时修改密码编辑框光标的状态
				break;
			case VK_RETURN:
				if( 
					m_pAccount->GetContent() == m_Account&&
					m_pPassWord->GetContent() == m_Password
					)
				{
					MessageBox(NULL,L"恭喜您，登陆成功！",L"",MB_OK);
					m_GameState=2;
					InitGame();
				}
				else
				{
					MessageBox(NULL,L"登陆信息错误",L"",MB_OK);
				}
				break;
			}
		}
	}	
}
