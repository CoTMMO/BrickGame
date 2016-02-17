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

CGameScene::CGameScene() : m_iSceneIndex(SCENE_GAMEOVER)
{
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
	CC_RETURN_FALSE_IF(!LayerColor::initWithColor(Color4B::WHITE));

	//��ʼ����������ȡ���ݵ�
	InitData();

	//UI��ʼ��
	InitUI();

	//��ʼ������
	InitBrick();

	//��ʼ��������
	InitCotroller();

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

	//��ʼ����ͣ���
	m_bGamePause = false;
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
		false, false, false, false, false, true, true, true, true, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, true, false, false, false, false,
		false, false, false, false, false, false, false, false, true, false, false, false, false, false,
		false, false, false, false, false, false, false, true, false, false, false, false, false,
		false, false, false, false, false, false, false, true, false, false, false, false, false, false,
		false, false, false, false, false, false, false, true, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, true, true, true, true, false, false, false,
		false, false, false, false, false, false, true, false, false, false, false, false, false, false,
		false, false, false, false, false, false, true, false, false, false, true, true, false, false,
		false, false, false, false, false, false, true, false, false, false, false, true, false, false,
		false, false, false, false, false, false, false, true, true, true, true, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, 
	};

	float fCurY = m_visibleSize.height;
	for (int i = 0; i < ROW_NUM; ++i)
	{
		float fCurX = 0;
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrBrickState[i][j] = arrBrick[i][j];
			m_pArrBrick[i][j] = Sprite::createWithSpriteFrameName(arrBrick[i][j] ? "black.png" : "empty.png");
			m_pArrBrick[i][j]->setPosition(fCurX + BRICK_WIDTH * 1.0f / 2, fCurY - BRICK_HEIGHT * 1.0f / 2);
			this->addChild(m_pArrBrick[i][j]);

			fCurX += BRICK_WIDTH;
		}

		fCurY -= BRICK_HEIGHT;
	}
}


