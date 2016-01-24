#pragma once
#include "SceneBase.h"

struct TANK_POS
{
	int m_iColIdx;				//��ǰ������

	int m_iRowIdx;				//��ǰ������

	bool operator== (const TANK_POS& stPos) const
	{
		return this->m_iRowIdx == stPos.m_iRowIdx && this->m_iRowIdx == stPos.m_iColIdx;
	};

	TANK_POS& operator+= (const TANK_POS& stPos)
	{
		this->m_iRowIdx += stPos.m_iRowIdx;
		this->m_iColIdx += stPos.m_iColIdx;
		return *this;
	};
};

class CTankGame : public CSceneBase
{
private:
	struct TANK_DATA
	{
		bool m_bDead;					//�Ƿ�����

		TANK_POS m_stTankPos;			//����λ��

		int m_iLastStep;				//��һ���ߵĲ���

		int m_iCurStep;					//��ǰ�ߵĲ���

		int m_iMaxStep;					//�����

		int m_iRetryNum;				//���Դ���������3���������һ������

		float m_iCurTime;				//����ѵȴ�ʱ��

		float m_iNextFireTime;			//��һ�������ʱ��

		int m_iDirection;				//��ǰ����
	};

	enum
	{
		TANK_MAXNUM = 4,					//̹���������

		TANK_REFRESH_TIME = 1000,			//ÿ��ˢ��һ��

		TANK_FIRE_MAXTIME = 5000,			//����ȴ��ʱ��

		TANK_RETRYMOVE_MAXCOUNT = 3,		//�����ƶ���������

		TANK_MOVE_MAXSTEP = ROW_NUM / 2,	//����ƶ�����
	};

public:
	CTankGame(CGameScene* pGameScene);
	~CTankGame();

	//---------------------    CSceneBase    ----------------------
	//��ʼ��
	void Init();

	//����
	void Play(float dt);

	//�ṩ��ÿ�θ��µ���Brick��Ϸ����ǰֻ����Ϸ������ʹ�ã���ȡ��ǰ�ı��Brick��������
	void GetCurPos(int& iRowIndex, int& iColIndex);

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

	//��������ʱ����̹��
	void CreateTank();

	//���ָ��λ���Ƿ���Ч
	bool CheckPosValid(const TANK_POS& stDestPos, int iDirection);

	//�������̹��λ���Ƿ����ص�
	bool CheckTankOverlap(const TANK_POS& stSrcPos, int iSrcDir, const TANK_POS& stDestPos, int iDestDir);

	//����̹������
	void UpdateTankPos();

private:
	TANK_DATA m_arrTankList[TANK_MAXNUM];		//̹��λ�ü���

	TANK_POS m_stSelf;							//�Լ�����λ��

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iLife;								//ʣ������

	int m_iScore;								//����

	int m_iCurTime;								//��ǰ�ѵȴ���ʱ��
};

