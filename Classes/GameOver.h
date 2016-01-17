#pragma once
#include "SceneBase.h"
class CGameOver : public CSceneBase
{
public:
	CGameOver();
	~CGameOver();

	//---------------------    SceneBase    ----------------------
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

	//��
	void OnLeft();

	//��
	void OnRight();

	//��
	void OnUp();

	//��
	void OnDown();

	//Fire
	void OnFire();

	//��ʼ
	void OnStart();
	//---------------------    SceneBase    ----------------------

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

