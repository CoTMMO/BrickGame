#pragma once
#include "BGGlobal.h"
#include "SceneBase.h"

class CAddBrickGame : public CSceneBase
{
public:
	CAddBrickGame(CGameScene* pScene, bool bSpecialMode = false);
	~CAddBrickGame();


	////////////////////////////////// CSceneBase ////////////////////////////////////////
	//��ʼ��
	virtual void Init();

	//����
	virtual void Play(float dt);

	//��ȡ��ǰBrick״̬
	virtual bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡС���������еķ���״̬
	virtual bool GetSmallBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	virtual SCENE_INDEX GetSceneType();

	//����
	virtual void OnLeftBtnPressed();

	//���ͷ�
	virtual void OnLeftBtnReleased();

	//�Ұ���
	virtual void OnRightBtnPressed();

	//���ͷ�
	virtual void OnRightBtnReleased();

	//Fire����
	virtual void OnFireBtnPressed();

	//Fire�ͷ�
	virtual void OnFireBtnReleased();

private:
	//��ʼ������
	void initData();

	//�ƶ�
	bool bricksMoveDown(float dt);

	//���״̬
	bool randState();

	//������
	void updateGameState();

	//�������
	bool fireBricks(float dt);

	//�ҷ��ƶ�
	bool selfMove(float dt);

	//�ӵ��ƶ�
	bool bulletsMove(float dt);

	//����
	void deleteLine(int nRowIdx);

private:
	enum VALID_BTN
	{
		VBTN_LEFT,
		VBTN_RIGHT,
		VBTN_FIRE,
		VBTN_MAX,
	};

	enum
	{
		GAMEOVER_WAIT_INTERVAL = 1500,		//��Ϸ�����ȴ�ʱ��

		GAMEPASS_WAIT_INTERVAL = 1500,		//��Ϸͨ���ȴ�ʱ��

		BOOM_SHOWCOUNT = 16,				//��˸��ʾ��ըЧ������

		BRICKS_MOVE_INTERVAL = 2500,		//�����ƶ�ʱ����

		MOVE_CHECK_INTERVAL = 65,			//��ť���ʱ����

		FIRE_CHECK_INTERVAL = 100,			//�����ť���ʱ����

		BULLET_MOVE_INTERVAL = 70,			//�ӵ��ƶ�ʱ��
	};

	typedef list<POSITION>	TLIST_POS;
	typedef TLIST_POS::iterator	TLIST_POS_ITER;

private:
	bool m_arrBrick[ROW_NUM][COLUMN_NUM];		//����״̬����

	POSITION m_stSelfPos;						//�ҷ�����λ��

	bool m_arrBtnPressFlag[DIR_MAX];			//��ť���±��

	GAME_STATE	m_enGameState;					//��Ϸ״̬

	float m_fWaitTime;							//�ȴ�ʱ��

	float m_fFireBtnTime;						//����ȴ�ʱ��

	float m_fSelfMoveTime;						//�ƶ��ȴ�ʱ��

	TLIST_POS m_lsBullets;						//�ӵ��б�

	float m_fBulletMoveTime;					//�ӵ��ƶ��ȴ�ʱ��

	bool m_bSpecialMode;						//����ģʽ

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iScore;								//����

	int m_iLife;								//����
};

