#include "HPText.h"

CHPText::CHPText(HWND hWnd)
{
	m_hWnd=hWnd;
}

CHPText::~CHPText(void)
{
}
void CHPText::Render(float fElapsedTime)
{
	hdc=BeginPaint(m_hWnd,&ps);

	//hFont1=(HFONT)GetStockObject(DEVICE_DEFAULT_FONT);	//��ȡϵͳ���������
	//
	hFont=CreateFont(			//�����Զ���������ʽ
		60,	//����ĸ߶ȣ�Ĭ��Ϊ0��ϵͳ�Զ���ú��ʵĸ߶�
		0,		//����Ŀ�ȣ���0��ϵͳ����������߶��Զ����
		0,		//ÿ�����������ҳ�׵���б��
		0,		//ÿ�����������ҳ�׵���б��
		400,	//����Ĵ�ϸ��400Ϊ������700Ϊ���壬0--1000ȡֵ
		0,		//�Ƿ�Ϊб����
		0,		//�����Ƿ����»���
		0,		//�����Ƿ����л���
		DEFAULT_CHARSET,		//�����������ַ���
		OUT_DEFAULT_PRECIS,	//����������ȣ�Ĭ��ΪOUT_DEFAULT_PRECIS
		CLIP_DEFAULT_PRECIS,	//����ü����ȣ�Ĭ��ΪCLIP_DEFAULT_PRECIS
		DEFAULT_QUALITY,		//��������������ȼ���Ĭ��ΪDEFAULT_QUALITY
		0,						//���������ļ�����Ϣ
		L"���Ĳ���"		//����
		);
	SelectObject(hdc,hFont);
	SetTextColor(hdc,RGB(255,255,0));
	SetBkMode(hdc,TRANSPARENT); 
	TextOut(hdc,100,20,	 L"��Һ�",	(int)wcslen(L"��Һ�"));
	DeleteObject(hFont);
	EndPaint(m_hWnd,&ps);
}
