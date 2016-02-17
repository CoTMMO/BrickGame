#pragma once
#include "SceneBase.h"
class CTetrisGame : public CSceneBase
{
public:
	CTetrisGame(CGameScene* pGameScene);
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
	void DeleteLine();

	//��������
	void DeleteSingleLine(int iRowIdx);

private:
	enum 
	{
		TETRIS_MAXSHAPE = 19,			//�����������

		BRICK_MOVE_INTERVAL = 500,		//�����ƶ��ȴ�ʱ��

		DELETE_LINE_ADD_SCORE = 10,		//�����мӷ�

		BTN_CHECK_INTERVAL = 60,		//��ť���ʱ����
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

	float m_fWaitTime;							//�ȴ�ʱ��

	bool m_bLeftBtnPressed;						//����ť����״̬

	bool m_bRightBtnPressed;					//�ҷ���ť����״̬

	bool m_bFastMoveDown;						//�Ƿ�����½�
};

