/*
		DESC:  该类的功能为加载资源图片
*/
#pragma once
#ifndef		CLoadImage_H_
#define    CLoadImage_H_
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")


class CLoadImage
{
public:
	LPDIRECT3DDEVICE9 m_pDevcie;		//设备指针
	LPDIRECT3DTEXTURE9 m_pTexture;		//图片指针
	D3DXIMAGE_INFO m_d3dii;					//存储图片信息的结构体

public:

	//加载单张图片，参数为图片路径及文件名
	void InitTexture(LPWSTR pFileName);	

	//加载一组图片，参数1为前段路径及文件名，参数2为图片数量，参数3为图片扩展名
	void InitTexture(LPWSTR pFront , UINT iCount ,LPWSTR pBack );

	CLoadImage( LPDIRECT3DDEVICE9 pDevice );
	~CLoadImage(void);
};
#endif