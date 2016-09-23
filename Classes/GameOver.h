#pragma once
#include "SceneBase.h"

class CGameOver : public CSceneBase
{
public:
	CGameOver(CGameScene* pGameScene);
	~CGameOver();

	//---------------------    SceneBase    ----------------------
	//��ʼ��
	void Init();

	//����
	void Play(float dt);

	//��ȡ��ǰҪ����Brick��λ��
	void GetCurPos(int& iRowIndex, int& iColIndex);

	//��Ϸ����
	SCENE_INDEX GetSceneType();

	//����
	void OnLeftBtnPressed();

	//�Ұ���
	void OnRightBtnPressed();

	//�ϰ���
	void OnUpBtnPressed();

	//�°���
	void OnDownBtnPressed();

	//Fire����
	void OnFireBtnPressed();

	//��ʼ
	void OnStart();
	//---------------------    SceneBase    ----------------------

private:
	int m_iColIdx;
	int m_iRowIdx;

	int m_iBeginColIdx;
	int m_iBeginRowIdx;

	int m_iEndColIdx;
	int m_iEndRowIdx;

	int m_iDirection;

	int m_iAllCount;
};

