#pragma once
#include "SceneBase.h"
class CTetrisGame : public CSceneBase
{
public:
	CTetrisGame(CGameScene* pGameScene, bool bMode);
	~CTetrisGame();

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

	//�°���
	void OnDownPressed();

	//���ͷ�
	void OnDownReleased();

	//Fire����
	void OnFireBtnPressed();

	//---------------------    CSceneBase    ----------------------


public:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//��������µķ�����״
	void RandNewShape();

	//�����ƶ�
	bool BrickMove(float dt);

	//���λ���Ƿ���Ч
	bool CheckBrickPos(int iShapeIdx, int iSrcRowIdx, int iSrcColIdx);

	//����
	void DeleteLine(bool bEnd);

	//��������
	void DeleteSingleLine(int iRowIdx);

	//��ȡ������״����
	inline int GetShapeCount();

	//��ȡָ���еķ�������
	int GetNextAddOrSubRowIdx(int iColIdx);

	//�����Լ�����ʾ״̬
	bool UpdateSelfState(float dt);

private:
	enum 
	{
		BRICK_MOVE_INTERVAL = 500,			//�����ƶ��ȴ�ʱ��

		DELETE_LINE_ADD_SCORE = 10,			//�����мӷ�

		BTN_CHECK_INTERVAL = 100,			//��ť���ʱ����

		BOOM_SHAPE_DELETE_LINE_COUNT = 2,	//��ը��������������

		SELF_FLASH_INTERVAL = 70,			//��˸ˢ��ʱ��
	};

private:
	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iScore;								//����

	bool m_arrBrick[ROW_NUM][COLUMN_NUM];		//����״̬����

	int m_iNextShape;							//��һ������

	int m_iCurShape;							//��ǰ����

	POSITION m_stCurPos;						//��ǰ����λ��

	GAME_STATE m_enGameState;					//��Ϸ״̬

	float m_fMoveDownTime;						//����ˢ��ʱ��

	float m_fBtnCheckTime;						//��ť���ȴ�ʱ��

	float m_fSelfFlashTime;						//��˸�ȴ�ʱ��

	bool m_bSelfShowFlag;						//��ʾ���

	bool m_bFlashFlag;							//�Ƿ����˸

	bool m_bLeftBtnPressed;						//����ť����״̬

	bool m_bRightBtnPressed;					//�ҷ���ť����״̬

	bool m_bFastMoveDown;						//�Ƿ�����½�

	bool m_bExtraMode;							//�Ƿ�������ģʽ
};

