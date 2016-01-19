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
	//����Brick���������
	void UpdateBricks();
	
	//��������iRoadIdx��ʾ����������iRowIdx��ʾ������
	void RandCreateCars();

	//��ʼ��Brick
	void InitBrick();

	//��ȡ���ֵ
	void RandSeed();

private:
	enum 
	{
		CAR_MAXNUM = 3,				//ͬʱ���ֵĳ��������

		ROAD_COUNT = 4,				//��������

		CAR_WIDTH = 3,				//�����

		CAR_HEIGHT = 4,				//���߶�

		GAMEOVER_REMAINTIME = 3000,	//��Ϸ�����������3��

		ROW_DISTANCE = 11,			//����11�������µ�����

		DEFAULT_INTERVAL = 400,		//Ĭ�ϵȴ�ʱ��

		CAR_DEFAULTROW = 2,		//Ĭ��������
	};


private:
	int m_iCarPos;								//����ǰλ��

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	bool m_arrCurBrick[ROW_NUM][COLUMN_NUM];	//Brick״̬

	int m_iLife;								//ʣ������

	int m_iRoadSignCount;						//·������

	bool m_bFirstShow;							//�Ƿ��ǵ�һ����ʾ

	int m_fWaitTime;							//�ȴ����¼��

	bool m_bGameOver;							//�Ƿ���Ϸ����

	int m_iScore;								//����

	int m_arrRowIdx[2];							//�м�¼
};

