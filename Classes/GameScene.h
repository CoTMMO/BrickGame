#pragma once
#include "cocos2d.h"
#include "GlobalDef.h"

class CSceneBase;

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

	//��������Brick
	void ResetAllBricks();

	//��ť��Ӧ
	void OnBtnClick(Ref* pSender, int iBtnIndex);


	CREATE_FUNC(CGameScene);

private:
	typedef map<int, CSceneBase*> TMAP_GAMEOBJ;
	typedef TMAP_GAMEOBJ::iterator TMAP_GAMEOBJ_ITER;

	//��ť����
	enum BTN_INDEX
	{
		BTN_UP,
		BTN_RIGHT,
		BTN_DOWN,
		BTN_LEFT,
		BTN_FIRE,
		BTN_START,
		BTN_SOUND,
		BTN_RESET,
	};

private:
	cocos2d::Sprite* m_pBrick[ROW_NUM][COLUMN_NUM];		//Sprite����

	cocos2d::Size m_visibleSize;						//��Ļ��С

	TMAP_GAMEOBJ m_mapGameObj;							//������Ϸ����ָ��

	int m_iGameIndex;									//��ǰ��Ϸ����

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];			//����ĵ�ǰ����Brick״̬

	float m_fCurTime;									//��ǰ������һ�δ���Play��ʱ��
};

