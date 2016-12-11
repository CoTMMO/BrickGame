#include "GameScene.h"
#include "GameOver.h"
#include "GeneralManager.h"
#include "ChooseGame.h"
#include "RacingGame.h"
#include "FroggerGame.h"
#include "TankGame.h"
#include "SnakeGame.h"
#include "MatchGame.h"
#include "PinballGame.h"
#include "TetrisGame.h"
#include "FlappyBirdGame.h"
#include "HitBrickGame.h"
#include "SetupLayer.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
#include "AddBrickGame.h"

//���ư�ť������ű���
const float FLOAT_CONTROLLER_SCALE_MAX = 1.72f;
const float FLOAT_CONTROLLER_LAND_SCALE_MAX = 1.5f;

CGameScene::CGameScene() : m_iSceneIndex(SCENE_GAMEOVER), m_nTipType(TIPS_INVALID), m_nRecordBtnIdx(BTN_DIRMAX), m_iBgColor(0), 
							m_lfClickExitTime(0), //m_lfClickSndTime(0), m_lfClickResetTime(0), m_lfClickStartTime(0),
							m_oBrickSize(Size::ZERO), m_oNumSize(Size::ZERO), m_pSetupLayer(nullptr), m_pTipsLabel(nullptr), 
							m_pPortNode(nullptr), m_pPauseSpr(nullptr), m_pPauseSprLand(nullptr), m_pLandNode(nullptr), 
							m_visibleSize(Size::ZERO), m_bPauseFlag(false), m_pStartBtn(nullptr), m_pStartBtnLand(nullptr), 
							m_pSoundBtn(nullptr), m_pSoundBtnLand(nullptr), m_pBgLayer(nullptr), m_bOldSoundState(false),
							m_oControllerCenterPos(Vec2::ZERO), m_oControllerLandCenterPos(Vec2::ZERO), 
							m_oControllerCenterSize(Size::ZERO), m_oControllerLandCenterSize(Size::ZERO)
{
	for (int nRowIdx = 0; nRowIdx < ROW_NUM; ++nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
		{
			m_pArrBrick[nRowIdx][nColIdx] = nullptr;
			m_pArrBrickLand[nRowIdx][nColIdx] = nullptr;
		}
	}

	for (int nRowIdx = 0; nRowIdx < 4; ++nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < 4; ++nColIdx)
		{
			m_pArrSmallBrick[nRowIdx][nColIdx] = nullptr;
			m_pArrSmallBrickLand[nRowIdx][nColIdx] = nullptr;
		}
	}

	for (int nIdx = 0; nIdx < 2; ++nIdx)
	{
		m_pArrSpeed[nIdx] = nullptr;
		m_pArrSpeedLand[nIdx] = nullptr;
		m_pArrLevel[nIdx] = nullptr;
		m_pArrLevelLand[nIdx] = nullptr;
	}

	for (int nIdx = 0; nIdx < 6; ++nIdx)
	{
		m_pArrScore[nIdx] = nullptr;
		m_pArrScoreLand[nIdx] = nullptr;
		m_pArrHighScore[nIdx] = nullptr;
		m_pArrHighScoreLand[nIdx] = nullptr;
	}
}


CGameScene::~CGameScene()
{
	for (int i = 0; i < m_mapGameObj.size(); ++i)
	{
		CC_SAFE_DELETE(m_mapGameObj[i]);
	}
}


Scene* CGameScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CGameScene::create();
	scene->addChild(layer);
	return scene;
}


bool CGameScene::init()
{
	CC_RETURN_FALSE_IF(!LayerColor::initWithColor(Color4B::BLACK));

	//��ʼ����������ȡ���ݵ�
	InitData();

	//��ʼ������
	InitBgLayer();

	//UI��ʼ��
	InitPortUI();

	//����UI��ʼ��
	InitLandUI();

	//��ʼ������
	InitBrick();

	//��ʼ��������
	InitPortController();

	//���������
	InitLandController();

	//��������
	CreateKeyListener();

	//������Ϸ����
	CreateGameObj();

	//��ʼ����
	RunScene(SCENE_GAMEOVER);

	//������Ч
	PLAY_BGMUSIC(BGM_START, true);

	//֡����
	this->scheduleUpdate();

	return true;
}


void CGameScene::InitData()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
}


//��ʼ��Brick
void CGameScene::InitBrick()
{
	bool arrBrick[ROW_NUM][COLUMN_NUM] =
	{
		false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, true, true, true, true, true, false, false, false, false, false, false, false,
		false, false, false, true, false, false, false, true, false, false, false, false, false, false,
		false, false, false, true, true, true, true, false, false, false, false, false, false, false,
		false, false, false, true, false, false, false, true, false, false, false, false, false, false,
		false, false, true, true, true, true, true, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, true, true, false, false, true, true, true, true, true, false, false,
		false, false, false, false, true, false, false, false, false, false, false, true, false, false,
		false, false, false, false, true, false, false, true, true, true, true, true, false, false,
		false, false, false, false, true, false, false, true, false, false, false, false, false, false,
		false, false, false, false, true, false, false, true, false, false, false, true, false, false,
		false, false, false, true, true, true, false, true, true, true, true, true, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, true, true, true, true, false, false, false,
		false, false, false, false, false, false, true, false, false, false, false, false, false, false,
		false, false, false, false, false, false, true, false, false, false, true, true, false, false,
		false, false, false, false, false, false, true, false, false, false, false, true, false, false,
		false, false, false, false, false, false, false, true, true, true, true, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false,
	};

	Size brickSize = GetBrickSize(false);

	float fCurY = m_visibleSize.height;
	for (int i = 0; i < ROW_NUM; ++i)
	{
		float fCurX = 0;
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			bool bFlag = arrBrick[i][j];
			m_arrBrickState[i][j] = bFlag;
			Sprite* pSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode(bFlag ? "black.png" : "empty.png"));
			pSpr->setPosition(fCurX + brickSize.width * 1.0f / 2, fCurY - brickSize.height * 1.0f / 2);
			pSpr->setTag(i * ROW_NUM + j);
			m_pPortNode->addChild(pSpr);

			m_pArrBrick[i][j] = pSpr;
			fCurX += brickSize.width;
		}

		fCurY -= brickSize.height;
	}

	float fScale = m_visibleSize.width / ROW_NUM * 1.0f / brickSize.width;
	float fCurX = m_visibleSize.width;
	brickSize = GetBrickSize(true);
	for (int i = 0; i < ROW_NUM; ++i)
	{
		fCurY = m_visibleSize.height / 2 + COLUMN_NUM * brickSize.height / 2.0f;
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			bool bFlag = arrBrick[i][j];
			Sprite* pSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode(bFlag ? "black.png" : "empty.png"));
			pSpr->setScale(fScale);
			pSpr->setPosition(fCurX - brickSize.width * 0.5f, fCurY - brickSize.height * 0.5f);
			pSpr->setTag(i * ROW_NUM + j);
			m_pLandNode->addChild(pSpr);

			m_pArrBrickLand[i][j] = pSpr;
			fCurY -= brickSize.height;
		}
		fCurX -= brickSize.width;
	}
}


