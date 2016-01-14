#pragma once
#include "GameBase.h"
class CGameOver : public CGameBase
{
public:
	CGameOver();
	~CGameOver();

	//���Ž���Ч��
	bool Play();

	//��ȡ��ǰҪ����Brick��λ��
	void GetCurPos(int& iRowIndex, int& iColIndex);

	//��Ϸ����
	GAME_INDEX GetGameType();

private:
	int m_iColIdx;
	int m_iRowIdx;

	int m_iBeginColIdx;
	int m_iBeginRowIdx;

	int m_iEndColIdx;
	int m_iEndRowIdx;

	int m_iDirection;

	int m_iAllCount;
};

