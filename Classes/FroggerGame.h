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
	void UpdateRiver(int iRowIndex, float dt);

	//�����Լ�
	void UpdateSelf(float dt);

	//��ʼ�����ݡ�������
	void InitData();


private:
	enum
	{
		RIVER_TOP_ROWINDEX = 8,		//�ӵ����������

		DEFAULT_REFRESHTIME = 700,	//Ĭ��ˢ��ʱ�䣬����

		SELF_REFRESHTIME = 60,		//�Լ�ˢ�µ�ʱ�䣬����
	};
	
	struct RIVER 
	{
		bool bLeft;				//�Ƿ������ƶ�

		int iOffset;			//ƫ��

		int iCurTime;			//��ǰʱ��

		int iRefreshTime;		//��һ��ˢ��ʱ��
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

	int m_iSelfCurTime;							//�Լ���һ�θ���ǰ�ۼ�ʱ��

	bool m_bSelfState;							//��ǰ״̬

	int m_iPassedBrickNum;						//ͨ����Brick����
};