//��ʼ��UI:�������ȼ���
void CGameScene::InitPortUI()
{
	//ͼƬ����
	float fSpriteScale = 0.38f;
	string numZeroName = GetSpriteNameByMode("0.png");

	//�����
	m_pPortNode = Node::create();
	this->addChild(m_pPortNode);
	bool bVisible = GET_BOOLVALUE("PORTRAIT", true);
	m_pPortNode->setVisible(bVisible);

	//����
	Size brickSize = GetBrickSize(false);
	auto pScore = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("score.png"));
	pScore->setScale(fSpriteScale);
	Size scoreSize = GET_CONTENTSIZE(pScore) * fSpriteScale;
	float fCurX = (m_visibleSize.width - COLUMN_NUM * brickSize.width) / 2 + COLUMN_NUM * brickSize.width;
	float fCurY = m_visibleSize.height - scoreSize.height * 3 / 2;
	pScore->setPosition(fCurX, fCurY + scoreSize.height / 2);
	m_pPortNode->addChild(pScore);

	//����Sprite����
	Size numSize = GetNumSize();
	float fTempX = fCurX - NUM_PADDING * 2.5f - numSize.width * 3;
	fCurY -= numSize.height * 1.3f;
	for (int i = 0; i < 6; ++i)
	{
		m_pArrScore[i] = CREATE_SPRITEWITHNAME(numZeroName);
		m_pArrScore[i]->setPosition(fTempX + numSize.width * 0.5f, fCurY + numSize.height * 0.5f);
		m_pPortNode->addChild(m_pArrScore[i]);

		fTempX += numSize.width + NUM_PADDING;
	}

	//��߷�
	auto pHighScore = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("hiscore.png"));
	pHighScore->setScale(fSpriteScale);
	Size highScoreSize = GET_CONTENTSIZE(pHighScore) * fSpriteScale;
	fCurY -= highScoreSize.height * 1.5f;
	pHighScore->setPosition(fCurX, fCurY + highScoreSize.height * 0.5f);
	m_pPortNode->addChild(pHighScore);

	//��߷�Sprite����
	fCurY -= numSize.height * 1.3f;
	fTempX = fCurX - NUM_PADDING * 2.5f - numSize.width * 3;
	for (int i = 0; i < 6; ++i)
	{
		m_pArrHighScore[i] = CREATE_SPRITEWITHNAME(numZeroName);
		m_pArrHighScore[i]->setPosition(fTempX + numSize.width * 0.5f, fCurY + numSize.height * 0.5f);
		m_pPortNode->addChild(m_pArrHighScore[i]);

		fTempX += numSize.width + NUM_PADDING;
	}

	//С��������
	float fBrickScale = 0.7f;
	float fPadding = 2;
	fCurY -= numSize.height * 0.5f;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float fX = fCurX + (brickSize.height * fBrickScale + fPadding) * (j - 1.5f);
			m_pArrSmallBrick[i][j] = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("empty.png"));
			m_pArrSmallBrick[i][j]->setScale(fBrickScale);
			m_pArrSmallBrick[i][j]->setPosition(fX, fCurY - brickSize.height * fBrickScale / 2);
			m_pPortNode->addChild(m_pArrSmallBrick[i][j]);
		}

		fCurY -= brickSize.height * fBrickScale + fPadding;
	}

	//�ٶ�
	auto pSpeed = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("speed.png"));
	pSpeed->setScale(fSpriteScale);
	Size speedSize = GET_CONTENTSIZE(pSpeed);
	fCurY -= speedSize.height;
	pSpeed->setPosition(fCurX, fCurY + speedSize.height / 2);
	m_pPortNode->addChild(pSpeed);

	fCurY -= numSize.height;
	m_pArrSpeed[0] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrSpeed[0]->setPosition(fCurX, fCurY + numSize.height / 2);
	m_pPortNode->addChild(m_pArrSpeed[0]);

	m_pArrSpeed[1] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrSpeed[1]->setPosition(fCurX, fCurY + numSize.height / 2);
	m_pPortNode->addChild(m_pArrSpeed[1]);
	m_pArrSpeed[1]->setVisible(false);

	fCurY -= numSize.height + NUM_PADDING * 10;
	m_pArrLevel[0] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrLevel[0]->setPosition(fCurX, fCurY + numSize.height / 2);
	m_pPortNode->addChild(m_pArrLevel[0]);

	m_pArrLevel[1] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrLevel[1]->setPosition(fCurX, fCurY + numSize.height / 2);
	m_pPortNode->addChild(m_pArrLevel[1]);
	m_pArrLevel[1]->setVisible(false);

	//�ȼ�
	auto pLevel = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("level.png"));
	pLevel->setScale(fSpriteScale);
	Size levelSize = GET_CONTENTSIZE(pLevel);
	fCurY -= levelSize.height;
	pLevel->setPosition(fCurX, fCurY + levelSize.height / 2);
	m_pPortNode->addChild(pLevel);

	//��ͣͼ��
	//float fPauseScale = fSpriteScale - 0.04f;
	m_pPauseSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("tea.png"));
	m_pPauseSpr->setScale(fSpriteScale);
	Size pauseSize = GET_CONTENTSIZE(m_pPauseSpr) * fSpriteScale;
	fCurY -= pauseSize.height;
	m_pPauseSpr->setPosition(fCurX, fCurY + pauseSize.height / 2);
	m_pPortNode->addChild(m_pPauseSpr);

	//Ĭ�Ϸ���ͣ״̬
	m_pPauseSpr->setVisible(m_bPauseFlag);
}


void CGameScene::InitLandUI()
{
	//�����
	m_pLandNode = Node::create();
	this->addChild(m_pLandNode);
	bool bVisible = GET_BOOLVALUE("PORTRAIT", true);
	m_pLandNode->setVisible(!bVisible);

	//ͼƬ����
	float fSpriteScale = 0.35f;
	string numZeroName = GetSpriteNameByMode("0.png");

	//Yλ��
	Size brickSize = GetBrickSize(true);
	float fUIPadding = (m_visibleSize.height - brickSize.width * COLUMN_NUM) * 0.5f;
	float fCurY = fUIPadding + brickSize.width * COLUMN_NUM;

	//����
	auto pScore = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("score.png"));
	pScore->setRotation(90);
	pScore->setScale(fSpriteScale);
	Size scoreSize = GET_CONTENTSIZE(pScore) * fSpriteScale;
	float fCurX = m_visibleSize.width - scoreSize.height * 1.4f;
	pScore->setPosition(fCurX + scoreSize.height * 0.5f, fCurY + fUIPadding * 0.5f);
	m_pLandNode->addChild(pScore);

	//����Sprite����
	Size numSize = GetNumSize();
	fCurX -= numSize.height + 5;
	for (int i = 0; i < 6; ++i)
	{
		Sprite* pSpr = CREATE_SPRITEWITHNAME(numZeroName);
		pSpr->setRotation(90);
		pSpr->setPosition(fCurX + numSize.height * 0.5f, fCurY + fUIPadding * 0.5f - (numSize.width + NUM_PADDING) * (i - 2.5f));
		m_pLandNode->addChild(pSpr);
		m_pArrScoreLand[i] = pSpr;
	}

	//��߷�
	auto pHighScore = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("hiscore.png"));
	pHighScore->setScale(fSpriteScale);
	pHighScore->setRotation(90);
	Size highScoreSize = GET_CONTENTSIZE(pHighScore) * fSpriteScale;
	fCurX -= highScoreSize.height * 1.4f;
	pHighScore->setPosition(fCurX + highScoreSize.height * 0.5f, fCurY + fUIPadding * 0.5f);
	m_pLandNode->addChild(pHighScore);

	//��߷�Sprite����
	fCurX -= numSize.height + 5;
	for (int i = 0; i < 6; ++i)
	{
		Sprite* pSpr = CREATE_SPRITEWITHNAME(numZeroName);
		pSpr->setRotation(90);
		pSpr->setPosition(fCurX + numSize.height * 0.5f, fCurY + fUIPadding * 0.5f - (numSize.width + NUM_PADDING) * (i - 2.5f));
		m_pLandNode->addChild(pSpr);
		m_pArrHighScoreLand[i] = pSpr;
	}

	//С��������
	fCurX = m_visibleSize.width - brickSize.width * 0.5f;
	float fBrickScale = 0.75f;
	float fBrickPadding = 2;
	float fSmallBrickWidth = GetBrickSize(true).width * fBrickScale;
	float fSmallBrickHeight = GetBrickSize(true).height * fBrickScale;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Sprite* pSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("empty.png"));
			pSpr->setScale(fBrickScale);
			pSpr->setPosition(fCurX - fSmallBrickWidth * 0.5f, fUIPadding * 0.5f - (fSmallBrickHeight + fBrickPadding) * (j - 1.5f));
			m_pLandNode->addChild(pSpr);

			m_pArrSmallBrickLand[i][j] = pSpr;
		}

		fCurX -= fSmallBrickWidth + fBrickPadding;
	}


	//�ٶ�
	fCurX -= brickSize.width + 20;
	m_pArrSpeedLand[0] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrSpeedLand[0]->setPosition(fCurX + numSize.height * 0.5f, fUIPadding * 0.5f + numSize.width * 2.2f);
	m_pArrSpeedLand[0]->setRotation(90);
	m_pLandNode->addChild(m_pArrSpeedLand[0]);

	m_pArrSpeedLand[1] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrSpeedLand[1]->setPosition(fCurX + numSize.height * 0.5f, fUIPadding * 0.5f + numSize.width * 2.2f);
	m_pArrSpeedLand[1]->setRotation(90);
	m_pLandNode->addChild(m_pArrSpeedLand[1]);
	m_pArrSpeedLand[1]->setVisible(false);

	//�ؿ�
	m_pArrLevelLand[0] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrLevelLand[0]->setPosition(fCurX + numSize.height * 0.5f, fUIPadding * 0.5f - numSize.width * 2.2f);
	m_pArrLevelLand[0]->setRotation(90);
	m_pLandNode->addChild(m_pArrLevelLand[0]);

	m_pArrLevelLand[1] = CREATE_SPRITEWITHNAME(numZeroName);
	m_pArrLevelLand[1]->setPosition(fCurX + numSize.height * 0.5f, fUIPadding * 0.5f - numSize.width * 2.2f);
	m_pArrLevelLand[1]->setRotation(90);
	m_pLandNode->addChild(m_pArrLevelLand[1]);
	m_pArrLevelLand[1]->setVisible(false);

	//��ͣͼ��
	m_pPauseSprLand = CREATE_SPRITEWITHNAME(numZeroName);
	m_pPauseSprLand->setScale(fSpriteScale);
	m_pPauseSprLand->setRotation(90);
	Size pauseSize = GET_CONTENTSIZE(m_pPauseSprLand) * fSpriteScale;
	m_pPauseSprLand->setPosition(m_visibleSize.width / 4.2f, fUIPadding * 0.5f);
	m_pLandNode->addChild(m_pPauseSprLand);

	//Ĭ�Ϸ���ͣ״̬
	m_pPauseSprLand->setVisible(m_bPauseFlag);
}

