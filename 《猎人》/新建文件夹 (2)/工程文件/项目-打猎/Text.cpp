#include "Text.h"

CText::CText(LPDIRECT3DDEVICE9 pDevice):
m_pDevice(pDevice)
{
	m_pFont = NULL;
}

CText::~CText(void)
{
}

void CText::InitText(float xPos, float yPos , wstring Content)
{
	D3DXCreateFont(						//创建字体指针的函数
		m_pDevice,		//设备指针
		0,0,					//字体的高、宽
		700,					//字体的粗细，400为正常，700为粗体，取值范围0-1000
		0,						//默认参数，给0即可
		true,				//是否为斜体字，false不是斜体
		DEFAULT_CHARSET,	//字体所属的字符集，给DEFAULT_CHARSET即可
		0,						//默认参数，给0即可
		0,						//默认参数，给0即可
		0,						//默认参数，给0即可
		L"微软雅黑",	//字体的样式
		&m_pFont			//返回的字体的指针
		);
	m_fTextPosX = xPos;
	m_fTextPosY = yPos;

	m_Content = Content;


	SetRect(&m_FontRect,(int)m_fTextPosX,(int)m_fTextPosY,		//根据字体的宽度来设置写
		(int)m_fTextPosX+140,(int)m_fTextPosY+30);	//字的那个矩形区域的大小


}

void CText::SetContent( wstring Content )
{
	m_Content = Content;
}

//void CText::Logic(float fElapsedTime)
//{
//
//}

void CText::Render(float fElapsedTime)
{
	m_pFont->DrawText(								//绘制字体的函数
		NULL,						//固定参数，为0即可
		m_Content.c_str(),	//要绘制的字体的内容
		-1,							//将字符串内容全部画出来
		&m_FontRect,			//写字的位置信息
		DT_LEFT|DT_TOP,	//字体写在矩形区域内部的哪个位置（对齐方式）
		D3DCOLOR_XRGB(200,200,0)	//字体的颜色
		);
}