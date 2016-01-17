#pragma once
#include "SceneBase.h"

class CRacingGame : public CSceneBase
{
public:
	CRacingGame();
	~CRacingGame();

	//---------------------    CSceneBase    ----------------------
	//��ʼ��
	void Init();

	//��Ϸ���У�����falseʱ��ʾ��Ϸ����
	bool Play();

	//��ȡ��ǰBrick״̬
	bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
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

	//---------------------    CSceneBase    ----------------------

private:
	int m_iCarPos;

};

