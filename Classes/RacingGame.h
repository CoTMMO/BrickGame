#pragma once
#include "cocos2d.h"
#include "GlobalDef.h"

class CRacingGame : public cocos2d::LayerColor
{
public:
	CRacingGame();
	~CRacingGame();

	static cocos2d::Scene* CreateScene();

	virtual bool init();

	//��ʼ������
	void InitData();

	//��ʼ��Brick
	void InitBrick();

	//����ָ���ĸ߶����޴������ư�ť
	void InitCotroller();

	//������Ϸ��������
	void PlayGameOverAnim();

	void update(float dt);

	CREATE_FUNC(CRacingGame);

private:
	cocos2d::Sprite* m_pBrick[ROW_NUM][COLUMN_NUM];		//Sprite����
	
	int m_arrCurBrick[ROW_NUM][COLUMN_NUM];				//��ǰBrick״̬

	int m_arrNextBrick[ROW_NUM][COLUMN_NUM];			//��һ��ˢ��ʱBirck״̬

	cocos2d::Size m_visibleSize;						//��Ļ��С

	int m_iColIdx;
	int m_iRowIdx;

	int m_iBeginColIdx;
	int m_iBeginRowIdx;
	int m_iEndColIdx;
	int m_iEndRowIdx;
	int m_iDirection;
	
	int m_iAllCount;
};

