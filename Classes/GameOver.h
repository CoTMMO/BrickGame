#pragma once
#include "GameBase.h"
class CGameOver : public CGameBase
{
public:
	CGameOver();
	~CGameOver();

	//---------------------    GameBase    ----------------------
	//��ʼ��
	void Init();

	//���Ž���Ч��
	bool Play();

	//��ȡ��ǰҪ����Brick��λ��
	void GetCurPos(int& iRowIndex, int& iColIndex);

	//��Ϸ����
	SCENE_INDEX GetSceneType();

	//��ȡÿ��ִ����Play��ȴ���ʱ��
	float GetRefreshTime();
	//---------------------    GameBase    ----------------------

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

