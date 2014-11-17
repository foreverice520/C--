#pragma once
#ifndef CArrow_H_
#define CArrow_H_

#include "Element.h"
#include "Bird.h"
#include "Hunter.h"
enum ArrowState{AS_IDLE , AS_NONINTERSECT , AS_INTERSECT };
class CArrow :public CElement
{
private:
	CHunter * pHunter;
	D3DXVECTOR2 m_vRotaCenter;		//旋转中心
	float m_fRotaAngle;									//旋转角度
	bool m_bIsRota;

	float m_fVelocity;			// 小球发射速度的初速度
	float m_fVelocityX;		// 小球在X方向的速度
	float m_fVelocityY;		// 小球在Y方向的速度
	float m_fAngle;				// 小球发射瞬间的角度
	float m_fGrivate;			// 小球收到的重力

	ArrowState m_ArrowState;		//小球的状态
public:
	CArrow(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite ,float fVelocity , ArrowState state = AS_IDLE);
	~CArrow(void);

	void SetRotationCenter()
	{ 
	m_vRotaCenter.x = float(m_uiWidth)/2 ; 
	m_vRotaCenter.y = float(m_uiHeight)-2 ; 
	}
	void GetAngle(float angle){ m_fAngle=angle ; }		//返回发射角度
	float GetRotaAngle(){return m_fRotaAngle;}
	void SetState(ArrowState state) { m_ArrowState = state ;} ;
	bool IsIntersect( CBird * pBird );
	void SetPos(CHunter * pHunter){m_vCurrentPos.y=(pHunter->GetCurrentpos()).y-50;m_vCurrentPos.x=(pHunter->GetCurrentpos()).x-10;}

	void ArrowLogic(float fElapsedTime,CHunter * pHunter);
	void ArrowRender(float fElapsedTime);
};
#endif