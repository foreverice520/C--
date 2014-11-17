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

	//hFont1=(HFONT)GetStockObject(DEVICE_DEFAULT_FONT);	//读取系统定义的字体
	//
	hFont=CreateFont(			//用来自定义字体样式
		60,	//字体的高度，默认为0，系统自动获得合适的高度
		0,		//字体的宽度，给0，系统将根据字体高度自动获得
		0,		//每行文字相对于页底的倾斜度
		0,		//每个文字相对于页底的倾斜度
		400,	//字体的粗细，400为正常，700为黑体，0--1000取值
		0,		//是否为斜体字
		0,		//字体是否有下划线
		0,		//字体是否有中划线
		DEFAULT_CHARSET,		//字体所属的字符集
		OUT_DEFAULT_PRECIS,	//字体输出精度，默认为OUT_DEFAULT_PRECIS
		CLIP_DEFAULT_PRECIS,	//字体裁剪精度，默认为CLIP_DEFAULT_PRECIS
		DEFAULT_QUALITY,		//字体输出的质量等级，默认为DEFAULT_QUALITY
		0,						//字体所属的家族信息
		L"华文彩云"		//字样
		);
	SelectObject(hdc,hFont);
	SetTextColor(hdc,RGB(255,255,0));
	SetBkMode(hdc,TRANSPARENT); 
	TextOut(hdc,100,20,	 L"大家好",	(int)wcslen(L"大家好"));
	DeleteObject(hFont);
	EndPaint(m_hWnd,&ps);
}
