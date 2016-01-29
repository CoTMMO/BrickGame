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
	void OnLeftBtnPressed();

	//�Ұ���
	void OnRightBtnPressed();

	//�ϰ���
	void OnUpBtnPressed();

	//�°���
	void OnDownPressed();

	//Fire����
	void OnFireBtnPressed();

	//Fire�ͷ�
	void OnFireBtnReleased();

	//---------------------    CSceneBase    ----------------------

private:
	//����Brick���������
	void UpdateBricks();
	
	//��������iRoadIdx��ʾ����������iRowIdx��ʾ������
	void RandCreateCars();

	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//��ʼ��Brick
	void InitBrick();

	//��ȡ�ȴ�ʱ��
	int GetWaitInterval();

private:
	enum 
	{
		CAR_MAXNUM = 3,							//ͬʱ���ֵĳ��������

		ROAD_COUNT = 4,							//��������

		CAR_WIDTH = 3,							//�����

		CAR_HEIGHT = 4,							//���߶�

		ROW_DISTANCE = ROW_NUM / 2 + 1,			//����11�������µ�����

		DEFAULT_INTERVAL = 160,					//Ĭ�ϵȴ�ʱ��

		CAR_DEFAULTROW = 2,						//Ĭ��������

		BOOM_SHOWCOUNT = 10,					//��˸��ʾ��ըЧ������

		GAMEPASS_ADDSCORE = 100,				//ͨ��ʱ����100

		GAMEPASS_ADDCOUNT = 10,					//����10��

		GAMEPASS_CARCOUNT = 16,					//�������������ﵽ16ʱͨ��
	};


private:
	int m_iCarPos;								//����ǰλ��

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	bool m_arrCurBrick[ROW_NUM][COLUMN_NUM];	//Brick״̬

	int m_iLife;								//ʣ������

	int m_iRoadSignCount;						//·������

	int m_iPassCarCount;						//��������������

	bool m_bFirstShow;							//�Ƿ��ǵ�һ����ʾ

	int m_fWaitTime;							//��ǰ�ȴ�����ʱ��

	bool m_bImproveSpeed;						//�Ƿ����

	GAME_STATE m_enGameState;					//��Ϸ״̬

	bool m_bShowBoom;							//��ը��ʾ/���ر�ǣ���˸��

	int m_iShowBoomCount;						//��˸��ʾ��ըЧ������

	int m_iScore;								//����

	int m_arrRowIdx[2];							//�м�¼

	int m_iAddScoreCount;						//��ǰ��Ӵ���
};