//��ʼ��UI:�������ȼ���
void CGameScene::InitUI()
{
	//TTFConfig ttfConfig("Fonts/DSDigital.ttf", 46.0f);
	Size visibleSize = GET_VISIBLESIZE();

	//ͼƬ����
	float fSpriteScale = 0.38f;

	//����
	m_pBgSpr = Sprite::create("bg.png");
	m_pBgSpr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_pBgSpr->setScale(GET_CONTENTSIZE(m_pBgSpr).width / visibleSize.width);
	this->addChild(m_pBgSpr);

	//����
	auto pScore = Sprite::create("score.png");
	pScore->setScale(fSpriteScale);
	Size scoreSize = GET_CONTENTSIZE(pScore) * fSpriteScale;
	float fCurX = (visibleSize.width - COLUMN_NUM * BRICK_WIDTH) / 2 + COLUMN_NUM * BRICK_WIDTH;
	float fCurY = visibleSize.height - scoreSize.height * 3 / 2;
	pScore->setPosition(fCurX, fCurY + scoreSize.height / 2);
	this->addChild(pScore);

	//����Label
	/*m_pScoreLabel = Label::createWithTTF(ttfConfig, "123456", TextHAlignment::CENTER);
	m_pScoreLabel = Label::createWithBMFont("Fonts/font.fnt", "123456", TextHAlignment::CENTER);
	Size scoreLabelSize = GET_CONTENTSIZE(m_pScoreLabel);
	fCurY -= scoreLabelSize.height * 2.5f / 2;
	m_pScoreLabel->setPosition(fCurX, fCurY + scoreLabelSize.height / 2);
	m_pScoreLabel->setTextColor(Color4B::BLACK);
	this->addChild(m_pScoreLabel);*/

	//����Sprite����
	float fTempX = fCurX - NUM_PADDING * 5 / 2 - NUM_WIDTH * 3;
	fCurY -= NUM_HEIGHT * 2.5f / 2;
	for (int i = 0; i < 6; ++i)
	{
		m_pArrScore[i] = CREATE_SPRITEWITHNAME("0.png");
		m_pArrScore[i]->setPosition(fTempX + NUM_WIDTH / 2, fCurY + NUM_HEIGHT / 2);
		this->addChild(m_pArrScore[i]);

		fTempX += NUM_WIDTH + NUM_PADDING;
	}

	//��߷�
	auto pHighScore = Sprite::create("hiscore.png");
	pHighScore->setScale(fSpriteScale);
	Size highScoreSize = GET_CONTENTSIZE(pHighScore) * fSpriteScale;
	fCurY -= highScoreSize.height * 3 / 2;
	pHighScore->setPosition(fCurX, fCurY + highScoreSize.height / 2);
	this->addChild(pHighScore);

	//��߷�Label
	/*m_pHighScoreLabel = Label::createWithBMFont("Fonts/font.fnt", "000000", TextHAlignment::CENTER);
	Size highScoreLabelSize = GET_CONTENTSIZE(m_pHighScoreLabel);
	fCurY -= highScoreLabelSize.height * 2.5f / 2;
	m_pHighScoreLabel->setPosition(fCurX, fCurY + highScoreLabelSize.height / 2);
	m_pHighScoreLabel->setTextColor(Color4B::BLACK);
	this->addChild(m_pHighScoreLabel);*/

	//��߷�Sprite����
	fCurY -= NUM_HEIGHT * 2.5f / 2;
	fTempX = fCurX - NUM_PADDING * 5 / 2 - NUM_WIDTH * 3;
	for (int i = 0; i < 6; ++i)
	{
		m_pArrHighScore[i] = CREATE_SPRITEWITHNAME("0.png");
		m_pArrHighScore[i]->setPosition(fTempX + NUM_WIDTH / 2, fCurY + NUM_HEIGHT / 2);
		this->addChild(m_pArrHighScore[i]);

		fTempX += NUM_WIDTH + NUM_PADDING;
	}

	//С��������
	float fBrickScale = 0.7f;
	float fPadding = 4;
	fCurY -= NUM_HEIGHT / 2;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float fX = fCurX + (BRICK_HEIGHT * fBrickScale + fPadding) * (j - 1.5f);
			m_pArrSmallBrick[i][j] = Sprite::createWithSpriteFrameName("empty.png");
			m_pArrSmallBrick[i][j]->setScale(fBrickScale);
			m_pArrSmallBrick[i][j]->setPosition(fX, fCurY - BRICK_HEIGHT * fBrickScale / 2);
			this->addChild(m_pArrSmallBrick[i][j]);
		}

		fCurY -= BRICK_HEIGHT * fBrickScale + fPadding;
	}

	//�ٶ�
	auto pSpeed = Sprite::create("speed.png");
	pSpeed->setScale(fSpriteScale);
	Size speedSize = GET_CONTENTSIZE(pSpeed);
	fCurY -= speedSize.height;
	pSpeed->setPosition(fCurX, fCurY + speedSize.height / 2);
	this->addChild(pSpeed);

	//�ٶ�Label
	/*m_pSpeedLabel = Label::createWithBMFont("Fonts/font.fnt", "0", TextHAlignment::CENTER);
	Size speedLabelSize = GET_CONTENTSIZE(m_pSpeedLabel);
	fCurY -= speedLabelSize.height;
	m_pSpeedLabel->setPosition(fCurX, fCurY + speedLabelSize.height / 2);
	m_pSpeedLabel->setTextColor(Color4B::BLACK);
	this->addChild(m_pSpeedLabel);*/
	fCurY -= NUM_HEIGHT;
	m_pArrSpeed[0] = CREATE_SPRITEWITHNAME("0.png");
	m_pArrSpeed[0]->setPosition(fCurX, fCurY + NUM_HEIGHT / 2);
	this->addChild(m_pArrSpeed[0]);

	m_pArrSpeed[1] = CREATE_SPRITEWITHNAME("0.png");
	m_pArrSpeed[1]->setPosition(fCurX, fCurY + NUM_HEIGHT / 2);
	this->addChild(m_pArrSpeed[1]);
	m_pArrSpeed[1]->setVisible(false);

	//�ȼ�Label
	/*m_pLevelLabel = Label::createWithBMFont("Fonts/font.fnt", "0", TextHAlignment::CENTER);
	Size levelLabelSize = GET_CONTENTSIZE(m_pLevelLabel);
	fCurY -= levelLabelSize.height;
	m_pLevelLabel->setPosition(fCurX, fCurY + levelLabelSize.height / 2);
	m_pLevelLabel->setTextColor(Color4B::BLACK);
	this->addChild(m_pLevelLabel);*/
	fCurY -= NUM_HEIGHT + NUM_PADDING * 10;
	m_pArrLevel[0] = CREATE_SPRITEWITHNAME("0.png");
	m_pArrLevel[0]->setPosition(fCurX, fCurY + NUM_HEIGHT / 2);
	this->addChild(m_pArrLevel[0]);

	m_pArrLevel[1] = CREATE_SPRITEWITHNAME("0.png");
	m_pArrLevel[1]->setPosition(fCurX, fCurY + NUM_HEIGHT / 2);
	this->addChild(m_pArrLevel[1]);
	m_pArrLevel[1]->setVisible(false);

	//�ȼ�
	auto pLevel = Sprite::create("level.png");
	pLevel->setScale(fSpriteScale);
	Size levelSize = GET_CONTENTSIZE(pLevel);
	fCurY -= levelSize.height;
	pLevel->setPosition(fCurX, fCurY + levelSize.height / 2);
	this->addChild(pLevel);

	//��ͣͼ��
	//float fPauseScale = fSpriteScale - 0.04f;
	m_pPauseSpr = Sprite::create("pause.png");
	m_pPauseSpr->setScale(fSpriteScale);
	Size pauseSize = GET_CONTENTSIZE(m_pPauseSpr) * fSpriteScale;
	fCurY -= pauseSize.height;
	m_pPauseSpr->setPosition(fCurX, fCurY + pauseSize.height / 2);
	this->addChild(m_pPauseSpr);

	//Ĭ�Ϸ���ͣ״̬
	m_pPauseSpr->setVisible(m_bGamePause);
}


