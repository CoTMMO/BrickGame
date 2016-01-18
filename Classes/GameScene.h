#pragma once
#include "GlobalDef.h"

class CSceneBase;

class CGameScene : public LayerColor
{
public:
	CGameScene();
	~CGameScene();

	static Scene* CreateScene();

	virtual bool init();

	//���µ���Brick״̬��bSmallBrickFlag �Ƿ����С���飬 bShowFlag��ʾ������
	void UpdateBrick(int iRowIndex, int iColIndex, bool bSmallBrickFlag, bool bShowFlag);

	//��������Brick״̬
	void UpdateBricks();

	//��������Brick
	void ResetBricks();

	//��ʾ�³���
	void ShowNewScene(int iSceneIndex);

	//���·�����ʾ
	void UpdateScore(int iScore);

	//���µȼ���ʾ
	void UpdateLevel(int iLevel);

	//�����ٶ���ʾ
	void UpdateSpeed(int iSpeed);

	//����С��������
	void UpdateSmallBricks();

	//��������СBrick
	void ResetSmallBricks();

	CREATE_FUNC(CGameScene);

private:
	//��ʼ������
	void InitData();

	//��ʼ��Brick
	void InitBrick();

	//��ʼ��UI:�������ȼ���
	void InitUI();

	//����ָ���ĸ߶����޴������ư�ť
	void InitCotroller();

	//����������Ϸ����
	void CreateGameObj();

	//֡����
	void update(float dt);

	//��ť��Ӧ  iBtnIndex ��ӦBTN_INDEX����
	void OnBtnClick(Ref* pSender, int iBtnIndex);

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
	Sprite* m_pArrBrick[ROW_NUM][COLUMN_NUM];				//Sprite����

	Size m_visibleSize;									//��Ļ��С

	TMAP_GAMEOBJ m_mapGameObj;							//������Ϸ����ָ��

	int m_iSceneIndex;									//��ǰ��Ϸ����

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];			//����ĵ�ǰ����Brick״̬

	Label* m_pScoreLabel;								//��������

	Label* m_pHighScoreLabel;							//��������

	Sprite* m_pArrSmallBrick[4][4];						//С��������

	Label* m_pLevelLabel;								//�ȼ�

	Label* m_pSpeedLabel;								//�ٶ�

	Sprite* m_pPauseSpr;								//��ͣͼ��
};

