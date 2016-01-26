#include "Bullet.h"
#include "GlobalDef.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}


//����λ��
void CBullet::Update(float dt)
{
	m_fCurTime += dt;
	if (m_fCurTime < BULLET_UPDATE_TIME)
	{
		return;
	}

	//����λ��
	switch (m_iDirection)
	{
	case DIR_RIGHT:
		++m_stPos.m_iColIdx;
		break;
	case DIR_LEFT:
		--m_stPos.m_iColIdx;
		break;
	case DIR_UP:
		--m_stPos.m_iRowIdx;
		break;
	case DIR_DOWN:
		++m_stPos.m_iRowIdx;
		break;
	}

	//��������߽磬���ñ��Ϊ��Ч
	if (m_stPos.m_iRowIdx < 0 || m_stPos.m_iRowIdx > ROW_NUM - 1
		|| m_stPos.m_iColIdx < 0 || m_stPos.m_iColIdx > COLUMN_NUM - 1)
	{
		m_bValid = false;
	}
}


//�Ƿ������̹��
bool CBullet::IsHitOnTank(const TANK_POS& stTankPos)
{
	if (abs(stTankPos.m_iRowIdx - stTankPos.m_iRowIdx) <= 1
		&& abs(m_stPos.m_iColIdx - stTankPos.m_iColIdx) <= 1)
	{
		return true;
	}

	return false;
}


//��ȡλ��
const TANK_POS& CBullet::GetPos()
{
	return m_stPos;
}


//��ȡ�Ƿ���Ч���
bool CBullet::IsValid()
{
	return m_bValid;
}


//�����Ƿ���Ч���
void CBullet::SetValid(bool bValid)
{
	m_bValid = bValid;
}


void CBullet::Init(int iRowIdx, int iColIdx, int iDirection)
{
	//λ��
	m_stPos.m_iRowIdx = iRowIdx;
	m_stPos.m_iColIdx = iColIdx;

	//����
	m_iDirection = iDirection;

	//ʱ��
	m_fCurTime = 0;

	//������Ч
	m_bValid = true;
}
