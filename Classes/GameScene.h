#pragma once
#include "cocos2d.h"
#include "GlobalDef.h"

class CGameBase;

class CGameScene : public cocos2d::LayerColor
{
public:
	CGameScene();
	~CGameScene();

	static cocos2d::Scene* CreateScene();

	virtual bool init();

	//��ʼ������
	void InitData();

	//��ʼ��Brick
	void InitBrick();

	//����ָ���ĸ߶����޴������ư�ť
	void InitCotroller();

	//����������Ϸ����
	void CreateGameObj();

	void update(float dt);

	//���µ���Brick״̬
	void UpdateBrick(int iRowIndex, int iColIndex, bool bShowFlag);

	//��������Brick״̬
	void UpdateBricks();

	CREATE_FUNC(CGameScene);

private:
	typedef std::map<int, CGameBase*> TMAP_GAMEOBJ;
	typedef TMAP_GAMEOBJ::iterator TMAP_GAMEOBJ_ITER;

private:
	cocos2d::Sprite* m_pBrick[ROW_NUM][COLUMN_NUM];		//Sprite����

	cocos2d::Size m_visibleSize;						//��Ļ��С

	TMAP_GAMEOBJ m_mapGameObj;							//������Ϸ����ָ��

	int m_iGameIndex;									//��ǰ��Ϸ����
};