void CGameScene::InitCotroller()
{
	//ʣ��߶ȣ����ڵ������ư�ťλ��
	float fHeight = m_visibleSize.height - BRICK_HEIGHT * ROW_NUM;

	float fBtnScale = 1.45f;
	//float fBtnPadding = 30 * fBtnScale;

	//��
	Button* pUpBtn = Button::create("btn_0.png", "btn_1.png");
	pUpBtn->setScale(fBtnScale);
	pUpBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_UP));
	Size upBtnSize = pUpBtn->getContentSize() * fBtnScale;

	//��
	Button* pRightBtn = Button::create("btn_0.png", "btn_1.png");
	pRightBtn->setScale(fBtnScale);
	pRightBtn->setRotation(90);
	pRightBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_RIGHT));
	Size rightBtnSize = pRightBtn->getContentSize() * fBtnScale;

	//��
	Button* pDownBtn = Button::create("btn_0.png", "btn_1.png");
	pDownBtn->setScale(fBtnScale);
	pDownBtn->setRotation(180);
	pDownBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_DOWN));
	Size downBtnSize = pDownBtn->getContentSize() * fBtnScale;

	//��
	Button* pLeftBtn = Button::create("btn_0.png", "btn_1.png");
	pLeftBtn->setScale(fBtnScale);
	pLeftBtn->setRotation(-90);
	pLeftBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_LEFT));
	Size leftBtnSize = pLeftBtn->getContentSize() * fBtnScale;

	//Fire
	float fFireScale = fBtnScale - 0.08f;
	Button* pFireBtn = Button::create("fire_0.png", "fire_1.png");
	pFireBtn->setScale(fFireScale);
	pFireBtn->addTouchEventListener(CC_CALLBACK_2(CGameScene::OnButtonEvent, this, BTN_FIRE));
	Size fireBtnSize = pFireBtn->getContentSize() * fFireScale;

	//����λ��
	float fTopPosY = fHeight - (fHeight - upBtnSize.height * 2) * 0.7f / 3;
	pLeftBtn->setPosition(Vec2(upBtnSize.height * 0.7f + 4.0f, fTopPosY - upBtnSize.height));
	pRightBtn->setPosition(Vec2(upBtnSize.height * 1.7f - 4.0f, fTopPosY - upBtnSize.height));
	pDownBtn->setPosition(Vec2(upBtnSize.height * 1.2f, fTopPosY - upBtnSize.height * 1.5f + 4.0f));
	pUpBtn->setPosition(Vec2(upBtnSize.height * 1.2f, fTopPosY - upBtnSize.height / 2 - 4.0f));
	pFireBtn->setPosition(Vec2(m_visibleSize.width - upBtnSize.height * 0.4f - fireBtnSize.width / 2, fTopPosY - upBtnSize.height));
	this->addChild(pLeftBtn);
	this->addChild(pRightBtn);
	this->addChild(pDownBtn);
	this->addChild(pUpBtn);
	this->addChild(pFireBtn);

	fTopPosY -= upBtnSize.height * 2;

	//��ʼ
	float fSpriteScale = 0.38f;
	auto startBtn = MenuItemSprite::create(
		Sprite::create("play.png"),
		Sprite::create("play.png"),
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_START)
		);
	startBtn->setScale(fSpriteScale);
	Size startBtnSize = startBtn->getContentSize() * fSpriteScale;

	//��ȡ����״̬
	bool bSoundState = GET_SOUNDSTATE();
	auto pSoundOnMenu = MenuItemSprite::create(
		Sprite::create("sound_on.png"),
		Sprite::create("sound_on.png"),
		nullptr
		);
	auto pSoundOffMenu = MenuItemSprite::create(
		Sprite::create("sound_off.png"),
		Sprite::create("sound_off.png"),
		nullptr
		);

	//��������
	auto soundBtn = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_SOUND),
		bSoundState ? pSoundOnMenu : pSoundOffMenu,
		bSoundState ? pSoundOffMenu : pSoundOnMenu,
		nullptr
		);
	soundBtn->setScale(fSpriteScale);
	Size soundBtnSize = soundBtn->getContentSize() * fSpriteScale;

	//����
	auto resetBtn = MenuItemSprite::create(
		Sprite::create("reset.png"),
		Sprite::create("reset.png"),
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_RESET)
		);
	resetBtn->setScale(fSpriteScale);
	Size resetBtnSize = resetBtn->getContentSize() * fSpriteScale;

	//�ײ���ť�߶�
	fHeight = (fTopPosY - soundBtnSize.height) / 2 + soundBtnSize.height / 2;
	//��ť���
	float fBtnPadding = soundBtnSize.width * 1.2f;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
	//���⹦��
	auto extremeBtn = MenuItemSprite::create(
		Sprite::create("star.png"),
		Sprite::create("star.png"),
		CC_CALLBACK_1(CGameScene::OnButtonClick, this, BTN_GIVESCORE)
		);
	extremeBtn->setScale(fSpriteScale);
	Size themeBtnSize = extremeBtn->getContentSize() * fSpriteScale;

	//λ��
	soundBtn->setPosition(m_visibleSize.width / 2 - fBtnPadding / 2 - soundBtnSize.width / 2, fHeight);
	startBtn->setPosition(m_visibleSize.width / 2 - fBtnPadding * 3 / 2 - soundBtnSize.width - startBtnSize.width / 2, fHeight);
	resetBtn->setPosition(m_visibleSize.width / 2 + fBtnPadding / 2 + resetBtnSize.width / 2, fHeight);
	extremeBtn->setPosition(m_visibleSize.width / 2 + fBtnPadding * 3 / 2 + resetBtnSize.width + themeBtnSize.width / 2, fHeight);

	auto menu = Menu::create(soundBtn, startBtn, resetBtn, extremeBtn, nullptr);
	float fCurHeight = 0;
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
#else
	soundBtn->setPosition(m_visibleSize.width / 2, fHeight);
	startBtn->setPosition(m_visibleSize.width / 2 - soundBtnSize.width / 2 - fBtnPadding - startBtnSize.width / 2, fHeight);
	resetBtn->setPosition(m_visibleSize.width / 2 + soundBtnSize.width / 2 + fBtnPadding + resetBtnSize.width / 2, fHeight);

	auto menu = Menu::create(soundBtn, startBtn, resetBtn, nullptr);
	float fCurHeight = 0;
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

