#pragma once
#include "SceneBase.h"

class CRacingGame : public CSceneBase
{
public:
	CRacingGame(CGameScene* pGameScene);
	~CRacingGame();

	//---------------------    CSceneBase    ----------------------
	//��ʼ��
	void Init();

	//����
	void Play(float dt);

	//��ȡ��ǰBrick״̬
	bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	SCENE_INDEX GetSceneType();

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

	


private:
	enum 
	{
		CAR_MAXNUM = 3,		//ͬʱ���ֵĳ��������

		ROAD_MAXINDEX = 3,	//���������������0��ʼ
	};


private:
	int m_iCarPos;								//����ǰλ��

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];	//Brick״̬

	int m_iLife;								//ʣ������
};

