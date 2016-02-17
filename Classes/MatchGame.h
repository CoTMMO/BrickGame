#pragma once
#include "SceneBase.h"
class CMatchGame : public CSceneBase
{
public:
	CMatchGame(CGameScene* pGameScene);
	~CMatchGame();

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

	//---------------------    CSceneBase    ----------------------

private:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//Ŀ�귽���ƶ�������ֵ��ʾ�Ƿ���Ҫ���½���
	bool DestBricksMove(float dt);

	//�ҷ������ƶ�
	bool MyBricksMove(float dt);

	//���ķ�������
	void ChangeType(DIRECTION enDirection, bool bPressed);

	//�����ҷ�����
	void UpdateMyBricks(DIRECTION enDirection);

	//������Ϸ״̬
	void UpdateGameState();

private:
	enum 
	{
		BRICK_MOVE_INTERVAL = 1000,				//�����ƶ�ʱ����

		BRICK_MATCH_NUM = 3,					//��ƥ��ķ�������

		BOOM_SHOWCOUNT = 16,					//��˸��ʾ��ըЧ������

		MACTHSUCC_ADDSCORE = 10,				//ͨ��ʱ����10

		GAMEPASS_MATCHCOUNT = 10,				//ͨ���ȼ���Ҫƥ��ɹ��Ĵ���

		GAMEPASS_ADDCOUNT = 10,					//����10��

		GAMEPASS_REFRESH_INTERVAL = 200,		//ͨ����ʾˢ��ʱ��

		BOOM_REFRESH_INTERVAL = 50,				//��ըЧ��ˢ��ʱ��

		BRICK_CHANGE_INTERVAL = 60,				//ÿ60�����л�һ��
	};

private:
	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iLife;								//ʣ������

	int m_iScore;								//����

	int m_iMatchSuccCount;						//ƥ��ɹ��ļ���

	int m_arrDestBrick[3];						//3��Ŀ�귽������

	int m_arrMyBrick[3];						//��ǰ3����������

	int m_arrBoomIndex[3];						//��ըλ������

	int m_iDestRowIdx;							//Ŀ�귽��������

	int m_iMyRowIdx;							//�ҷ�����������

	float m_fDestBrickMoveTime;					//Ŀ�귽���ƶ��ȴ�ˢ��ʱ��

	float m_fWaitTime;							//�ȴ�ˢ��ʱ��/�ҷ������ƶ��ȴ�ʱ��

	GAME_STATE m_enGameState;					//��Ϸ״̬

	bool m_bShowBoom;							//��ը��ʾ/���ر�ǣ���˸��

	int m_iShowBoomCount;						//��˸��ʾ��ըЧ������

	int m_iAddScoreCount;						//��ǰ�������Ӵ���

	bool m_arrBtnState[4];						//��ť״̬

	bool m_bConfirmMatch;						//�Ƿ�ȷ��ƥ��
};