void CGameScene::InitPortController()
{
	//��ʼ
	Sprite* pPlaySpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("play.png"));
	Sprite* pPauseSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("pause.png"));
	float fSpriteScale = 0.4f;
	m_pStartBtn = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_START),
		MenuItemSprite::create(pPlaySpr, pPlaySpr, nullptr),
		MenuItemSprite::create(pPauseSpr, pPauseSpr, nullptr),
		nullptr
		);
	m_pStartBtn->setScale(fSpriteScale);
	Size startBtnSize = m_pStartBtn->getContentSize() * fSpriteScale;

	//��ȡ����״̬
	Sprite* pSndOnSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("sound_on.png"));
	Sprite* pSndOffSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("sound_off.png"));
	bool bSoundState = GET_BOOLVALUE("SOUND", true);
	auto pSoundOnMenu = MenuItemSprite::create(
		pSndOnSpr,
		pSndOnSpr,
		nullptr
		);
	auto pSoundOffMenu = MenuItemSprite::create(
		pSndOffSpr,
		pSndOffSpr,
		nullptr
		);

	//��������
	m_pSoundBtn = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_SOUND),
		bSoundState ? pSoundOnMenu : pSoundOffMenu,
		bSoundState ? pSoundOffMenu : pSoundOnMenu,
		nullptr
		);
	m_pSoundBtn->setScale(fSpriteScale);
	Size soundBtnSize = m_pSoundBtn->getContentSize() * fSpriteScale;

	//����
	Sprite* pResetSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("reset.png"));
	auto resetBtn = MenuItemSprite::create(
		pResetSpr,
		pResetSpr,
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_RESET)
		);
	resetBtn->setScale(fSpriteScale);
	Size resetBtnSize = resetBtn->getContentSize() * fSpriteScale;

	//���⹦��
	Sprite* pStarSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("setup.png"));
	auto extremeBtn = MenuItemSprite::create(
		pStarSpr,
		pStarSpr,
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_GIVESCORE)
		);
	extremeBtn->setScale(fSpriteScale);
	Size themeBtnSize = extremeBtn->getContentSize() * fSpriteScale;

	//�ײ���ť�߶�
	//fHeight = (fTopPosY - soundBtnSize.height) / 2 + soundBtnSize.height / 2;
	//��ť���
	float fBtnPadding = soundBtnSize.width * 1.2f;

	//λ��
	float fSmallBtnTopHeight = soundBtnSize.height * 1.3f;
	float fSmallBtnCenterHeight = fSmallBtnTopHeight - soundBtnSize.height / 3.1f;
	m_pSoundBtn->setPosition(m_visibleSize.width / 2 - fBtnPadding / 2 - soundBtnSize.width / 2, fSmallBtnCenterHeight);
	m_pStartBtn->setPosition(m_visibleSize.width / 2 - fBtnPadding * 3 / 2 - soundBtnSize.width - startBtnSize.width / 2, fSmallBtnCenterHeight);
	resetBtn->setPosition(m_visibleSize.width / 2 + fBtnPadding / 2 + resetBtnSize.width / 2, fSmallBtnCenterHeight);
	extremeBtn->setPosition(m_visibleSize.width / 2 + fBtnPadding * 3 / 2 + resetBtnSize.width + themeBtnSize.width / 2, fSmallBtnCenterHeight);

	auto menu = Menu::create(m_pStartBtn, m_pSoundBtn, resetBtn, extremeBtn, nullptr);
	menu->setPosition(Vec2::ZERO);
	m_pPortNode->addChild(menu);


	//ʣ��߶ȣ����ڵ������ư�ťλ��
	float fHeight = m_visibleSize.height - GetBrickSize(false).height * ROW_NUM;

	//��ť���Ŵ�С
	fBtnPadding = 2.0f;
	float fControllerPadding = 10;
	float fBtnScale = (fHeight - fSmallBtnTopHeight - fControllerPadding * 2) * 1.0f / 2 / BTN_HEIGHT;
	//log("fBtnScale=%f  fRemainHeight=%f", fBtnScale, fHeight - fSmallBtnTopHeight);
	
	//���µ������
	if (fBtnScale > FLOAT_CONTROLLER_SCALE_MAX)
	{
		fBtnScale = FLOAT_CONTROLLER_SCALE_MAX;
		fControllerPadding = (fHeight - fSmallBtnTopHeight - FLOAT_CONTROLLER_SCALE_MAX * BTN_HEIGHT * 2) / 2;
		//log("fControllerPadding=%f", fControllerPadding);
	}

	float fTopPosY = fHeight - fControllerPadding;

	//��
	string strBtn0Name = GetSpriteNameByMode("btn_0.png");
	Button* pUpBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pUpBtn->setScale(fBtnScale);
	pUpBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_UP));
	Size upBtnSize = pUpBtn->getContentSize() * fBtnScale;

	//��
	Button* pRightBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pRightBtn->setScale(fBtnScale);
	pRightBtn->setRotation(90);
	pRightBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_RIGHT));
	Size rightBtnSize = pRightBtn->getContentSize() * fBtnScale;

	//��
	Button* pDownBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pDownBtn->setScale(fBtnScale);
	pDownBtn->setRotation(180);
	pDownBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_DOWN));
	Size downBtnSize = pDownBtn->getContentSize() * fBtnScale;

	//��
	Button* pLeftBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pLeftBtn->setScale(fBtnScale);
	pLeftBtn->setRotation(-90);
	pLeftBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_LEFT));
	Size leftBtnSize = pLeftBtn->getContentSize() * fBtnScale;

	//Fire
	float fFireScale = 1.4f;
	Button* pFireBtn = Button::create(GetSpriteNameByMode("fire_0.png"), GetSpriteNameByMode("fire_1.png"), "", Widget::TextureResType::PLIST);
	pFireBtn->setScale(fFireScale);
	pFireBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_FIRE));
	Size fireBtnSize = pFireBtn->getContentSize() * fFireScale;

	//����λ��
	pLeftBtn->setPosition(Vec2(upBtnSize.height * 0.6f + fBtnPadding, fTopPosY - upBtnSize.height));
	pRightBtn->setPosition(Vec2(upBtnSize.height * 1.6f - fBtnPadding, fTopPosY - upBtnSize.height));
	pDownBtn->setPosition(Vec2(upBtnSize.height * 1.1f, fTopPosY - upBtnSize.height * 1.5f + fBtnPadding));
	pUpBtn->setPosition(Vec2(upBtnSize.height * 1.1f, fTopPosY - upBtnSize.height * 0.5f - fBtnPadding));
	pFireBtn->setPosition(Vec2(m_visibleSize.width - fireBtnSize.width * 0.8f, fTopPosY - upBtnSize.height));

	//����λ��
	m_oControllerCenterPos = Vec2(upBtnSize.height * 1.1f, fTopPosY - upBtnSize.height);
	m_oControllerCenterSize = Size(upBtnSize.width, upBtnSize.width);

	m_pPortNode->addChild(pLeftBtn);
	m_pPortNode->addChild(pRightBtn);
	m_pPortNode->addChild(pDownBtn);
	m_pPortNode->addChild(pUpBtn);
	m_pPortNode->addChild(pFireBtn);
}


