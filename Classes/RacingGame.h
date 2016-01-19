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

	//������
	bool GetSmallBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	SCENE_INDEX GetSceneType();

	//����
	virtual void OnLeftBtnPressed();

	//�Ұ���
	virtual void OnRightBtnPressed();

	//�ϰ���
	virtual void OnUpBtnPressed();

	//�°���
	virtual void OnDownPressed();

	//Fire����
	virtual void OnFireBtnPressed();

	//Fire�ͷ�
	virtual void OnFireBtnReleased();

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

	//��ȡ�ȴ�ʱ��
	int GetWaitInterval();

private:
	enum 
	{
		CAR_MAXNUM = 3,				//ͬʱ���ֵĳ��������

		ROAD_COUNT = 4,				//��������

		CAR_WIDTH = 3,				//�����

		CAR_HEIGHT = 4,				//���߶�

		GAMEOVER_REMAINTIME = 3000,	//��Ϸ�����������3��

		ROW_DISTANCE = 11,			//����11�������µ�����

		DEFAULT_INTERVAL = 160,		//Ĭ�ϵȴ�ʱ��

		CAR_DEFAULTROW = 2,			//Ĭ��������

		BOOM_SHOWCOUNT = 6,			//��˸��ʾ��ըЧ������
	};


private:
	int m_iCarPos;								//����ǰλ��

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	bool m_arrCurBrick[ROW_NUM][COLUMN_NUM];	//Brick״̬

	int m_iLife;								//ʣ������

	int m_iRoadSignCount;						//·������

	bool m_bFirstShow;							//�Ƿ��ǵ�һ����ʾ

	int m_fWaitTime;							//��ǰ�ȴ�����ʱ��

	bool m_bImproveSpeed;						//�Ƿ����

	bool m_bGameOver;							//�Ƿ���Ϸ����

	bool m_bShowBoom;							//��ը��ʾ/���ر�ǣ���˸��

	int m_iShowBoomCount;						//��˸��ʾ��ըЧ������

	int m_iScore;								//����

	int m_arrRowIdx[2];							//�м�¼
};

