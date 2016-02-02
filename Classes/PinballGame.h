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

	//---------------------    CSceneBase    ----------------------

private:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//С���ƶ�
	void BallMove(float dt);

	//��ȡ���еķ�������
	int GetHitBrickIndex(const POSITION& stPos);

private:
	typedef map<int, POSITION> TMAP_BRICK;
	typedef TMAP_BRICK::iterator TMAP_BRICK_ITER;

	enum 
	{
		GUARD_BRICK_COUNT = 4,		//���巽������

		BALL_MOVE_INTERVAL = 150,	//���ƶ�ʱ����
	};

private:
	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iLife;								//ʣ������

	int m_iScore;								//����

	POSITION m_stBall;							//��λ��

	POSITION m_stBallDis;						//��ÿ���ƶ��ľ���

	POSITION m_stGuard;							//����λ��

	TMAP_BRICK m_mapBrick;						//��������λ��

	GAME_STATE m_enGameState;					//��Ϸ״̬

	float m_fMoveTime;							//�ƶ��ȴ�ʱ��
};

