#include "GameScene.h"
#include "GameOver.h"
#include "DataManager.h"
#include "ChooseGame.h"

USING_NS_CC;

CGameScene::CGameScene() : m_iGameIndex(CHOOSE_GAME), m_fCurTime(0)
{
}


CGameScene::~CGameScene()
{
	for (int i = 0; i < m_mapGameObj.size(); ++i)
	{
		SAFE_DELETE(m_mapGameObj[i]);
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Brick.plist");

	CC_RETURN_FALSE_IF(!LayerColor::initWithColor(Color4B::WHITE));

	CDataManager::getInstance();
	
	//��ʼ����������ȡ���ݵ�
	InitData();

	//��ʼ������
	InitBrick();

	//��ʼ��������
	InitCotroller();

	//������Ϸ����
	CreateGameObj();

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
	float fCurY = m_visibleSize.height;
	for (int i = 0; i < ROW_NUM; ++i)
	{
		float fCurX = 0;
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrBrickState[i][j] = false;
			m_pBrick[i][j] = Sprite::create("empty.png");
			m_pBrick[i][j]->setPosition(fCurX + BRICK_WIDTH * 1.0f / 2, fCurY - BRICK_HEIGHT * 1.0f / 2);
			this->addChild(m_pBrick[i][j]);

			fCurX += BRICK_WIDTH;
		}

		fCurY -= BRICK_HEIGHT;
	}
}


void CGameScene::InitCotroller()
{
	//ʣ��߶ȣ����ڵ������ư�ťλ��
	float fHeight = m_visibleSize.height - BRICK_HEIGHT * ROW_NUM;

	auto upBtn = MenuItemSprite::create(
		Sprite::create("lineDark01.png"),
		Sprite::create("flatDark01.png"),
		NULL
		);
	Size upBtnSize = upBtn->getContentSize();

	auto rightBtn = MenuItemSprite::create(
		Sprite::create("lineDark02.png"),
		Sprite::create("flatDark02.png"),
		NULL
		);
	Size rightBtnSize = rightBtn->getContentSize();

	auto downBtn = MenuItemSprite::create(
		Sprite::create("lineDark03.png"),
		Sprite::create("flatDark03.png"),
		NULL
		);
	Size downBtnSize = downBtn->getContentSize();

	auto leftBtn = MenuItemSprite::create(
		Sprite::create("lineDark04.png"),
		Sprite::create("flatDark04.png"),
		NULL
		);
	Size leftBtnSize = leftBtn->getContentSize();

	auto fireBtn = MenuItemSprite::create(
		Sprite::create("lineDark05.png"),
		Sprite::create("flatDark05.png"),
		NULL
		);
	Size fireBtnSize = fireBtn->getContentSize();


	float fScale = 1.5f;
	auto startBtn = MenuItemSprite::create(
		Sprite::create("start_0.png"),
		Sprite::create("start_1.png"),
		NULL
		);
	startBtn->setScale(fScale);
	Size startBtnSize = startBtn->getContentSize() * fScale;

	auto soundBtn = MenuItemSprite::create(
		Sprite::create("sound_on_0.png"),
		Sprite::create("sound_on_1.png"),
		NULL
		);
	soundBtn->setScale(fScale);
	Size soundBtnSize = soundBtn->getContentSize() * fScale;

	auto resetBtn = MenuItemSprite::create(
		Sprite::create("reset_0.png"),
		Sprite::create("reset_1.png"),
		NULL
		);
	resetBtn->setScale(fScale);
	Size resetBtnSize = resetBtn->getContentSize() * fScale;

	leftBtn->setPosition(leftBtnSize.width, downBtnSize.height * 2.0f + 6);
	rightBtn->setPosition(leftBtnSize.width * 1.5f + rightBtnSize.width / 2 + 12, downBtnSize.height * 2.0f + 6);
	downBtn->setPosition(leftBtnSize.width * 1.5f + 6, downBtnSize.height * 1.5f);
	upBtn->setPosition(leftBtnSize.width * 1.5f + 6, downBtnSize.height * 2.0f + 12 + upBtnSize.height / 2);
	fireBtn->setPosition(m_visibleSize.width - (leftBtnSize.width * 1.5f + 6), downBtnSize.height * 2.0f + 6);

	soundBtn->setPosition(m_visibleSize.width / 2, soundBtnSize.height / 2);
	startBtn->setPosition(m_visibleSize.width / 2 - 20 - soundBtnSize.width / 2 - startBtnSize.width / 2, soundBtnSize.height / 2);
	resetBtn->setPosition(m_visibleSize.width / 2 + 20 + soundBtnSize.width / 2 + resetBtnSize.width / 2, soundBtnSize.height / 2);

	auto menu = Menu::create(leftBtn, upBtn, rightBtn, downBtn, fireBtn, soundBtn, startBtn, resetBtn, NULL);
	float fCurHeight = downBtnSize.height * 2.0f + 12 + upBtnSize.height;
	menu->setPosition(Vec2(0, (fHeight - fCurHeight) / 3));
	this->addChild(menu);
}


void CGameScene::update(float dt)
{
	m_fCurTime += dt * 1000;
	float fWaitTime = m_mapGameObj[m_iGameIndex]->GetRefreshTime();
	if (m_fCurTime < fWaitTime)
	{
		return;
	}

	//����ʱ��
	m_fCurTime = 0;

	SCENE_INDEX enGameIdx = m_mapGameObj[m_iGameIndex]->GetSceneType();
	bool bRet = m_mapGameObj[m_iGameIndex]->Play();
	if (bRet)
	{
		//��Ϸ�������棬ÿ�ν�����һ��Brick
		if (enGameIdx == GAME_OVER)
		{
			int iRowIndex = 0;
			int iColIndex = 0;
			m_mapGameObj[m_iGameIndex]->GetCurPos(iRowIndex, iColIndex);
			UpdateBrick(iRowIndex, iColIndex, true);
		}
		else
		{
			//��������Brick
			UpdateBricks();
		}
	}
	else
	{
		//���
		ResetAllBricks();

		//��һ����Ϸ
		//++m_iGameIndex;

		//��ʼ��
		m_mapGameObj[m_iGameIndex]->Init();
	}
}


//����������Ϸ����
void CGameScene::CreateGameObj()
{
	//��Ϸ����
	CGameOver* pGameOver = new CGameOver();
	pGameOver->Init();
	m_mapGameObj[0] = pGameOver;

	//ѡ����Ϸ
	CChooseGame* pChooseGame = new CChooseGame();
	pChooseGame->Init();
	m_mapGameObj[1] = pChooseGame;
}


//���µ���Brick״̬
void CGameScene::UpdateBrick(int iRowIndex, int iColIndex, bool bShowFlag)
{
	//����״̬��¼
	m_arrBrickState[iRowIndex][iColIndex] = bShowFlag;

	if (bShowFlag)
	{
		m_pBrick[iRowIndex][iColIndex]->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("black.png"));
	}
	else
	{
		m_pBrick[iRowIndex][iColIndex]->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("empty.png"));
	}
}


//��������Brick״̬
void CGameScene::UpdateBricks()
{
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			bool bState = m_mapGameObj[m_iGameIndex]->GetBrickState(i, j);
			if (m_arrBrickState[i][j] != bState)
			{
				UpdateBrick(i, j, bState);
			}
		}
	}
}


//��������Brick
void CGameScene::ResetAllBricks()
{
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			UpdateBrick(i, j, false);
		}
	}
}