void CGameScene::InitLandController()
{
	//��ʼ
	Sprite* pPlaySpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("play.png"));
	Sprite* pPauseSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("pause.png"));
	float fSpriteScale = 0.4f;
	m_pStartBtnLand = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_START),
		MenuItemSprite::create(pPlaySpr, pPlaySpr, nullptr),
		MenuItemSprite::create(pPauseSpr, pPauseSpr, nullptr),
		nullptr
		);
	m_pStartBtnLand->setScale(fSpriteScale);
	m_pStartBtnLand->setRotation(90);
	Size startBtnSize = m_pStartBtnLand->getContentSize() * fSpriteScale;

	//��ȡ����״̬
	Sprite* pSndOnSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("sound_on.png"));
	Sprite* pSndOffSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("sound_off.png"));
	bool bSoundState = GET_BOOLVALUE("SOUND", true);
	auto pSoundOnMenu = MenuItemSprite::create(
		pSndOnSpr,
		pSndOnSpr,
		nullptr
		);
	auto pSoundOffMenu = MenuItemSprite::create(
		pSndOffSpr,
		pSndOffSpr,
		nullptr
		);

	//��������
	m_pSoundBtnLand = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_SOUND),
		bSoundState ? pSoundOnMenu : pSoundOffMenu,
		bSoundState ? pSoundOffMenu : pSoundOnMenu,
		nullptr
		);
	m_pSoundBtnLand->setScale(fSpriteScale);
	m_pSoundBtnLand->setRotation(90);
	Size soundBtnSize = m_pSoundBtnLand->getContentSize() * fSpriteScale;

	//����
	Sprite* pResetSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("reset.png"));
	auto resetBtn = MenuItemSprite::create(
		pResetSpr,
		pResetSpr,
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_RESET)
		);
	resetBtn->setScale(fSpriteScale);
	resetBtn->setRotation(90);
	Size resetBtnSize = resetBtn->getContentSize() * fSpriteScale;

	//���⹦��
	Sprite* pStarSpr = CREATE_SPRITEWITHNAME(GetSpriteNameByMode("setup.png"));
	auto extremeBtn = MenuItemSprite::create(
		pStarSpr,
		pStarSpr,
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_GIVESCORE)
		);
	extremeBtn->setScale(fSpriteScale);
	extremeBtn->setRotation(90);
	Size extremeBtnSize = extremeBtn->getContentSize() * fSpriteScale;

	//λ��
	float fPosX = startBtnSize.height * 0.8f;
	float fBrickBottomHeight = (m_visibleSize.height - COLUMN_NUM * GetBrickSize(true).width) * 0.5f;
	float fBrickTopHeight = fBrickBottomHeight + COLUMN_NUM * GetBrickSize(true).width;
	float fUpPadding = (m_visibleSize.height - fBrickTopHeight - startBtnSize.width - soundBtnSize.width) / 3.0f;
	float fDownPadding = (fBrickBottomHeight - resetBtnSize.width - extremeBtnSize.width) / 3.0f;

	m_pStartBtnLand->setPosition(fPosX, m_visibleSize.height - fUpPadding - startBtnSize.width * 0.5f);
	m_pSoundBtnLand->setPosition(fPosX, fBrickTopHeight + fUpPadding + soundBtnSize.width * 0.5f);
	resetBtn->setPosition(fPosX, fBrickBottomHeight - fDownPadding - resetBtnSize.width * 0.5f);
	extremeBtn->setPosition(fPosX, fDownPadding + extremeBtnSize.width * 0.5f);

	auto menu = Menu::create(m_pStartBtnLand, m_pSoundBtnLand, resetBtn, extremeBtn, nullptr);
	menu->setPosition(Vec2::ZERO);
	m_pLandNode->addChild(menu);

	//���µ������
	string strBtn0Name = GetSpriteNameByMode("btn_0.png");
	Sprite* pSampleBtn = CREATE_SPRITEWITHNAME(strBtn0Name);
	Size sampleBtnSize = GET_CONTENTSIZE(pSampleBtn);
	float fBtnScale = (fBrickBottomHeight - 40) / sampleBtnSize.height / 2.0f;
	if (fBtnScale > FLOAT_CONTROLLER_SCALE_MAX)
	{
		fBtnScale = FLOAT_CONTROLLER_SCALE_MAX;
	}
	sampleBtnSize = sampleBtnSize * fBtnScale;

	//���
	float fBtnPadding = 2.0f;
	float fHeightPadding = (fBrickBottomHeight - sampleBtnSize.height * 2 - fBtnPadding * 2) * 0.5f;

	//��
	Button* pLeftBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pLeftBtn->setScale(fBtnScale);
	pLeftBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_LEFT));

	//��
	Button* pUpBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pUpBtn->setRotation(90);
	pUpBtn->setScale(fBtnScale);
	pUpBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_UP));

	//��
	Button* pRightBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pRightBtn->setScale(fBtnScale);
	pRightBtn->setRotation(180);
	pRightBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_RIGHT));

	//��
	Button* pDownBtn = Button::create(strBtn0Name, strBtn0Name, "", Widget::TextureResType::PLIST);
	pDownBtn->setScale(fBtnScale);
	pDownBtn->setRotation(270);
	pDownBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_DOWN));

	//Fire
	float fFireScale = 1.5f;
	Button* pFireBtn = Button::create(GetSpriteNameByMode("fire_0.png"), GetSpriteNameByMode("fire_1.png"), "", Widget::TextureResType::PLIST);
	pFireBtn->setScale(fFireScale);
	pFireBtn->setRotation(90);
	Size fireBtnSize = GET_CONTENTSIZE(pFireBtn) * fFireScale;
	pFireBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_FIRE));

	//����λ��
	float fTopCenterY = sampleBtnSize.height + fBrickTopHeight + fHeightPadding;
	pLeftBtn->setPosition(Vec2(m_visibleSize.width * 0.38f, fTopCenterY + sampleBtnSize.height * 0.5f - fBtnPadding));
	pRightBtn->setPosition(Vec2(m_visibleSize.width * 0.38f, fTopCenterY - sampleBtnSize.height * 0.5f + fBtnPadding));
	pDownBtn->setPosition(Vec2(m_visibleSize.width * 0.38f - sampleBtnSize.height * 0.5f + fBtnPadding, fTopCenterY));
	pUpBtn->setPosition(Vec2(m_visibleSize.width * 0.38f + sampleBtnSize.height * 0.5f - fBtnPadding, fTopCenterY));
	pFireBtn->setPosition(Vec2(m_visibleSize.width * 0.38f, fBrickBottomHeight * 0.5f));

	//����λ��
	m_oControllerLandCenterPos = Vec2(m_visibleSize.width * 0.38f, fTopCenterY);
	m_oControllerLandCenterSize = Size(sampleBtnSize.width, sampleBtnSize.width);

	m_pLandNode->addChild(pLeftBtn);
	m_pLandNode->addChild(pRightBtn);
	m_pLandNode->addChild(pDownBtn);
	m_pLandNode->addChild(pUpBtn);
	m_pLandNode->addChild(pFireBtn);
}


Size CGameScene::GetBrickSize(bool bLandVisible)
{
	if (m_oBrickSize.equals(Size::ZERO))
	{
		Sprite* pSpr = CREATE_SPRITEWITHNAME("empty.png");
		m_oBrickSize = GET_CONTENTSIZE(pSpr);
	}

	if (bLandVisible)
	{
		return m_oBrickSize * (m_visibleSize.width / ROW_NUM * 1.0f / m_oBrickSize.width);
	}

	return m_oBrickSize;
}


Size CGameScene::GetNumSize()
{
	if (m_oNumSize.equals(Size::ZERO))
	{
		Sprite* pSpr = CREATE_SPRITEWITHNAME("0.png");
		m_oNumSize = GET_CONTENTSIZE(pSpr);
	}

	return m_oNumSize;
}


//��������������
void CGameScene::CreateKeyListener()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (EventKeyboard::KeyCode::KEY_A == keyCode)
		{
			//log("A Pressed");
			OnButtonPressed(BTN_LEFT);
		}
		else if (EventKeyboard::KeyCode::KEY_D == keyCode)
		{
			//log("D Pressed");
			OnButtonPressed(BTN_RIGHT);
		}
		else if (EventKeyboard::KeyCode::KEY_S == keyCode)
		{
			//log("S Pressed");
			OnButtonPressed(BTN_DOWN);
		}
		else if (EventKeyboard::KeyCode::KEY_W == keyCode)
		{
			//log("W Pressed");
			OnButtonPressed(BTN_UP);
		}
		else if (EventKeyboard::KeyCode::KEY_K == keyCode)
		{
			//log("K Pressed");
			OnButtonPressed(BTN_FIRE);
		}
		else if (EventKeyboard::KeyCode::KEY_SPACE == keyCode)
		{
			OnButtonClick(nullptr, BTN_START);
		}
	};

	keyListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (EventKeyboard::KeyCode::KEY_A == keyCode)
		{
			//log("A Released");
			OnButtonReleased(BTN_LEFT);
		}
		else if (EventKeyboard::KeyCode::KEY_D == keyCode)
		{
			//log("D Released");
			OnButtonReleased(BTN_RIGHT);
		}
		else if (EventKeyboard::KeyCode::KEY_S == keyCode)
		{
			//log("S Released");
			OnButtonReleased(BTN_DOWN);
		}
		else if (EventKeyboard::KeyCode::KEY_W == keyCode)
		{
			//log("W Released");
			OnButtonReleased(BTN_UP);
		}
		else if (EventKeyboard::KeyCode::KEY_K == keyCode)
		{
			//log("K Released");
			OnButtonReleased(BTN_FIRE);
		}
		else if (EventKeyboard::KeyCode::KEY_RETURN == keyCode ||
			EventKeyboard::KeyCode::KEY_ESCAPE == keyCode ||
			EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
		{
			LaunchQuitRoutine();
		}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
		else if (EventKeyboard::KeyCode::KEY_PLAY == keyCode)
		{
			LaunchQuitRoutine();
		}
		else if (EventKeyboard::KeyCode::KEY_ENTER == keyCode)
		{
			if (m_iSceneIndex == SCENE_TETRIS || m_iSceneIndex == SCENE_TETRIS2)
			{
				//��������
				m_mapGameObj[m_iSceneIndex]->SaveGameData();
			}
		}
#endif
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}


