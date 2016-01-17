#pragma once
#include "GameBase.h"
class CChooseGame : public CGameBase
{
public:
	CChooseGame();
	~CChooseGame();

	//---------------------    GameBase    ----------------------
	//��ʼ��
	void Init();
	
	//��Ϸ���У�����falseʱ��ʾ��Ϸ����
	bool Play();

	//��ȡ��ǰBrick״̬
	bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	SCENE_INDEX GetSceneType();

	//��ȡÿ��ִ����Play��ȴ���ʱ��
	float GetRefreshTime();
	//---------------------    GameBase    ----------------------

private:
	typedef vector<int> TVECTOR_ANIMDATA;

	enum 
	{
		ANIM_NUM = 4,
	};

private:
	TVECTOR_ANIMDATA* m_pAnimData;		//ָ�򶯻����ݵ�ָ��

	int m_iAnimIndex;					//��ǰ��������

	bool m_bFirstAnim;					//��һ����������ȴ�
};

