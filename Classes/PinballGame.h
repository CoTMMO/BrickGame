#pragma once
#include "SceneBase.h"

class CPinballGame : public CSceneBase
{
public:
	CPinballGame(CGameScene* pGameScene);
	~CPinballGame();

	//---------------------    CSceneBase    ----------------------
	//��ʼ��
	void Init();

	//����
	void Play(float dt);

	//��ȡ��ǰBrick״̬
	bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡС���������еķ���״̬
	bool GetSmallBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	SCENE_INDEX GetSceneType();

	//����
	void OnLeftBtnPressed();

	//���ͷ�
	void OnLeftBtnReleased();

	//�Ұ���
	void OnRightBtnPressed();

	//���ͷ�
	void OnRightBtnReleased();

	//Fire����
	void OnFireBtnPressed();

	//Fire�ͷ�
	void OnFireBtnReleased();

	//---------------------    CSceneBase    ----------------------

private:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//С���ƶ�
	bool BallMove(float dt);

	//�����ƶ�
	bool GuardMove(float dt);

	//�ӷ�
	void AddScore(int iScore);

	//����Ƿ�ͨ��
	bool CheckGamePass();

private:
	enum 
	{
		GUARD_BRICK_COUNT = 4,				//���巽������

		BALL_MOVE_INTERVAL = 100,			//���ƶ�ʱ����

		BRICKS_ROWCOUNT = 5,				//��������

		BTN_CHECK_INTERVAL = 50,			//��ť���ʱ����

		GAMEPASS_ADDCOUNT = 10,				//����10��

		GAMEPASS_ADDSCORE = 10,				//ͨ��ʱÿ�����ӵķ���

		GAMEPASS_REFRESH_INTERVAL = 200,	//ͨ����ʾˢ��ʱ��

		BOOM_REFRESH_INTERVAL = 50,			//��ըЧ��ˢ��ʱ��

		BOOM_SHOWCOUNT = 16,				//��˸��ʾ��ըЧ������
	};

private:
	int m_iSpeed;											//�ٶ�

	int m_iLevel;											//�ؿ�

	int m_iLife;											//ʣ������

	int m_iScore;											//����

	bool m_arrBricks[ROW_NUM][COLUMN_NUM];					//����״̬

	POSITION m_stBallPos;									//��λ��

	POSITION m_stBallDis;									//��ÿ���ƶ��ľ���

	int m_iGuardColIdx;										//����������

	GAME_STATE m_enGameState;								//��Ϸ״̬

	float m_fWaitTime;										//�ƶ��ȴ�ʱ��

	float m_fBtnCheckTime;									//��ť���ʱ��

	bool bLeftMoveFlag;										//���Ʊ��

	bool bRightMoveFlag;									//���Ʊ��

	bool m_bImproveSpeedFlag;								//���ٱ��

	bool m_bShowBoom;										//��ը��ʾ/���ر�ǣ���˸��

	int m_iShowBoomCount;									//��˸��ʾ��ըЧ������

	int m_iAddScoreCount;									//��ǰ�������Ӵ���
};

