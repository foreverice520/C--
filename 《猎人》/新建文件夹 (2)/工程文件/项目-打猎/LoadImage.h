/*
		DESC:  ����Ĺ���Ϊ������ԴͼƬ
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
	LPDIRECT3DDEVICE9 m_pDevcie;		//�豸ָ��
	LPDIRECT3DTEXTURE9 m_pTexture;		//ͼƬָ��
	D3DXIMAGE_INFO m_d3dii;					//�洢ͼƬ��Ϣ�Ľṹ��

public:

	//���ص���ͼƬ������ΪͼƬ·�����ļ���
	void InitTexture(LPWSTR pFileName);	

	//����һ��ͼƬ������1Ϊǰ��·�����ļ���������2ΪͼƬ����������3ΪͼƬ��չ��
	void InitTexture(LPWSTR pFront , UINT iCount ,LPWSTR pBack );

	CLoadImage( LPDIRECT3DDEVICE9 pDevice );
	~CLoadImage(void);
};
#endif