void CGameScene::update(float dt)
{
//	if (m_fClickLoveTime >= 0)
//	{
//		m_fClickLoveTime += dt * 1000;
//		if (m_fClickLoveTime > CHANGEBG_INTERVAL)
//		{
//			m_fClickLoveTime = -1;
//#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8 
//			GLView::sharedOpenGLView()->OnGiveScore();
//#endif
//
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//			JniMethodInfo minfo;
//			bool bFuncExistFlag = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "GiveScore", "()V");
//			//log("bFuncExistFlag=%d", bFuncExistFlag);
//			if (bFuncExistFlag)
//			{
//				minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
//			}
//#endif
//		}
//	}

	m_mapGameObj[m_iSceneIndex]->Play(dt * 1000);
}


//����������Ϸ����
void CGameScene::CreateGameObj()
{
	//��Ϸ����
	CGameOver* pGameOver = new CGameOver(this);
	m_mapGameObj[SCENE_GAMEOVER] = pGameOver;

	//ѡ����Ϸ
	CChooseGame* pChooseGame = new CChooseGame(this);
	m_mapGameObj[SCENE_CHOOSEGAME] = pChooseGame;

	//̹�˴�ս
	CTankGame* pTankGame = new CTankGame(this);
	m_mapGameObj[SCENE_TANK] = pTankGame;

	//����
	CRacingGame* pRacingGame = new CRacingGame(this);
	m_mapGameObj[SCENE_RACING] = pRacingGame;

	//̰����
	CSnakeGame* pSnakeGame = new CSnakeGame(this);
	m_mapGameObj[SCENE_SNAKE] = pSnakeGame;

	//ƥ��
	CMatchGame* pMatchGame = new CMatchGame(this);
	m_mapGameObj[SCENE_MATCH] = pMatchGame;

	//���ܹ���
	CFroggerGame* pFroggerGame = new CFroggerGame(this);
	m_mapGameObj[SCENE_FROGGER] = pFroggerGame;

	//����
	CPinballGame* pPinballGame = new CPinballGame(this, false);
	m_mapGameObj[SCENE_PINBALL] = pPinballGame;

	//����˹����
	CTetrisGame* pTetrisGame = new CTetrisGame(this, false);
	m_mapGameObj[SCENE_TETRIS] = pTetrisGame;

	//FlappyBird
	CFlappyBirdGame* pFlappyBirdGame = new CFlappyBirdGame(this);
	m_mapGameObj[SCENE_FLAPPYBIRD] = pFlappyBirdGame;

	//����˹����2
	CTetrisGame* pTetrisGame2 = new CTetrisGame(this, true);
	m_mapGameObj[SCENE_TETRIS2] = pTetrisGame2;

	//����2
	CPinballGame* pPinballGame2 = new CPinballGame(this, true);
	m_mapGameObj[SCENE_PINBALL2] = pPinballGame2;

	//��ש��
	CHitBrickGame* pHitBrickGame = new CHitBrickGame(this);
	m_mapGameObj[SCENE_HITBRICK] = pHitBrickGame;

	//��ש��
	CAddBrickGame* pAddBrickGame = new CAddBrickGame(this);
	m_mapGameObj[SCENE_ADDBRICK] = pAddBrickGame;
}


//���µ���Brick״̬
void CGameScene::UpdateBrick(int iRowIndex, int iColIndex, bool bSmallBrickFlag, bool bShowFlag)
{
	Sprite* pLandBrick = GetBrickSprite(iRowIndex, iColIndex, bSmallBrickFlag, true);
	Sprite* pBrick = GetBrickSprite(iRowIndex, iColIndex, bSmallBrickFlag, false);
	if (pLandBrick == nullptr || pBrick == nullptr)
	{
		return;
	}

	if (!bSmallBrickFlag)
	{
		//����״̬��¼
		m_arrBrickState[iRowIndex][iColIndex] = bShowFlag;
	}

	//������ʾ������״̬
	if (bShowFlag)
	{
		string strBlackName = GetSpriteNameByMode("black.png");
		pBrick->setSpriteFrame(strBlackName);
		pLandBrick->setSpriteFrame(strBlackName);
	}
	else
	{
		string strEmptyName = GetSpriteNameByMode("empty.png");
		pBrick->setSpriteFrame(strEmptyName);
		pLandBrick->setSpriteFrame(strEmptyName);
	}
}


//��������Brick״̬
void CGameScene::UpdateBricks( int iStartRowIdx /*= -1*/, int iStartColIdx /*= -1*/, int iEndRowIdx /*= -1*/, int iEndColIdx /*= -1*/ )
{
	//�߽���
	iEndRowIdx = (iEndRowIdx > ROW_NUM ? ROW_NUM : iEndRowIdx);
	iEndColIdx = (iEndColIdx > COLUMN_NUM ? COLUMN_NUM : iEndColIdx);

	for (int i = (iStartRowIdx == -1 ? 0 : iStartRowIdx); i < (iEndRowIdx == -1 ? ROW_NUM : iEndRowIdx); ++i)
	{
		for (int j = (iStartColIdx == -1 ? 0 : iStartColIdx); j < (iEndColIdx == -1 ? COLUMN_NUM : iEndColIdx); ++j)
		{
			bool bState = m_mapGameObj[m_iSceneIndex]->GetBrickState(i, j);
			if (m_arrBrickState[i][j] != bState)
			{
				UpdateBrick(i, j, false, bState);
			}
		}
	}
}


//��������Brick
void CGameScene::ResetBricks()
{
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			UpdateBrick(i, j, false, false);
		}
	}
}


//��ť��Ӧ
void CGameScene::OnButtonEvent(Ref* pSender, Widget::TouchEventType enType, int iBtnIndex)
{
	//�����ͣ������Ӧ��ť�¼�
	if (m_bPauseFlag)
	{
		return;
	}

	Button* pButton = (Button*)pSender;
	Vec2 oPos = Vec2::ZERO;

	switch (enType)
	{
	case Widget::TouchEventType::BEGAN:
		{
			//log("-----------------\nORIGIN  iBtnIndex=%d", iBtnIndex);
			oPos = pButton->getTouchBeganPosition();
			if (!AdjustClickIndex(oPos, iBtnIndex))
			{
				return;
			}

			//�����һ�εİ�ť��¼��Ч���Ҵ�ʱ���µİ�ť����һ�εĲ���ͬ�����ͷ���һ�εİ�ť
			if (m_nRecordBtnIdx < BTN_INVALID && iBtnIndex != m_nRecordBtnIdx)
			{
				//Release
				OnButtonReleased(m_nRecordBtnIdx);
			}
			m_nRecordBtnIdx = iBtnIndex;


			//log("BEGAN  iBtnIndex=%d", iBtnIndex);
			OnButtonPressed(iBtnIndex);
		}
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
	case Widget::TouchEventType::CANCELED:
		{
			oPos = pButton->getTouchEndPosition();
			if (!AdjustClickIndex(oPos, iBtnIndex))
			{
				return;
			}

			//�����һ�εİ�ť��¼��Ч���Ҵ�ʱ�ͷŵİ�ť����һ�εĲ���ͬ�����ͷ���һ�εİ�ť
			if (m_nRecordBtnIdx != BTN_INVALID && iBtnIndex != m_nRecordBtnIdx)
			{
				//Release
				OnButtonReleased(m_nRecordBtnIdx);
			}

			//����
			m_nRecordBtnIdx = BTN_INVALID;

			//log("RELEASE  iBtnIndex=%d", iBtnIndex);
			OnButtonReleased(iBtnIndex);
		}
		break;
	}
}


