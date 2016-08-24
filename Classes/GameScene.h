#pragma once
#include "BGGlobal.h"

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
	void UpdateBricks(int iStartRowIdx = -1, int iStartColIdx = -1, int iEndRowIdx = -1, int iEndColIdx = -1);

	//��������Brick
	void ResetBricks();

	//��ʾ�³���
	void RunScene(int iSceneIndex);

	//���·�����ʾ
	void UpdateScore(int iScore, bool bPlayEffect = true);

	//������߷���ʾ
	void UpdateHighScore(int iGameIdx, int iHighScore = 0);

	//���µȼ���ʾ
	void UpdateLevel(int iLevel);

	//�����ٶ���ʾ
	void UpdateSpeed(int iSpeed);

	//����С��������
	void UpdateSmallBricks();

	//��������СBrick
	void ResetSmallBricks();

	//��ʾ��ʾ
	void ShowTips(TIPS_TYPE enTipType);


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

	//��������������
	void CreateKeyListener();

	//����������Ϸ����
	void CreateGameObj();

	//֡����
	void update(float dt);

	//��ť��Ӧ  iBtnIndex ��ӦBTN_INDEX����
	void OnButtonEvent(Ref* pSender, Widget::TouchEventType enType, int iBtnIndex);

	//��ť����
	void OnButtonPressed(int iBtnIndex);

	//��ť�ͷ�
	void OnButtonReleased(int iBtnIndex);
	
	//��ť���� iBtnIndex ��ӦBTN_INDEX����
	void OnButtonClick(Ref* pSender, int iBtnIndex);

	//Change the background image
	void ChangeBGPic();

	//Change the play button state when game state changed
	void ChangePlayState(bool bPlay);

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
		BTN_GIVESCORE,
	};

	enum 
	{
		NUM_WIDTH = 22,				//���ֿ��

		NUM_HEIGHT = 36,			//���ָ߶�

		NUM_PADDING = 2,			//���ּ��

		BGPIC_COUNT = 2,			//����ͼƬ����

		CHANGEBG_INTERVAL = 1000,	//���ı����ļ��

		CLICK_INTERVAL = 2000,		//2��

		BTN_HEIGHT = 95,			//��ť�߶�
	};

private:
	Sprite* m_pArrBrick[ROW_NUM][COLUMN_NUM];			//Sprite����

	Size m_visibleSize;									//��Ļ��С

	TMAP_GAMEOBJ m_mapGameObj;							//������Ϸ����ָ��

	int m_iSceneIndex;									//��ǰ��Ϸ����

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];			//����ĵ�ǰ����Brick״̬

	Sprite* m_pArrSmallBrick[4][4];						//С��������

	//Label* m_pLevelLabel;								//�ȼ��ı�

	//Label* m_pSpeedLabel;								//�ٶ��ı�

	//Label* m_pScoreLabel;								//�����ı�

	//Label* m_pHighScoreLabel;							//��߷��ı�

	Sprite* m_pArrSpeed[2];								//�ٶ�Sprite����

	Sprite* m_pArrLevel[2];								//�ȼ�Sprite����

	Sprite* m_pArrScore[6];								//����Sprite����

	Sprite* m_pArrHighScore[6];							//��߷�Sprite����

	Sprite* m_pPauseSpr;								//��ͣͼ��

	Sprite* m_pBgSpr;									//����ͼƬ

	Sprite* m_pTipSpr;									//��ʾ

	MenuItemToggle* m_pStartBtn;						//Start Button

	bool m_bGamePause;									//��ͣ��־

	int m_iBgColor;										//��ǰ������ɫ��ţ�0��ɫ��>=1�Զ���

	double m_fClickTime;								//Click love btn time, two:change the background with WP

	double m_lfClickExitTime;							//��һ�ε���˳�ʱ��

	double m_lfClickResetTime;							//��һ�ε������ʱ��

	TIPS_TYPE m_enTipType;								//��ǰ��ʾ����
};

