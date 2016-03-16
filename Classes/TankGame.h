#pragma once
#include "SceneBase.h"

class CTankGame : public CSceneBase
{
private:
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
		int m_iCamp;			//��Ӫ

		POSITION m_stPos;		//λ��

		float m_fMoveTime;		//�ƶ��ȴ�ʱ��

		int m_iDirection;		//����

		bool m_bValid;			//�Ƿ���Ч
	};

	//struct BOSS_DATA
	//{
	//	bool m_bDead;			//�Ƿ�����

	//	int m_iColIdx;			//��λ��

	//	float m_fMoveTime;		//�ƶ��ȴ�ʱ��

	//	float m_fMoveMaxTime;	//�ƶ��ȴ������

	//	float m_fFireTime;		//�ȴ������ӵ�ʱ��

	//	float m_fFireMaxTime;	//�����ӵ��ȴ������

	//	int m_iDirection;		//����
	//};

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

	//�ȴ��ƶ����ײ��м�
	bool WaitToMoveBottomCenter(float dt, bool& bDoneFlag);

	//---------------------    CSceneBase    ----------------------

private:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//����̹��
	bool CreateTank(float dt);

	//��̹��
	bool DrawTank(const POSITION& stPos, int iDirection, const POSITION& stTargetPos);

	//���λ���Ƿ���Ч
	bool CheckPos(int iTankIdx, const POSITION& stPos);

	//̹���ƶ�
	bool TankMove(float dt);

	//����ĳ��̹��λ��
	void UpdateTankPos(int iTankIdx);

	//��ȡ��һ��λ��
	bool GetNextPos(int iTankIdx, POSITION& stOutPos);

	//��ȡ��һ��λ��
	bool GetNextPos(const POSITION& stCurPos, int iDirection, POSITION& stOutPos, bool bTankFlag = true);

	//�ҷ�̹���ƶ�
	bool SelfTankMove(float dt);

	//̹�˷����ӵ�
	bool TankFire(float dt);

	//�ӵ�����
	void CreateBullet(int iTankIdx);

	//�ӵ��ƶ�
	bool BulletMove(float dt);

	//�ӵ�
	void BulletShoot();

	//�ӵ����е�̹��������δ����ʱ����-1
	int GetBulletFireTankIndex(const POSITION& stBulletPos, int iCamp);

	//��ʾ��ըЧ�������ؽ����ʾ�Ƿ���Ҫʹ�ô�����ֵ
	bool ShowBoom(int iRowIndex, int iColIndex, bool& bState);

	//�Ƿ�ͨ����ǰ�ȼ�
	bool CheckAllTankDead();

	//��ȡһ����Ч�Ľ���λ��
	bool GetCornerPos(int iTankIdx);

private:
	enum
	{
		TANK_MAXNUM = 4,							//̹���������

		BULLET_MAXNUM = 20,							//�ӵ������������

		TANK_MOVE_INTERVAL = 800,					//̹���ƶ�ʱ����

		BULLET_MOVE_INTERVAL = 40,					//�ӵ��ƶ�ʱ����

		BULLET_CREATE_MAXTIME = 5500,				//������ӵ�ʱ��

		TANK_CREATE_TIME = TANK_MOVE_INTERVAL,		//̹�˴���ʱ����

		TANK_MOVE_MAXSTEP = 10,						//̹���ƶ������

		TANK_SELF_MOVE_INTERVAL = 55,				//�ҷ�̹��ÿ���ƶ��ȴ�ʱ��

		TANK_SELF_FIRE_TIME = 200,					//ÿ�η����ӵ�����

		BOOM_SHOWCOUNT = 16,						//��˸��ʾ��ըЧ������

		GAMEPASS_ADDCOUNT = 10,						//����10��

		GAMEPASS_REFRESH_INTERVAL = 200,			//ͨ����ʾˢ��ʱ��

		BOOM_REFRESH_INTERVAL = 50,					//��ըЧ��ˢ��ʱ��

		TANK_KILL_ADD_SCORE = 10,					//ɱ��һ��̹�����ӵķ���

		TANK_CREATE_MAXCOUNT = 4,					//ÿһ���ȼ�̹�˴����������

		BOSS_FIRE_MIN_INTERVAL = 500,				//boss�����ӵ���Сʱ����

		BOSS_FIRE_MAX_INTERVAL = 2000,				//boss�����ӵ����ʱ����
	};

	//��Ӫ
	enum CAMP
	{
		CAMP_NONE,
		CAMP_A,
		CAMP_B,
	};

	typedef vector<BULLET_DATA> TVEC_BULLET;
	typedef TVEC_BULLET::iterator TVEC_BULLET_ITER;

private:
	TANK_DATA m_arrTank[TANK_MAXNUM];			//̹����������

	BULLET_DATA m_arrBullet[BULLET_MAXNUM];	//�ӵ���������

	TANK_DATA m_stSelfTank;						//̹���Լ�

	bool m_arrBtnState[DIR_MAX];				//�ĸ�����ť״̬

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iLife;								//ʣ������

	int m_iScore;								//����

	float m_fTankMoveTime;						//̹���ƶ��ȴ�ʱ��

	float m_fTankCreateTime;					//̹�˴���ʱ��

	float m_fSelfMoveTime;						//�ҷ�̹���ƶ�ʱ��

	float m_fWaitRefreshTime;					//�ȴ�ˢ��ʱ��

	bool m_arrCornerState[4];					//��һ�δ����ĸ�����̹�˵����

	GAME_STATE m_enGameState;					//��Ϸ״̬

	bool m_bShowBoom;							//��ը��ʾ/���ر�ǣ���˸��

	int m_iShowBoomCount;						//��˸��ʾ��ըЧ������

	int m_iAddScoreCount;						//��ǰ�������Ӵ���

	bool m_bFireState;							//����״̬

	int m_iTankCreateCount;						//̹�˴�������

	TANK_DATA m_stBoss;							//boss����

	bool m_bBossFlag;							//�Ƿ���BOSS�׶�
};

