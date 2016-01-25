#pragma once

//λ�ýṹ��
struct TANK_POS
{
	int m_iColIdx;				//��ǰ������

	int m_iRowIdx;				//��ǰ������

	TANK_POS() : m_iRowIdx(0), m_iColIdx(0)
	{
	};

	TANK_POS(int iRowIdx, int iColIdx) : m_iRowIdx(iRowIdx), m_iColIdx(iColIdx)
	{
	};

	TANK_POS(const TANK_POS& stPos)
	{
		this->m_iRowIdx = stPos.m_iRowIdx;
		this->m_iColIdx = stPos.m_iColIdx;
	};

	bool operator== (const TANK_POS& stPos) const
	{
		return this->m_iRowIdx == stPos.m_iRowIdx && this->m_iRowIdx == stPos.m_iColIdx;
	};
};


//��Ӫö��
enum TANK_CAMP
{
	CAMP_NONE,
	CAMP_A,
	CAMP_B,
};
