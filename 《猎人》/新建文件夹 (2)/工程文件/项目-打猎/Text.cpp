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
	D3DXCreateFont(						//��������ָ��ĺ���
		m_pDevice,		//�豸ָ��
		0,0,					//����ĸߡ���
		700,					//����Ĵ�ϸ��400Ϊ������700Ϊ���壬ȡֵ��Χ0-1000
		0,						//Ĭ�ϲ�������0����
		true,				//�Ƿ�Ϊб���֣�false����б��
		DEFAULT_CHARSET,	//�����������ַ�������DEFAULT_CHARSET����
		0,						//Ĭ�ϲ�������0����
		0,						//Ĭ�ϲ�������0����
		0,						//Ĭ�ϲ�������0����
		L"΢���ź�",	//�������ʽ
		&m_pFont			//���ص������ָ��
		);
	m_fTextPosX = xPos;
	m_fTextPosY = yPos;

	m_Content = Content;


	SetRect(&m_FontRect,(int)m_fTextPosX,(int)m_fTextPosY,		//��������Ŀ��������д
		(int)m_fTextPosX+140,(int)m_fTextPosY+30);	//�ֵ��Ǹ���������Ĵ�С


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
	m_pFont->DrawText(								//��������ĺ���
		NULL,						//�̶�������Ϊ0����
		m_Content.c_str(),	//Ҫ���Ƶ����������
		-1,							//���ַ�������ȫ��������
		&m_FontRect,			//д�ֵ�λ����Ϣ
		DT_LEFT|DT_TOP,	//����д�ھ��������ڲ����ĸ�λ�ã����뷽ʽ��
		D3DCOLOR_XRGB(200,200,0)	//�������ɫ
		);
}