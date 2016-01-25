#pragma once
#include "SceneBase.h"
class CFroggerGame : public CSceneBase
{
public:
	CFroggerGame(CGameScene* pGameScene);
	~CFroggerGame();

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

	//---------------------    CSceneBase    ----------------------

private:
	//�������кӵ�
	void UpdateRivers(float dt);

	//����ָ���еĺӵ�
	void UpdateRiver(int iRowIndex);

	//�����Լ�
	void UpdateSelf(float dt);

	//��ʼ�����ݡ�������
	void InitData();

	//������Ϸ״̬
	void UpdateGameState();

	//���ñ�ը
	void SetBoom(float dt);

private:
	enum
	{
		RIVER_ROWTOP_INDEX = 8,		//�ӵ����������

		DEFAULT_REFRESHTIME = 700,	//Ĭ��ˢ��ʱ�䣬����

		SELF_REFRESHTIME = 60,		//�Լ�ˢ�µ�ʱ�䣬����

		RIVER_COUNT = 5,			//�ӵ�����

		GAMEPASS_COUNT = 5,			//�ﵽ������ʱ��Ϸ������һ��

		BOOM_SHOWCOUNT = 10,		//��˸��ʾ��ըЧ������

		BOOM_REFRESHTIME = 60,		//��ը��˸���

		GAMEPASS_WAITTIME = 1000,	//ͨ����ȴ���ʱ��
	};
	
	struct RIVER 
	{
		bool bLeft;					//�Ƿ������ƶ�

		int iOffset;				//ƫ��

		bool arrDefaultState[20];	//Ĭ��״̬
	};

	typedef map<int, RIVER> TMAP_RIVER;

private:
	TMAP_RIVER m_mapRiverData;					//�ӵ�����

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];	//Brick״̬

	int m_iLife;								//������

	int m_iSpeed;								//��ǰ�ٶ�

	int m_iLevel;								//��ǰ�ȼ�

	int m_iScore;								//��ǰ����

	int m_iSelfRowIdx;							//�Լ����ڵ�������

	int m_iSelfColIdx;							//�Լ����ڵ�������

	float m_fSelfCurTime;						//�Լ���һ�θ���ǰ�ۼ�ʱ��

	float m_fRiverCurTime;						//�ӵ���ǰʱ��

	int m_iPassCount;							//ͨ������������

	bool m_bSelfState;							//��ǰ״̬

	GAME_STATE m_enGameState;					//��Ϸ״̬

	int m_iShowBoomCount;						//��˸��ʾ��ըЧ������

	float m_fBoomCurTime;						//��ը��ǰʱ��

	float m_fPassCurTime;						//ͨ����ǰʱ��
};

