#pragma once
#include "SceneBase.h"

class CChooseGame : public CSceneBase
{
public:
	CChooseGame(CGameScene* pGameScene);
	~CChooseGame();

	//---------------------    CSceneBase    ----------------------
	//��ʼ��
	void Init();
	
	//����
	void Play(float dt);

	//��ȡ��ǰBrick״̬
	bool GetBrickState(int iRowIndex, int iColIndex);

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

	//��ʼ
	void OnStart();

	//---------------------    CSceneBase    ----------------------

private:
	typedef vector<int> TVECTOR_ANIMDATA;

	enum 
	{
		ANIM_NUM = 4,

		REFRESH_INTERVAL = 1000,		//ˢ�¼��
	};

private:
	TVECTOR_ANIMDATA* m_pAnimData;		//ָ�򶯻����ݵ�ָ��

	int m_iGameIndex;					//��Ϸ����

	int m_iAnimIndex;					//��ǰ��������

	bool m_bFirstAnim;					//��һ����������ȴ�

	int m_iSpeed;						//�ٶ�

	int m_iLevel;						//�ȼ�

	float m_fCurTime;					//��ǰʱ��
};

