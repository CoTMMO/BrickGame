#pragma once
#include "BGGlobal.h"

class CSceneBase;

class CGameScene : public LayerColor
{
public:
	CGameScene();
	~CGameScene();

	static Scene* CreateScene();

	//init
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

	//��ʼ������
	void InitBgLayer();

	//��ʼ��UI:�������ȼ���
	void InitPortUI();

	//��ʼ������UI
	void InitLandUI();

	//����ָ���ĸ߶����޴������ư�ť
	void InitPortController();

	//����ָ���ĸ߶����޴������ư�ť
	void InitLandController();

	//��ȡ����Size
	Size GetBrickSize(bool bLandVisible);

	//��ȡ����Size
	Size GetNumSize();

	//��������������
	void CreateKeyListener();

	//����������Ϸ����
	void CreateGameObj();

	//֡����
	void update(float dt);

	//��ť��Ӧ  iBtnIndex ��ӦBTN_INDEX����
	void OnButtonEvent(Ref* pSender, Widget::TouchEventType enType, int iBtnIndex);

	//����λ�õ�����������
	bool AdjustClickIndex(Vec2 pos, int& nIndex);

	//��ť����
	void OnButtonPressed(int iBtnIndex);

	//��ť�ͷ�
	void OnButtonReleased(int iBtnIndex);
	
	//��ť���� iBtnIndex ��ӦBTN_INDEX����
	void OnButtonClick(Ref* pSender, int iBtnIndex);

	//Change the background image
	void ChangeColorMode();

	//Change the play button state when game state changed
	void ChangePlayState(bool bPlay);

	//��ȡ����Sprite
	Sprite* GetBrickSprite(int nRowIdx, int nColIdx, bool bSmallFlag, bool bLandFlag);

	//��ʼ����ʾ
	void InitTips();

	//�ı�Sprite
	void ChangeSprite(Sprite* pSprite, bool bNightMode);

	//�ı�MenuItemSprite
	void ChangeMenuItemSprite(MenuItemSprite* pMenuItemSpr, bool bNightMode);

	//�ı�MenuItemToggle
	void ChangeMenuItemToggle(MenuItemToggle* pMenuItemToggle, bool bNightMode);

	//�ı�Button
	void ChangeButton(Button* pButton, bool bNightMode);

	//����ģʽ����sprite����
	string GetSpriteNameByMode(const char* szName);

private:
	typedef map<int, CSceneBase*> TMAP_GAMEOBJ;
	typedef TMAP_GAMEOBJ::iterator TMAP_GAMEOBJ_ITER;

	//��ť����
	enum BTN_INDEX
	{
		BTN_INVALID = -1,
		BTN_UP,
		BTN_RIGHT,
		BTN_DOWN,
		BTN_LEFT,
		BTN_DIRMAX,
		BTN_FIRE = BTN_DIRMAX,
		BTN_START,
		BTN_SOUND,
		BTN_RESET,
		BTN_GIVESCORE,
	};

	enum 
	{
		NUM_PADDING = 2,			//���ּ��

		BGPIC_COUNT = 1,			//����ͼƬ����

		CHANGEBG_INTERVAL = 1000,	//���ı����ļ��

		CLICK_INTERVAL = 1200,		//1.2��

		BTN_HEIGHT = 95,			//��ť�߶�
	};

private:
	Node* m_pLandNode;									//������ĻNode

	Node* m_pPortNode;									//������ĻNode

	Sprite* m_pArrBrick[ROW_NUM][COLUMN_NUM];			//Sprite����

	Sprite* m_pArrBrickLand[ROW_NUM][COLUMN_NUM];		//������Ļ�µķ���Sprite����

	Size m_visibleSize;									//��Ļ��С

	TMAP_GAMEOBJ m_mapGameObj;							//������Ϸ����ָ��

	int m_iSceneIndex;									//��ǰ��Ϸ����

	bool m_arrBrickState[ROW_NUM][COLUMN_NUM];			//����ĵ�ǰ����Brick״̬

	Sprite* m_pArrSmallBrick[4][4];						//С��������

	Sprite* m_pArrSmallBrickLand[4][4];					//����С��������

	Sprite* m_pArrSpeed[2];								//�ٶ�Sprite����

	Sprite* m_pArrSpeedLand[2];							//�ٶ�Sprite����

	Sprite* m_pArrLevel[2];								//�ȼ�Sprite����

	Sprite* m_pArrLevelLand[2];							//�ȼ�Sprite����

	Sprite* m_pArrScore[6];								//����Sprite����

	Sprite* m_pArrScoreLand[6];							//����Sprite����

	Sprite* m_pArrHighScore[6];							//��߷�Sprite����

	Sprite* m_pArrHighScoreLand[6];						//��߷�Sprite����

	Sprite* m_pPauseSpr;								//��ͣͼ��

	Sprite* m_pPauseSprLand;							//������ͣͼ��

	Sprite* m_pTipSpr;									//��ʾ

	Sprite* m_pTipSprLand;								//��ʾ

	MenuItemToggle* m_pStartBtn;						//Start Button

	MenuItemToggle* m_pStartBtnLand;					//Start Button

	MenuItemToggle* m_pSoundBtn;						//Sound Button

	MenuItemToggle* m_pSoundBtnLand;					//Sound Button

	bool m_bGamePause;									//��ͣ��־

	int m_iBgColor;										//��ǰ������ɫ��ţ�0��ɫ��>=1�Զ���

	double m_fClickLoveTime;							//������ΰ�ťʱ��

	double m_lfClickExitTime;							//��һ�ε���˳�ʱ��

	double m_lfClickSndTime;							//��һ�ε������ʱ��

	double m_lfClickResetTime;							//��һ�ε������ʱ��

	TIPS_TYPE m_enTipType;								//��ǰ��ʾ����

	Vec2 m_oControllerCenterPos;						//����������λ��

	Size m_oControllerCenterSize;						//���������Ĵ�С

	Vec2 m_oControllerLandCenterPos;					//����������λ��

	Size m_oControllerLandCenterSize;					//���������Ĵ�С

	int m_nRecordBtnIdx;								//��¼��ť����

	Size m_oBrickSize;									//�����С

	Size m_oNumSize;									//�����С

	LayerColor* m_pBgLayer;								//������ɫ
};

