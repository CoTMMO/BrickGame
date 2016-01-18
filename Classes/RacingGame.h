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
	//�������
	void AddNewLine();
	
	//��������iRoadIdx��ʾ����������iRowIdx��ʾ��������bSelf��ʾ�Ƿ����Լ�
	void DrawCar(int iRoadIdx, int iRowIdx, bool bSelf);

	//��ʼ��Brick
	void InitBrick();

	//�Ƿ���Ϸ����
	bool IsGameOver();

	//����Brick
	void UpdateBricks();

private:
	enum 
	{
		CAR_MAXNUM = 3,		//ͬʱ���ֵĳ��������

		ROAD_MAXINDEX = 3,	//���������������0��ʼ

		CAR_WIDTH = 3,		//�����

		CAR_HEIGHT = 4,		//���߶�
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
};

