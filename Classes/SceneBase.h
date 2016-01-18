#pragma once
#include "GlobalDef.h"
#include "GameScene.h"

class CSceneBase
{
public:
	CSceneBase(CGameScene* pGameScene);
	~CSceneBase();

	//��ʼ��
	virtual void Init();

	//����
	virtual void Play(float dt);

	//�ṩ��ÿ�θ��µ���Brick��Ϸ����ǰֻ����Ϸ������ʹ�ã���ȡ��ǰ�ı��Brick��������
	virtual void GetCurPos(int& iRowIndex, int& iColIndex);

	//��ȡ��ǰBrick״̬
	virtual bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡС���������еķ���״̬
	virtual bool GetSmallBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	virtual SCENE_INDEX GetSceneType();

	//��
	virtual void OnLeft();

	//��
	virtual void OnRight();

	//��
	virtual void OnUp();

	//��
	virtual void OnDown();

	//Fire
	virtual void OnFire();

	//��ʼ
	virtual void OnStart();

protected:
	CGameScene* m_pGameScene;
};