bool CGameScene::AdjustClickIndex(Vec2 pos, int& nIndex)
{
	//ֻ�������
	if (nIndex >= BTN_DIRMAX)
	{
		return true;
	}

	if (m_pLandNode->isVisible())
	{
		Vec2 dis = pos - m_oControllerLandCenterPos;
		float fFactor = dis.x / dis.y;
		if (fFactor >= 1 || fFactor <= -1)
		{
			nIndex = dis.x > 1e-6 ? BTN_UP : BTN_DOWN;
			return true;
		}

		if (fFactor < 1 && fFactor >= -1)
		{
			nIndex = dis.y > 1e-6 ? BTN_LEFT : BTN_RIGHT;
			return true;
		}
	}
	else
	{
		Vec2 dis = pos - m_oControllerCenterPos;
		float fFactor = dis.y / dis.x;
		if (fFactor >= 1 || fFactor <= -1)
		{
			nIndex = dis.y > 1e-6 ? BTN_UP : BTN_DOWN;
			return true;
		}

		if (fFactor < 1 && fFactor >= -1)
		{
			nIndex = dis.x > 1e-6 ? BTN_RIGHT : BTN_LEFT;
			return true;
		}
	}

	nIndex = -1;
	return false;
}


//��ť����
void CGameScene::OnButtonPressed(int iBtnIndex)
{
	if (m_iSceneIndex <= SCENE_CHOOSEGAME)
	{
		//��ť��Ч
		PLAY_EFFECT(EFFECT_CHANGE2);
	}

	switch (iBtnIndex)
	{
	case BTN_DOWN:
		m_mapGameObj[m_iSceneIndex]->OnDownBtnPressed();
		break;

	case BTN_LEFT:
		m_mapGameObj[m_iSceneIndex]->OnLeftBtnPressed();
		break;

	case BTN_RIGHT:
		m_mapGameObj[m_iSceneIndex]->OnRightBtnPressed();
		break;

	case BTN_UP:
		m_mapGameObj[m_iSceneIndex]->OnUpBtnPressed();
		break;

	case BTN_FIRE:
		m_mapGameObj[m_iSceneIndex]->OnFireBtnPressed();
		break;
	}
}


//��ť�ͷ�
void CGameScene::OnButtonReleased(int iBtnIndex)
{
	switch (iBtnIndex)
	{
	case BTN_DOWN:
		m_mapGameObj[m_iSceneIndex]->OnDownBtnReleased();
		break;

	case BTN_LEFT:
		m_mapGameObj[m_iSceneIndex]->OnLeftBtnReleased();
		break;

	case BTN_RIGHT:
		m_mapGameObj[m_iSceneIndex]->OnRightBtnReleased();
		break;

	case BTN_UP:
		m_mapGameObj[m_iSceneIndex]->OnUpBtnReleased();
		break;

	case BTN_FIRE:
		m_mapGameObj[m_iSceneIndex]->OnFireBtnReleased();
		break;
	}
}


//��ť���� iBtnIndex ��ӦBTN_INDEX����
void CGameScene::OnButtonClick(Ref* pSender, int iBtnIndex)
{
	double lfCurTime = GetMillSecond();

	switch (iBtnIndex)
	{
		case BTN_START:
		{
			//play effect
			PLAY_EFFECT(EFFECT_CHANGE2);

			if (m_iSceneIndex <= SCENE_CHOOSEGAME)
			{
				m_mapGameObj[m_iSceneIndex]->OnStart();
			}
			else
			{
				m_bPauseFlag = !m_bPauseFlag;
				m_pPauseSpr->setVisible(m_bPauseFlag);
				m_pPauseSprLand->setVisible(m_bPauseFlag);
				ChangePlayState(!m_bPauseFlag);

				//�����ͣ����ֹͣ����
				if (m_bPauseFlag)
				{
					this->unscheduleUpdate();
				}
				else
				{
					this->scheduleUpdate();
				}
			}
		}
		break;

		case BTN_SOUND:
		{
			bool bState = !GET_BOOLVALUE("SOUND", true);
			SET_BOOLVALUE("SOUND", bState);
			
			//������������
			m_pSetupLayer->UpdateSingleMenuAndLabel(MENU_SOUND);

			//����������ť״̬
			bool bPortVisible = GET_BOOLVALUE("PORTRAIT", true);
			if (bPortVisible)
			{
				int nIndex = m_pSoundBtn->getSelectedIndex();
				m_pSoundBtnLand->setSelectedIndex(nIndex);
			}
			else
			{
				int nIndex = m_pSoundBtnLand->getSelectedIndex();
				m_pSoundBtn->setSelectedIndex(nIndex);
			}

			if (bState)
			{
				PLAY_EFFECT(EFFECT_SOUNDON);
				if (m_iSceneIndex <= SCENE_CHOOSEGAME)
				{
					PLAY_BGMUSIC(BGM_START, true);
				}
			}
			else
			{
				//PLAY_EFFECT(EFFECT_SOUNDOFF);
				PAUSE_BGMUSIC();
			}
		}
		break;

		case BTN_RESET:
		{
			PLAY_EFFECT(EFFECT_CHANGE2);

			//�����ͣ�ˣ���ָ�����
			if (m_bPauseFlag)
			{
				m_bPauseFlag = false;
				m_pPauseSpr->setVisible(false);
				this->scheduleUpdate();
			}

			if (m_iSceneIndex > SCENE_CHOOSEGAME)
			{
				if (m_iSceneIndex == SCENE_TETRIS || m_iSceneIndex == SCENE_TETRIS2)
				{
					//��������
					m_mapGameObj[m_iSceneIndex]->SaveGameData();
				}

				RunScene(SCENE_GAMEOVER);
			}
		}
		break;
		case BTN_GIVESCORE:
		{
			PLAY_EFFECT(EFFECT_CHANGE2);

			//���غ���������
			m_pLandNode->setVisible(false);
			m_pPortNode->setVisible(false);
			//��ʾ���ý���
			m_pSetupLayer->setVisible(true);

			//��¼����״̬
			m_bOldSoundState = GET_BOOLVALUE("SOUND", true);

			//��ͣ
			this->unscheduleUpdate();
		}
		break;
	}
}


void CGameScene::ChangePlayState(bool bPlay)
{
	m_pStartBtn->setSelectedIndex(bPlay ? 1 : 0);
	m_pStartBtnLand->setSelectedIndex(bPlay ? 1 : 0);
}


Sprite* CGameScene::GetBrickSprite(int nRowIdx, int nColIdx, bool bSmallFlag, bool bLandFlag)
{
	if ((bSmallFlag && (nRowIdx >= 4 || nRowIdx < 0 || nColIdx >= 4 || nColIdx < 0))
		|| (!bSmallFlag && (nRowIdx >= ROW_NUM || nRowIdx < 0 || nColIdx >= COLUMN_NUM || nColIdx < 0)))
	{
		return nullptr;
	}

	if (!bLandFlag)
	{
		if (bSmallFlag)
		{
			return m_pArrSmallBrick[nRowIdx][nColIdx];
		}
		else
		{
			return m_pArrBrick[nRowIdx][nColIdx];
		}
	}
	else
	{
		if (bSmallFlag)
		{
			return m_pArrSmallBrickLand[nRowIdx][nColIdx];
		}
		else
		{
			return m_pArrBrickLand[nRowIdx][nColIdx];
		}
	}
}


void CGameScene::ShowTips(int nTipType)
{
	//�����ͬ����ʾ
	if (m_nTipType == nTipType)
	{
		return;
	}

	m_nTipType = nTipType;
	int nStrID = STRNAME_MAX;
	switch (m_nTipType)
	{
	case TIPS_EXIT:
	{
		nStrID = STRNAME_QUIT;
	}
	break;

	case TIPS_SAVEOPEN:
	{
		nStrID = STRNAME_RECOVERON;
	}
	break;

	case TIPS_SAVECLOSE:
	{
		nStrID = STRNAME_RECOVEROFF;
	}
	break;
	case TIPS_SAVEOK:
	{
		nStrID = STRNAME_SAVEOK;
	}
	break;
	default:
		return;
		break;
	}

	int nLangID = GET_INTVALUE("LANGUAGE", LANG_CH);
	string strName = CGeneralManager::getInstance()->GetStringByID(nLangID, nStrID);
	if (m_pTipsLabel == nullptr)
	{
		m_pTipsLabel = Label::createWithSystemFont(strName, FONT_NAME, 36);
		m_pTipsLabel->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
		m_pTipsLabel->setRotation(90);
		this->addChild(m_pTipsLabel, 999);
	}
	else
	{
		m_pTipsLabel->setString(strName);
	}

	//������ɫ
	bool bNightMode = GET_BOOLVALUE("NIGHTMODE", false);
	m_pTipsLabel->setColor(bNightMode ? Color3B::WHITE : Color3B::BLACK);

	//������
	bool bPortraitFlag = GET_BOOLVALUE("PORTRAIT", true);
	float fRotation = bPortraitFlag ? 0 : 90;
	m_pTipsLabel->setRotation(fRotation);

	//��ֹͣ���ж���
	m_pTipsLabel->stopAllActions();
	//m_pTipSpr->setVisible(true);
	m_pTipsLabel->runAction(
		Sequence::create(FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), CallFunc::create(CC_CALLBACK_0(CGameScene::ClearTipsRecord, this)), nullptr)
		);
}


