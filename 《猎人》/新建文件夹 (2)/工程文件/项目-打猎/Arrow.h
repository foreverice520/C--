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
	D3DXVECTOR2 m_vRotaCenter;		//��ת����
	float m_fRotaAngle;									//��ת�Ƕ�
	bool m_bIsRota;

	float m_fVelocity;			// С�����ٶȵĳ��ٶ�
	float m_fVelocityX;		// С����X������ٶ�
	float m_fVelocityY;		// С����Y������ٶ�
	float m_fAngle;				// С����˲��ĽǶ�
	float m_fGrivate;			// С���յ�������

	ArrowState m_ArrowState;		//С���״̬
public:
	CArrow(HWND hWnd,LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite ,float fVelocity , ArrowState state = AS_IDLE);
	~CArrow(void);

	void SetRotationCenter()
	{ 
	m_vRotaCenter.x = float(m_uiWidth)/2 ; 
	m_vRotaCenter.y = float(m_uiHeight)-2 ; 
	}
	void GetAngle(float angle){ m_fAngle=angle ; }		//���ط���Ƕ�
	float GetRotaAngle(){return m_fRotaAngle;}
	void SetState(ArrowState state) { m_ArrowState = state ;} ;
	bool IsIntersect( CBird * pBird );
	void SetPos(CHunter * pHunter){m_vCurrentPos.y=(pHunter->GetCurrentpos()).y-50;m_vCurrentPos.x=(pHunter->GetCurrentpos()).x-10;}

	void ArrowLogic(float fElapsedTime,CHunter * pHunter);
	void ArrowRender(float fElapsedTime);
};
#endif