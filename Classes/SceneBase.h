#pragma once
#include "GlobalDef.h"

class CSceneBase
{
public:
	CSceneBase();
	~CSceneBase();

	//��ʼ��
	virtual void Init();

	//��Ϸ���У�����falseʱ��ʾ��Ϸ����
	virtual bool Play();

	//�ṩ��ÿ�θ��µ���Brick��Ϸ����ǰֻ����Ϸ������ʹ�ã���ȡ��ǰ�ı��Brick��������
	virtual void GetCurPos(int& iRowIndex, int& iColIndex);

	//��ȡ��ǰBrick״̬
	virtual bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	virtual SCENE_INDEX GetSceneType();

	//��ȡÿ��ִ����Play��ȴ���ʱ��
	virtual float GetRefreshTime();

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
};