void CGameScene::ChangeColorMode()
{
	bool bNightMode = GET_BOOLVALUE("NIGHTMODE", false);
	bNightMode = !bNightMode;
	SET_BOOLVALUE("NIGHTMODE", bNightMode);

	//����
	m_pBgLayer->setVisible(!bNightMode);

	//���з������
	for (int nRowIdx = 0; nRowIdx < ROW_NUM; ++nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
		{
			UpdateBrick(nRowIdx, nColIdx, false, m_arrBrickState[nRowIdx][nColIdx]);
		}
	}


	Vector<Node*> vecNode = m_pLandNode->getChildren();
	for (int nIdx = 0; nIdx < vecNode.size(); ++nIdx)
	{
		Node* pNode = vecNode.at(nIdx);
		Sprite* pSprite = dynamic_cast<Sprite *>(pNode);
		if (pSprite != nullptr && pSprite->getTag() < 0)
		{
			ChangeSprite(pSprite, bNightMode);
			continue;
		}

		//�˵�
		Menu* pMenu = dynamic_cast<Menu *>(pNode);
		if (pMenu != nullptr)
		{
			Vector<Node*> vecMenu = pMenu->getChildren();
			for (int i = 0; i < vecMenu.size(); ++i)
			{
				MenuItemSprite* pMenuItemSpr = dynamic_cast<MenuItemSprite*>(vecMenu.at(i));
				if (pMenuItemSpr != nullptr)
				{
					ChangeMenuItemSprite(pMenuItemSpr, bNightMode);
				}

				MenuItemToggle* pMenuItemToggle = dynamic_cast<MenuItemToggle*>(vecMenu.at(i));
				if (pMenuItemToggle != nullptr)
				{
					ChangeMenuItemToggle(pMenuItemToggle, bNightMode);
				}
			}
		}

		//��ť
		Button* pButton = dynamic_cast<Button*>(pNode);
		if (pButton != nullptr)
		{
			ChangeButton(pButton, bNightMode);
		}
	}

	vecNode.clear();
	vecNode = m_pPortNode->getChildren();
	for (int nIdx = 0; nIdx < vecNode.size(); ++nIdx)
	{
		Node* pNode = vecNode.at(nIdx);
		Sprite* pSprite = dynamic_cast<Sprite *>(pNode);
		if (pSprite != nullptr && pSprite->getTag() < 0)
		{
			ChangeSprite(pSprite, bNightMode);
			continue;
		}

		//�˵�
		Menu* pMenu = dynamic_cast<Menu *>(pNode);
		if (pMenu != nullptr)
		{
			Vector<Node*> vecMenu = pMenu->getChildren();
			for (int i = 0; i < vecMenu.size(); ++i)
			{
				MenuItemSprite* pMenuItemSpr = dynamic_cast<MenuItemSprite*>(vecMenu.at(i));
				if (pMenuItemSpr != nullptr)
				{
					ChangeMenuItemSprite(pMenuItemSpr, bNightMode);
				}

				MenuItemToggle* pMenuItemToggle = dynamic_cast<MenuItemToggle*>(vecMenu.at(i));
				if (pMenuItemToggle != nullptr)
				{
					ChangeMenuItemToggle(pMenuItemToggle, bNightMode);
				}
			}
		}

		//��ť
		Button* pButton = dynamic_cast<Button*>(pNode);
		if (pButton != nullptr)
		{
			ChangeButton(pButton, bNightMode);
		}
	}
}


void CGameScene::SaveTetrisRecord()
{
	if (m_iSceneIndex != SCENE_TETRIS && m_iSceneIndex != SCENE_TETRIS2)
	{
		return;
	}

	//����
	m_mapGameObj[m_iSceneIndex]->SaveGameData();

	//��ʾ
	ShowTips(CGameScene::TIPS_SAVEOK);
}


void CGameScene::GiveRate()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8 
	GLView::sharedOpenGLView()->OnGiveScore();
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo minfo;
	bool bFuncExistFlag = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "OnGiveScore", "()V");
	if (bFuncExistFlag)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}


void CGameScene::ShowMyApps()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8 
	GLView::sharedOpenGLView()->OnShowMyApps();
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo minfo;
	bool bFuncExistFlag = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "OnShowMyApps", "()V");
	if (bFuncExistFlag)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}


bool CGameScene::CheckSetupLayerVisible()
{
	return m_pSetupLayer->isVisible();
}


void CGameScene::QuitSetupLayer()
{
	m_pSetupLayer->setVisible(false);

	bool bPortVisible = GET_BOOLVALUE("PORTRAIT", true);
	m_pPortNode->setVisible(bPortVisible);
	m_pLandNode->setVisible(!bPortVisible);

	//������ť״̬����
	bool bSoundState = GET_BOOLVALUE("SOUND", true);
	int nIndex = m_pSoundBtn->getSelectedIndex();
	if (m_bOldSoundState != bSoundState)
	{
		nIndex = ((nIndex == 1) ? 0 : 1);
		m_pSoundBtn->setSelectedIndex(nIndex);
		m_pSoundBtnLand->setSelectedIndex(nIndex);
	}

	//�ָ�
	this->scheduleUpdate();
}


//��ʾ�³���
void CGameScene::RunScene(int iSceneIndex)
{
	//log("Old Scene: %d   Current Scene: %d", m_iSceneIndex, iSceneIndex);
	m_iSceneIndex = iSceneIndex;
	m_mapGameObj[m_iSceneIndex]->Init();

	//Change the play button state
	ChangePlayState(m_iSceneIndex > SCENE_CHOOSEGAME);
}


//���·�����ʾ
void CGameScene::UpdateScore(int iScore, bool bPlayEffect)
{
	if (bPlayEffect)
	{
		PLAY_EFFECT(EFFECT_ADD);
	}

	//log("Current Score: %d", iScore);

	char arrNum[7] = {'\0'};
	sprintf(arrNum, "%06d", iScore);

	char szSprName[20] = {'\0'};
	for (int i = 0; i < 6; ++i)
	{
		sprintf(szSprName, "%c.png", arrNum[i]);
		string strName = GetSpriteNameByMode(szSprName);
		m_pArrScore[i]->setSpriteFrame(strName);
		m_pArrScoreLand[i]->setSpriteFrame(strName);
	}

	UpdateHighScore(m_iSceneIndex - 2, iScore);
}


//������߷���ʾ
void CGameScene::UpdateHighScore(int iGameIdx, int iHighScore)
{
	if (iGameIdx < 0)
	{
		return;
	}

	int iRecordHighScore = CGeneralManager::getInstance()->GetHighScore(iGameIdx);
	if (iRecordHighScore > iHighScore)
	{
		iHighScore = iRecordHighScore;
	}
	else if (iRecordHighScore < iHighScore)
	{
		CGeneralManager::getInstance()->SetHighScore(iGameIdx, iHighScore);
	}
	
	char arrNum[7] = { '\0' };
	sprintf(arrNum, "%06d", iHighScore);
	char szName[20] = {'\0'};
	for (int i = 0; i < 6; ++i)
	{
		sprintf(szName, "%c.png", arrNum[i]);
		string strName = GetSpriteNameByMode(szName);
		m_pArrHighScore[i]->setSpriteFrame(strName);
		m_pArrHighScoreLand[i]->setSpriteFrame(strName);
	}
}


