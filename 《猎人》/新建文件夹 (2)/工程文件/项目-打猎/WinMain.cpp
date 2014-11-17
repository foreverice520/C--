#include<Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")
#include<time.h>
#include"Game.h"
HWND hWnd;
HINSTANCE hInst;	//一个全局的应用程序实例句柄
RECT WindowRect;
RECT ClientRect;
CGame * g_pGame=NULL;
void InitGame()		//初始化游戏
{
	g_pGame = new CGame(hWnd);
	g_pGame->InitD3D();
	g_pGame->InitGame();
}

void GameLogic(float fElapsedTime)	//游戏逻辑循环
{
	g_pGame->GameLogic(fElapsedTime);
}

void GameRender(float fElapsedTime)		//游戏渲染循环
{
	g_pGame->GameRender(fElapsedTime);
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	WNDCLASS wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance=hInstance;
	wc.lpfnWndProc=WndProc;
	wc.lpszClassName=L"999999999";
	wc.lpszMenuName=NULL;
	wc.style=CS_HREDRAW|CS_VREDRAW;
	RegisterClass(&wc);
	hWnd=CreateWindow(wc.lpszClassName,L"打猎",WS_OVERLAPPEDWINDOW,100,30,1024,700,NULL,NULL,hInstance,NULL);
	if (hWnd)
	{
		ShowWindow(hWnd,SW_NORMAL);
		UpdateWindow(hWnd);
	}
	else
	{
		MessageBox(NULL,L"CreateWindow Error",L"",MB_OK);
		return 0;
	}
	/*g_pGame = new CGame(hWnd);
	g_pGame->InitD3D();
	g_pGame->InitGame();*/
	InitGame();
	MSG uMsg;
	ZeroMemory(&uMsg,sizeof(uMsg));
	while (uMsg.message!=WM_QUIT)
	{
		if (PeekMessage(&uMsg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		else
		{
			static DWORD FPS = 60;
			static DWORD dwTime = timeGetTime();
			DWORD dwCurrentTime = timeGetTime();
			DWORD dwElapsedTime = dwCurrentTime - dwTime;
			float fElapsedTime = (float)dwElapsedTime*0.001f;
			//----------------------------------------------------	
			/*g_pGame->*/GameLogic(fElapsedTime);
			/*g_pGame->*/GameRender(fElapsedTime);
			//----------------------------------------------------
			if( dwElapsedTime < 1000/FPS )
			{
				Sleep( 1000/FPS - dwElapsedTime );
			}
			dwTime = dwCurrentTime;
		}
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if(g_pGame)
		g_pGame->HandleMessage(hWnd,uMsg,wParam,lParam);
	switch(uMsg)
	{
	case WM_CREATE:
		srand((unsigned)time(NULL));
	case WM_PAINT:
		break;
	case WM_KEYDOWN:
		if(wParam==VK_ESCAPE)
			DestroyWindow(hWnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		if(g_pGame)
		{
			delete g_pGame;
			g_pGame = NULL;
		}
		PostQuitMessage(0);
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}