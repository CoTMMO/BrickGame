#pragma once
#include "GlobalDef.h"

class CGameBase
{
public:
	CGameBase();
	~CGameBase();

	//��Ϸ���У�����falseʱ��ʾ��Ϸ����
	virtual bool Play();

	//�ṩ��ÿ�θ��µ���Brick��Ϸ����ǰֻ����Ϸ������ʹ�ã���ȡ��ǰ�ı��Brick��������
	virtual void GetCurPos(int& iRowIndex, int& iColIndex);

	virtual GAME_INDEX GetGameType();
};