//���µȼ���ʾ
void CGameScene::UpdateLevel(int iLevel)
{
	//log("Current Level: %d", iLevel);
	
	//��ȡ����λ��
	Size brickSize = GetBrickSize(true);
	Size numSize = GetNumSize();
	float fCenterPosX = (m_visibleSize.width - COLUMN_NUM * brickSize.width) * 0.5f + COLUMN_NUM * brickSize.width;
	float fCenterPosY = (m_visibleSize.height - brickSize.width * COLUMN_NUM) * 0.5f * 0.5f - numSize.width * 2.2f;
	if (iLevel == 10)
	{
		string strName = GetSpriteNameByMode("1.png");
		m_pArrLevel[0]->setSpriteFrame(strName);
		m_pArrLevel[0]->setPositionX(fCenterPosX - numSize.width * 0.5f);
		m_pArrLevel[1]->setPositionX(fCenterPosX + numSize.width * 0.5f);
		m_pArrLevel[1]->setVisible(true);

		m_pArrLevelLand[0]->setSpriteFrame(strName);
		m_pArrLevelLand[0]->setPositionY(fCenterPosY + numSize.width * 0.5f);
		m_pArrLevelLand[1]->setPositionY(fCenterPosY - numSize.width * 0.5f);
		m_pArrLevelLand[1]->setVisible(true);
	}
	else
	{
		if (m_pArrLevel[1]->isVisible())
		{
			m_pArrLevel[1]->setVisible(false);
			m_pArrLevel[0]->setPositionX(fCenterPosX);

			m_pArrLevelLand[1]->setVisible(false);
			m_pArrLevelLand[0]->setPositionY(fCenterPosY);
		}
		
		char szName[20] = { '\0' };
		sprintf(szName, "%d.png", iLevel);
		string strName = GetSpriteNameByMode(szName);
		m_pArrLevel[0]->setSpriteFrame(strName);
		m_pArrLevelLand[0]->setSpriteFrame(strName);
	}
}


//�����ٶ���ʾ
void CGameScene::UpdateSpeed(int iSpeed)
{
	//log("Current Speed: %d", iSpeed);
	
	//��ȡ����λ��
	Size brickSize = GetBrickSize(true);
	Size numSize = GetNumSize();
	float fCenterPosX = (m_visibleSize.width - COLUMN_NUM * brickSize.width) * 0.5f + COLUMN_NUM * brickSize.width;
	float fCenterPosY = (m_visibleSize.height - brickSize.width * COLUMN_NUM) * 0.5f * 0.5f + numSize.width * 2.2f;
	if (iSpeed == 10)
	{
		string strName = GetSpriteNameByMode("1.png");
		m_pArrSpeed[0]->setSpriteFrame(strName);
		m_pArrSpeed[0]->setPositionX(fCenterPosX - numSize.width * 0.5f);
		m_pArrSpeed[1]->setPositionX(fCenterPosX + numSize.width * 0.5f);
		m_pArrSpeed[1]->setVisible(true);

		m_pArrSpeedLand[0]->setSpriteFrame(strName);
		m_pArrSpeedLand[0]->setPositionY(fCenterPosY + numSize.width * 0.5f);
		m_pArrSpeedLand[1]->setPositionY(fCenterPosY - numSize.width * 0.5f);
		m_pArrSpeedLand[1]->setVisible(true);
	}
	else
	{
		if (m_pArrSpeed[1]->isVisible())
		{
			m_pArrSpeed[1]->setVisible(false);
			m_pArrSpeed[0]->setPositionX(fCenterPosX);

			m_pArrSpeedLand[1]->setVisible(false);
			m_pArrSpeedLand[0]->setPositionY(fCenterPosY);
		}

		char szName[20] = {'\0'};
		sprintf(szName, "%d.png", iSpeed);
		string strName = GetSpriteNameByMode(szName);
		m_pArrSpeed[0]->setSpriteFrame(strName);
		m_pArrSpeedLand[0]->setSpriteFrame(strName);
	}
}


//����С��������
void CGameScene::UpdateSmallBricks()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			bool bState = m_mapGameObj[m_iSceneIndex]->GetSmallBrickState(i, j);
			UpdateBrick(i, j, true, bState);
		}
	}
}


//��������СBrick
void CGameScene::ResetSmallBricks()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			UpdateBrick(i, j, true, false);
		}
	}
}


void CGameScene::ChangeSprite(Sprite* pSprite, bool bNightMode)
{
	string strName = pSprite->getSpriteFrameName();
	int nIndex = strName.find(bNightMode ? ".png" : "_night");
	if (nIndex != string::npos)
	{
		string strNew = strName.substr(0, nIndex) + (bNightMode ? "_night.png" : ".png");
		int nTag = pSprite->getTag();
		pSprite->setSpriteFrame(strNew);
	}
}


void CGameScene::ChangeMenuItemSprite(MenuItemSprite* pMenuItemSpr, bool bNightMode)
{
	Sprite* pSprite = dynamic_cast<Sprite*>(pMenuItemSpr->getNormalImage());
	if (pSprite != nullptr)
	{
		ChangeSprite(pSprite, bNightMode);
	}

	pSprite = dynamic_cast<Sprite*>(pMenuItemSpr->getSelectedImage());
	if (pSprite != nullptr)
	{
		ChangeSprite(pSprite, bNightMode);
	}

	pSprite = dynamic_cast<Sprite*>(pMenuItemSpr->getDisabledImage());
	if (pSprite != nullptr)
	{
		ChangeSprite(pSprite, bNightMode);
	}
}


void CGameScene::ChangeMenuItemToggle(MenuItemToggle* pMenuItemToggle, bool bNightMode)
{
	Vector<MenuItem*> vecMenuItem = pMenuItemToggle->getSubItems();
	for (int i = 0; i < vecMenuItem.size(); ++i)
	{
		MenuItemSprite* pMenuItemSpr = dynamic_cast<MenuItemSprite*>(vecMenuItem.at(i));
		if (pMenuItemSpr != nullptr)
		{
			ChangeMenuItemSprite(pMenuItemSpr, bNightMode);
		}
	}
}


void CGameScene::ChangeButton(Button* pButton, bool bNightMode)
{
	string strName = pButton->getNormalName();
	int nIndex = strName.find(bNightMode ? ".png" : "_night");
	if (nIndex != string::npos)
	{
		string strNew = strName.substr(0, nIndex) + (bNightMode ? "_night.png" : ".png");
		//log("Normal  %s->%s", strName.c_str(), strNew.c_str());
		pButton->loadTextureNormal(strNew, TextureResType::PLIST);
	}

	strName = pButton->getClickedName();
	nIndex = strName.find(bNightMode ? ".png" : "_night");
	if (nIndex != string::npos)
	{
		string strNew = strName.substr(0, nIndex) + (bNightMode ? "_night.png" : ".png");
		//log("Clicked  %s->%s", strName.c_str(), strNew.c_str());
		pButton->loadTexturePressed(strNew, TextureResType::PLIST);
	}

	strName = pButton->getDisabledName();
	nIndex = strName.find(bNightMode ? ".png" : "_night");
	if (nIndex != string::npos)
	{
		string strNew = strName.substr(0, nIndex) + (bNightMode ? "_night.png" : ".png");
		//log("Disabled  %s->%s", strName.c_str(), strNew.c_str());
		pButton->loadTextureDisabled(strNew, TextureResType::PLIST);
	}
}


std::string CGameScene::GetSpriteNameByMode(const char* szName)
{
	string strTemp(szName);
	bool bNightMode = GET_BOOLVALUE("NIGHTMODE", false);
	if (bNightMode)
	{
		int nIndex = strTemp.find(".png");
		assert(nIndex != string::npos);

		strTemp = strTemp.substr(0, nIndex) + "_night.png";
	}

	return strTemp;
}


void CGameScene::ClearTipsRecord()
{
	m_nTipType = TIPS_INVALID;
}


void CGameScene::LaunchQuitRoutine()
{
	//�����ʾ�����ý��棬�򷵻�
	if (CheckSetupLayerVisible())
	{
		QuitSetupLayer();
		return;
	}

	double lfCurTime = GetMillSecond();
	if (lfCurTime - m_lfClickExitTime <= CLICK_INTERVAL)
	{
		if (m_iSceneIndex == SCENE_TETRIS || m_iSceneIndex == SCENE_TETRIS2)
		{
			//��������
			m_mapGameObj[m_iSceneIndex]->SaveGameData();
		}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
		Director::getInstance()->getOpenGLView()->QuitGame();
#else
		DIRECTOR_INSTANCE()->end();
#endif

		return;
	}

	m_lfClickExitTime = lfCurTime;

	//��ʾ�˳���ʾ
	ShowTips(TIPS_EXIT);
}

void CGameScene::InitBgLayer()
{
	m_pBgLayer = LayerColor::create(Color4B::WHITE);
	m_pBgLayer->setContentSize(m_visibleSize);
	this->addChild(m_pBgLayer);

	m_pBgLayer->setVisible(!GET_BOOLVALUE("NIGHTMODE", false));

	//��ʼ��SetupLayer
	m_pSetupLayer = CSetupLayer::create();
	m_pSetupLayer->setPosition(Vec2::ZERO);
	m_pSetupLayer->Init(this);
	this->addChild(m_pSetupLayer);
	m_pSetupLayer->setVisible(false);
}
