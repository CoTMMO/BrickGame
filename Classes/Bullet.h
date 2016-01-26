#pragma once
#include "TankCommon.h"

class CBullet
{
public:
	CBullet();
	~CBullet();

	//��ʼ��
	void Init(int iRowIdx, int iColIdx, int iDirection);

	//����λ��
	void Update(float dt);

	//��ȡλ��
	const TANK_POS& GetPos();

	//�Ƿ���Ч
	bool IsValid();

	//�����Ƿ���Ч���
	void SetValid(bool bValid);

	//�Ƿ������̹��
	bool IsHitOnTank(const TANK_POS& stTankPos);

private:
	enum 
	{
		BULLET_UPDATE_TIME = 500,	//ÿ500����ˢ��һ��
	};

private:
	bool m_bValid;			//�Ƿ���Ч

	float m_fCurTime;		//��ǰ�ȴ�����ʱ��

	TANK_POS m_stPos;		//��ǰλ��

	int m_iDirection;		//����
};