#endif

}


//��������������
void CGameScene::CreateKeyListener()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (EventKeyboard::KeyCode::KEY_A == keyCode)
		{
			log("A Pressed");
			OnButtonPressed(BTN_LEFT);
		}
		else if (EventKeyboard::KeyCode::KEY_D == keyCode)
		{
			log("D Pressed");
			OnButtonPressed(BTN_RIGHT);
		}
		else if (EventKeyboard::KeyCode::KEY_S == keyCode)
		{
			log("S Pressed");
			OnButtonPressed(BTN_DOWN);
		}
		else if (EventKeyboard::KeyCode::KEY_W == keyCode)
		{
			log("W Pressed");
			OnButtonPressed(BTN_UP);
		}
		else if (EventKeyboard::KeyCode::KEY_K == keyCode)
		{
			log("K Pressed");
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
			log("A Released");
			OnButtonReleased(BTN_LEFT);
		}
		else if (EventKeyboard::KeyCode::KEY_D == keyCode)
		{
			log("D Released");
			OnButtonReleased(BTN_RIGHT);
		}
		else if (EventKeyboard::KeyCode::KEY_S == keyCode)
		{
			log("S Released");
			OnButtonReleased(BTN_DOWN);
		}
		else if (EventKeyboard::KeyCode::KEY_W == keyCode)
		{
			log("W Released");
			OnButtonReleased(BTN_UP);
		}
		else if (EventKeyboard::KeyCode::KEY_K == keyCode)
		{
			log("K Released");
			OnButtonReleased(BTN_FIRE);
		}
		else if (EventKeyboard::KeyCode::KEY_RETURN == keyCode ||
			EventKeyboard::KeyCode::KEY_ESCAPE == keyCode ||
			EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
		{
			DIRECTOR_INSTANCE()->end();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}


void CGameScene::update(float dt)
{
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
	CPinballGame* pPinballGame = new CPinballGame(this);
	m_mapGameObj[SCENE_PINBALL] = pPinballGame;

	//����˹����
	CTetrisGame* pTetrisGame = new CTetrisGame(this);
	m_mapGameObj[SCENE_TETRIS] = pTetrisGame;
}


//���µ���Brick״̬
void CGameScene::UpdateBrick(int iRowIndex, int iColIndex, bool bSmallBrickFlag, bool bShowFlag)
{
	Sprite* pBrick = nullptr;
	if (bSmallBrickFlag)
	{
		pBrick = m_pArrSmallBrick[iRowIndex][iColIndex];
	}
	else
	{
		//����״̬��¼
		m_arrBrickState[iRowIndex][iColIndex] = bShowFlag;

		pBrick = m_pArrBrick[iRowIndex][iColIndex];
	}

	//������ʾ������״̬
	if (bShowFlag)
	{
		pBrick->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("black.png"));
	}
	else
	{
		pBrick->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("empty.png"));
	}
}


