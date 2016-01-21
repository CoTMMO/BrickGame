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

	//��ʼ�����ݡ�������
	void InitData();

private:
	struct RIVER
	{
		bool bLeft;				//�Ƿ�������ƶ�

		int iCurState;			//��һ��������Brick״̬��0��ʾ��

		int iCount;				//��ǰ����Brick�ĸ���

		int arrMaxCount[2];		//��Ӧ״̬������Brick�������

		int arrRefreshTime[2];	//ˢ��ʱ��

		int iCurTime;			//��ǰʱ��
	};

	typedef map<int, RIVER> TMAP_RIVER;

private:
	TMAP_RIVER m_mapRiver;						//�ӵ�����

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];	//Brick״̬

	int m_iLife;								//������

	int m_iSpeed;								//��ǰ�ٶ�

	int m_iLevel;								//��ǰ�ȼ�

	int m_iScore;								//��ǰ����

	int m_iEndRiverIdx;							//�ӵ����ϲ�����������ÿһ���ȼ���������

	int m_iSelfRowIdx;							//�Լ����ڵ�������

	int m_iSelfColIdx;							//�Լ����ڵ�������
};

