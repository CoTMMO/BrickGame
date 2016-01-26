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

	bool operator== (const TANK_POS& rhs) const
	{
		return this->m_iRowIdx == rhs.m_iRowIdx && this->m_iRowIdx == rhs.m_iColIdx;
	};

	TANK_POS& operator+= (const TANK_POS& rhs)
	{
		this->m_iRowIdx += rhs.m_iRowIdx;
		this->m_iColIdx += rhs.m_iColIdx;
		return *this;
	}

	const TANK_POS operator+ (const TANK_POS& rhs) const
	{
		TANK_POS temp(*this);
		temp += rhs;
		return temp;
	}
};


//��Ӫö��
enum TANK_CAMP
{
	CAMP_NONE,
	CAMP_A,
	CAMP_B,
};