//��������Brick״̬
void CGameScene::UpdateBricks( int iStartRowIdx, int iStartColIdx, int iEndRowIdx, int iEndColIdx )
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
	if (m_bGamePause)
	{
		return;
	}

	switch (enType)
	{
	case Widget::TouchEventType::BEGAN:
		OnButtonPressed(iBtnIndex);
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		OnButtonReleased(iBtnIndex);
		break;

	case Widget::TouchEventType::CANCELED:
		OnButtonReleased(iBtnIndex);
		break;
	}
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
		m_mapGameObj[m_iSceneIndex]->OnDownPressed();
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
		m_mapGameObj[m_iSceneIndex]->OnDownReleased();
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
	switch (iBtnIndex)
	{
		case BTN_START:
		{
			PLAY_EFFECT(EFFECT_CHANGE2);

			if (m_iSceneIndex <= SCENE_CHOOSEGAME)
			{
				m_mapGameObj[m_iSceneIndex]->OnStart();
			}
			else
			{
				m_bGamePause = !m_bGamePause;
				m_pPauseSpr->setVisible(m_bGamePause);
				//�����ͣ����ֹͣ����
				if (m_bGamePause)
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
			bool bState = !GET_SOUNDSTATE();
			SET_SOUNDSTATE(bState);

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
			if (m_bGamePause)
			{
				m_bGamePause = false;
				m_pPauseSpr->setVisible(false);
				this->scheduleUpdate();
			}

			if (m_iSceneIndex > SCENE_CHOOSEGAME)
			{
				RunScene(SCENE_GAMEOVER);
			}
		}
		break;
		case BTN_GIVESCORE:
		{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
			PLAY_EFFECT(EFFECT_CHANGE2);
			GLView::sharedOpenGLView()->OnGiveScore();
#endif
		}
		break;
	}
}

