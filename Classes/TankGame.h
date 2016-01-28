#pragma once
#include "SceneBase.h"

class CTankGame : public CSceneBase
{
private:
	struct POSITION
	{
		int m_iRowIdx;			//��λ��

		int m_iColIdx;			//��λ��
	};

	//̹������
	struct TANK_DATA
	{
		POSITION m_stPos;		//λ��

		int m_iDirection;		//�ƶ�����

		int m_iCurStep;			//��ǰ���߲���

		int m_iMaxStep;			//�����

		bool m_bNeedReset;		//�Ƿ���Ҫ���ã������ͷ���

		int m_iCamp;			//��Ӫ

		float m_fFireWaitTime;	//����ȴ���ʱ��

		float m_fFireMaxTime;	//���η�����ȴ���ʱ��

		bool m_bDead;			//�Ƿ�����
	};

	//�ӵ�����
	struct BULLET_DATA
	{
		POSITION m_stPos;		//λ��

		float m_fMoveTime;		//�ƶ��ȴ�ʱ��

		bool m_bValid;			//�Ƿ���Ч
	};

public:
	CTankGame(CGameScene* pGameScene);
	~CTankGame();

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

	//�ϰ���
	void OnUpBtnPressed();

	//���ͷ�
	void OnUpBtnReleased();

	//�°���
	void OnDownPressed();

	//���ͷ�
	void OnDownReleased();

	//Fire����
	void OnFireBtnPressed();

	//Fire�ͷ�
	void OnFireBtnReleased();

	//---------------------    CSceneBase    ----------------------

private:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//����̹��
	void CreateTank(float dt);

	//��̹��
	bool DrawTank(const POSITION& stPos, int iDirection, const POSITION& stTargetPos);

	//���λ���Ƿ���Ч
	bool CheckPos(int iTankIdx, const POSITION& stPos);

	//̹���ƶ�
	void TankMove(float dt);

	//����ĳ��̹��λ��
	void UpdateTankPos(int iTankIdx);

	//��ȡ��һ��λ��
	bool GetNextPos(int iTankIdx, POSITION& stOutPos);

private:
	enum
	{
		TANK_MAXNUM = 4,							//̹���������

		TANK_MOVE_INTERVAL = 800,					//̹���ƶ�ʱ����

		BULLET_MOVE_INTERVAL = 500,					//�ӵ��ƶ�ʱ����

		BULLET_CREATE_MAXTIME = 10000,				//������ӵ�ʱ��

		TANK_CREATE_TIME = 2 * TANK_MOVE_INTERVAL,	//̹�˴���ʱ����

		TANK_MOVE_MAXSTEP = 10,						//̹���ƶ������
	};

	//��Ӫ
	enum CAMP
	{
		CAMP_NONE,
		CAMP_A,
		CAMP_B,
	};

private:
	TANK_DATA m_arrTank[TANK_MAXNUM];			//̹����������

	BULLET_DATA m_arrBullet[TANK_MAXNUM];		//�ӵ���������

	TANK_DATA m_stSelfTank;						//̹���Լ�

	BULLET_DATA m_stSelfBullet;					//��Ӧ���ӵ�

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iLife;								//ʣ������

	int m_iScore;								//����

	float m_fTankMoveTime;						//̹���ƶ��ȴ�ʱ��

	float m_fTankCreateTime;					//̹�˴���ʱ��

	int m_iFirstCreateNum;						//��һ�δ���̹������
};