//��ʾ�³���
void CGameScene::RunScene(int iSceneIndex)
{
	log("Old Scene: %d   Current Scene: %d", m_iSceneIndex, iSceneIndex);
	m_iSceneIndex = iSceneIndex;
	m_mapGameObj[m_iSceneIndex]->Init();
}


//���·�����ʾ
void CGameScene::UpdateScore(int iScore, bool bPlayEffect)
{
	if (bPlayEffect)
	{
		PLAY_EFFECT(EFFECT_ADD);
	}

	log("Current Score: %d", iScore);

	char arrNum[7] = {'\0'};
	sprintf(arrNum, "%06d", iScore);
	for (int i = 0; i < 6; ++i)
	{
		m_pArrScore[i]->setSpriteFrame(StringUtils::format("%c.png", arrNum[i]));
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
	for (int i = 0; i < 6; ++i)
	{
		m_pArrHighScore[i]->setSpriteFrame(StringUtils::format("%c.png", arrNum[i]));
	}
}


//���µȼ���ʾ
void CGameScene::UpdateLevel(int iLevel)
{
	log("Current Level: %d", iLevel);
	
	float fCenterPosX = (GET_VISIBLESIZE().width - COLUMN_NUM * BRICK_WIDTH) / 2 + COLUMN_NUM * BRICK_WIDTH;
	if (iLevel == 10)
	{
		m_pArrLevel[0]->setSpriteFrame("1.png");
		m_pArrLevel[0]->setPositionX(fCenterPosX - NUM_WIDTH / 2);
		m_pArrLevel[1]->setPositionX(fCenterPosX + NUM_WIDTH / 2);
		m_pArrLevel[1]->setVisible(true);
	}
	else
	{
		if (m_pArrLevel[1]->isVisible())
		{
			m_pArrLevel[1]->setVisible(false);
			m_pArrLevel[0]->setPositionX(fCenterPosX);
		}
		m_pArrLevel[0]->setSpriteFrame(StringUtils::format("%d.png", iLevel));
	}
}


//�����ٶ���ʾ
void CGameScene::UpdateSpeed(int iSpeed)
{
	log("Current Speed: %d", iSpeed);
	
	float fCenterPosX = (GET_VISIBLESIZE().width - COLUMN_NUM * BRICK_WIDTH) / 2 + COLUMN_NUM * BRICK_WIDTH;
	if (iSpeed == 10)
	{
		m_pArrSpeed[0]->setSpriteFrame("1.png");
		m_pArrSpeed[0]->setPositionX(fCenterPosX - NUM_WIDTH / 2);
		m_pArrSpeed[1]->setPositionX(fCenterPosX + NUM_WIDTH / 2);
		m_pArrSpeed[1]->setVisible(true);
	}
	else
	{
		if (m_pArrSpeed[1]->isVisible())
		{
			m_pArrSpeed[1]->setVisible(false);
			m_pArrSpeed[0]->setPositionX(fCenterPosX);
		}
		m_pArrSpeed[0]->setSpriteFrame(StringUtils::format("%d.png", iSpeed));
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
