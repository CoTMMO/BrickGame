#include "SetupLayer.h"
#include "GeneralManager.h"
#include "GameScene.h"
#include "VolumeLayer.h"
#include "BarrierLayer.h"

USING_NS_CC;

//�˵�ѡ���Ӧ�ַ���ID
const string MENU_SPRITE_STRING[MENU_MAX][2] =
{
	{ "vibrate_off.png", "vibrate.png"  },		//MENU_VIBRATION
	{ "sound.png", "sound.png" },				//MENU_SOUND
	{ "sun.png", "moon.png" },					//MENU_NIGHTMODE
	{ "portrait.png", "landscape.png" },		//MENU_ORIENTATION
	{ "lefthand.png", "righthand.png" },		//MENU_RHMODE
	{ "autorecover.png", "autorecover.png" },	//MENU_AUTORECOVER
	{ "save.png", "save.png" },					//MENU_SAVENOW
	{ "rotate.png", "down.png" },				//MENU_UPBTN
	{ "lfeng.png", "lfeng.png" },				//MENU_AUTHOR
	{ "like.png", "like.png" },					//MENU_RATE
	{ "back.png", "back.png" },					//MENU_BACK
};

//���˵����Ӳ˵���ϵ
const int MENU_RELATION[MAINMENU_MAX][5] = 
{
	{ MENU_VIBRATION, MENU_SOUND, MENU_NIGHTMODE, MENU_ORIENTATION, MENU_RHMODE },
	{ MENU_AUTORECOVER, MENU_SAVENOW, MENU_UPBTN, -1, -1 },
	{ MENU_AUTHOR, MENU_RATE, MENU_BACK, -1, -1 },
};


const float LANDSCAPE_MENU_SCALE = 1.03f;
const float PORTRAIT_MENU_SCALE = 1.6f;



CSetupLayer::CSetupLayer() : m_pGameScene(nullptr)
{
}


CSetupLayer::~CSetupLayer()
{
}


bool CSetupLayer::Init(CGameScene* pGameScene)
{
	if (pGameScene == nullptr)
	{
		return false;
	}
	m_pGameScene = pGameScene;

	//�������в˵�
	initAllMenu();

	//����λ��
	adjustMenuPos();

	return true;
}


void CSetupLayer::UpdateSingleMenu(int nMenuIdx)
{
	MenuItem* pMenuItem = m_vecMenuItem.at(nMenuIdx);
	if (pMenuItem == nullptr)
	{
		return;
	}
	
	updateSingleMenu(pMenuItem, nMenuIdx);
}


void CSetupLayer::updateAllMenu()
{
	for (int nIndex = 0; nIndex < m_vecMenuItem.size(); ++nIndex)
	{
		UpdateSingleMenu(nIndex);
	}

	//����Label
	bool bNightMode = getValueByMenuIdx(MENU_NIGHTMODE);
	for (int nIndex = 0; nIndex < m_vecLabel.size(); ++nIndex)
	{
		Label* pLabel = m_vecLabel.at(nIndex);
		if (pLabel == nullptr)
		{
			continue;
		}

		pLabel->setColor(bNightMode ? Color3B::WHITE : Color3B::BLACK);
	}
}


int CSetupLayer::getValueByMenuIdx(int nMenuIdx)
{
	switch (nMenuIdx)
	{
	case MENU_VIBRATION:
		return GET_INTVALUE("VIBRATION", 0);		//0�ر� 1����
		break;
	case MENU_SOUND:
		return GET_BOOLVALUE("SOUND", true); 		//0�ر� 1����
		break;
	case MENU_NIGHTMODE:
		return GET_BOOLVALUE("NIGHTMODE", false);	//0�ر� 1����
		break;
	case MENU_ORIENTATION:
		return GET_BOOLVALUE("PORTRAIT", true);		//0���� 1����
		break;
	case MENU_RHMODE:
		return GET_BOOLVALUE("RHMODE", false);		//0�ر� 1����
		break;
	case MENU_AUTORECOVER:
		return GET_BOOLVALUE("TETRIS_RECORD_VALID", false);	//0�ر� 1����
		break;
	case MENU_UPBTN:
		return GET_INTVALUE("UPBUTTON", 0);			//0��ת 1ֱ��
		break;
	default:
		return 0;
		break;
	}
}


void CSetupLayer::onClickMenu(Ref* pSender, int nMenuIdx)
{
	MenuItem* pMenuItem = static_cast<MenuItem*>(pSender);
	int nValue = getValueByMenuIdx(nMenuIdx);
	nValue = ((nValue != 0) ? 0 : 1);
	bool bState = ((nValue == 1) ? true : false);

	//�����˵���������
	switch (nMenuIdx)
	{
		case MENU_VIBRATION:
		{
			SET_INTVALUE("VIBRATION", nValue);			//0���� 1�ر�
			updateSingleMenu(pMenuItem, nMenuIdx);
		}
		break;
		case MENU_SOUND:
		{
			CVolumeLayer* pLayer = CVolumeLayer::create();
			pLayer->setPosition(Size::ZERO);
			this->addChild(pLayer);
		}
		break;
		case MENU_NIGHTMODE:
		{
			SET_BOOLVALUE("NIGHTMODE", bState);				//0�ռ�ģʽ 1ҹ��ģʽ
			m_pGameScene->ChangeColorMode();
			updateAllMenu();
		}
		break;
		case MENU_ORIENTATION:
		{
			SET_BOOLVALUE("PORTRAIT", bState);				//0���� 1����
			updateAllMenu();
			adjustMenuPos();
		}
		break;
		case MENU_RHMODE:
		{
			SET_BOOLVALUE("RHMODE", bState);	//0�ر� 1����
			m_pGameScene->ChangeControllerPos();
			updateSingleMenu(pMenuItem, nMenuIdx);
		}
		break;
		case MENU_AUTORECOVER:
		{
			SET_BOOLVALUE("TETRIS_RECORD_VALID", bState);	//0�ر� 1����
			m_pGameScene->ShowTips(bState ? CGameScene::TIPS_SAVEOPEN : CGameScene::TIPS_SAVECLOSE);
			updateSingleMenu(pMenuItem, nMenuIdx);
		}
		break;
		case MENU_SAVENOW:
		{
			m_pGameScene->SaveTetrisRecord();
		}
		break;
		case MENU_UPBTN:
		{
			SET_INTVALUE("UPBUTTON", nValue);			//0��ת 1ֱ��
			updateSingleMenu(pMenuItem, nMenuIdx);
		}
		break;
		case MENU_AUTHOR:
		{
			m_pGameScene->ShowMyApps();
		}
		break;
		case MENU_RATE:
		{
			m_pGameScene->GiveRate();
		}
		break;
		case MENU_BACK:
		{
			m_pGameScene->QuitSetupLayer();
		}
		break;
		default:
			break;
	}
}


int CSetupLayer::getStrIDByMenuIdx(int nMenuIdx)
{
	switch (nMenuIdx)
	{
		case MENU_VIBRATION: 
			return STRNAME_VIBRATION;
			break;
		case MENU_SOUND: 
			return STRNAME_SOUND;
			break;
		case MENU_NIGHTMODE: 
			return STRNAME_NIGHTMODE;
			break;
		case MENU_ORIENTATION: 
			return STRNAME_ORIENTATION;
			break;
		case MENU_RHMODE:
			return STRNAME_RHMODE;
			break;
		case MENU_AUTORECOVER: 
			return STRNAME_AUTORECOVER;
			break;
		case MENU_SAVENOW: 
			return STRNAME_SAVENOW;
			break;
		case MENU_UPBTN: 
			return STRNAME_UPBTN;
			break;
		case MENU_AUTHOR: 
			return STRNAME_AUTHOR;
			break;
		case MENU_RATE: 
			return STRNAME_RATE;
			break;
		case MENU_BACK:
			return STRNAME_BACK;
			break;
		default: 
			return STRNAME_MAX;
			break;
	}
}


void CSetupLayer::initAllMenu()
{
	Size visibleSize = GET_VISIBLESIZE();
	float fCurHeight = visibleSize.height;

	int nLangID = (CCApplication::getInstance()->getCurrentLanguage() != LanguageType::CHINESE);
	bool bNightMode = getValueByMenuIdx(MENU_NIGHTMODE);
	float fMenuHeight = 0.0f;

	for (int nMainMenuIdx = MAINMENU_MIN; nMainMenuIdx < MAINMENU_MAX; ++nMainMenuIdx)
	{
		fCurHeight -= fMenuHeight;

		//���˵�Label
		int nStrID = getStrIDByMainMenuIdx(nMainMenuIdx);
		string strText = CGeneralManager::getInstance()->GetStringByID(nLangID, nStrID);
		Label* pMainTitle = Label::createWithSystemFont(strText, FONT_NAME, TITLE_FONT_SIZE);
		Size mainTitleSize = GET_CONTENTSIZE(pMainTitle);
		pMainTitle->setColor(bNightMode ? Color3B::WHITE : Color3B::BLACK);
		pMainTitle->setPosition(mainTitleSize.width * 0.5f + MENU_X_PADDING, fCurHeight - mainTitleSize.height);
		this->addChild(pMainTitle);
		m_vecLabel.pushBack(pMainTitle);

		fCurHeight -= mainTitleSize.height * 1.5f;
		float fCurWidth = MENU_X_PADDING;
		fMenuHeight = 0;

		for (int nIndex = 0; nIndex < _countof(MENU_RELATION[nMainMenuIdx]); ++nIndex)
		{
			int nMenuIdx = MENU_RELATION[nMainMenuIdx][nIndex];
			if (nMenuIdx < 0)
			{
				continue;
			}

			//���ݲ˵�ID��ȡ�ַ���
			nStrID = getStrIDByMenuIdx(nMenuIdx);
			strText = CGeneralManager::getInstance()->GetStringByID(nLangID, nStrID);

			//��ȡ��¼ֵ
			int nValue = getValueByMenuIdx(nMenuIdx);
			nValue = (nValue != 0) ? 1 : 0;

			//�˵�
			const string& strSprName = MENU_SPRITE_STRING[nMenuIdx][nValue];
			MenuItemSprite* pMenuItem = MenuItemSprite::create(
				CREATE_SPRITEWITHNAME(CGeneralManager::getInstance()->GetSpriteName(strSprName, bNightMode)),
				CREATE_SPRITEWITHNAME(CGeneralManager::getInstance()->GetSpriteName(strSprName, bNightMode)),
				CC_CALLBACK_1(CSetupLayer::onClickMenu, this, nMenuIdx)
				);
			Size menuItemSize = GET_CONTENTSIZE(pMenuItem);
			pMenuItem->setPosition(fCurWidth + menuItemSize.width * 0.5f, fCurHeight - menuItemSize.height * 0.5f - MENU_Y_PADDING);

			//ͼ��ײ���ǩ
			Label* pTitle = Label::createWithSystemFont(strText, FONT_NAME, NORMAL_FONT_SIZE, Size::ZERO, TextHAlignment::CENTER);
			Size titleSize = GET_CONTENTSIZE(pTitle);
			pTitle->setColor(bNightMode ? Color3B::WHITE : Color3B::BLACK);
			pTitle->setPosition(menuItemSize.width * 0.5f, -MENU_Y_PADDING);
			pTitle->setTag(TITLE_TAG);
			pMenuItem->addChild(pTitle);

			//��ȵ���
			if (fCurWidth + menuItemSize.width >= visibleSize.width)
			{
				fCurWidth = MENU_X_PADDING;
				//�߶ȼ�ȥһ���˵��߶Ⱥͱ�ǩ�߶�
				fCurHeight -= menuItemSize.height + titleSize.height + MENU_Y_PADDING * 2;
				//����λ��
				pMenuItem->setPosition(fCurWidth + menuItemSize.width * 0.5f, fCurHeight - menuItemSize.height * 0.5f - MENU_Y_PADDING);
			}

			//���²˵��ܸ߶�
			if (FLOAT_EQ(fMenuHeight, 0))
			{
				fMenuHeight = menuItemSize.height + titleSize.height + MENU_Y_PADDING * 2;
			}
			fCurWidth += menuItemSize.width * 1.2f + MENU_X_PADDING;

			//����
			m_vecMenuItem.pushBack(pMenuItem);
		}
	}

	//��ӵ��˵�
	Menu* pMenu = Menu::createWithArray(m_vecMenuItem);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);
}


int CSetupLayer::getStrIDByMainMenuIdx(int nMainMenuIdx)
{
	switch (nMainMenuIdx)
	{
	case MAINMENU_GLOBALSET:
		return STRNAME_GLOBALSETTING;
		break;

	case MAINMENU_TETRISSET:
		return STRNAME_TETRISSETTING;
		break;

	case MAINMENU_OTHERSET:
		return STRNAME_OTHER;
		break;

	default:
		return 0;
		break;
	}
}


void CSetupLayer::updateSingleMenu(MenuItem* pMenuItem, int nMenuIdx)
{
	bool bNightMode = getValueByMenuIdx(MENU_NIGHTMODE);
	MenuItemSprite* pMenuItemSpr = static_cast<MenuItemSprite*>(pMenuItem);

	//��ȡֵ
	int nValue = getValueByMenuIdx(nMenuIdx);
	nValue = ((nValue != 0) ? 1 : 0);

	//���²˵�
	const string& strSprName = MENU_SPRITE_STRING[nMenuIdx][nValue];
	pMenuItemSpr->setNormalImage(CREATE_SPRITEWITHNAME(CGeneralManager::getInstance()->GetSpriteName(strSprName, bNightMode)));
	pMenuItemSpr->setSelectedImage(CREATE_SPRITEWITHNAME(CGeneralManager::getInstance()->GetSpriteName(strSprName, bNightMode)));

	//��ȡLabel
	Node* pLabelNode = pMenuItem->getChildByTag(TITLE_TAG);
	if (pLabelNode == nullptr)
	{
		return;
	}

	Label* pLabel = static_cast<Label*>(pLabelNode);
	pLabel->setColor(bNightMode ? Color3B::WHITE : Color3B::BLACK);
}


int CSetupLayer::getMenuCountByMainMenuIdx(int nMainMenuIdx)
{
	if (nMainMenuIdx < MAINMENU_MIN || nMainMenuIdx >= MAINMENU_MAX)
	{
		return 0;
	}

	int nCount = _countof(MENU_RELATION[nMainMenuIdx]);
	for (int nIndex = 0; nIndex < nCount; ++nIndex)
	{
		if (MENU_RELATION[nMainMenuIdx][nIndex] == -1)
		{
			return nIndex;
		}
	}

	return nCount;
}


void CSetupLayer::adjustMenuPosForPortrait()
{
	Size visibleSize = GET_VISIBLESIZE();
	float fCurHeight = visibleSize.height;
	float fMenuHeight = 0.0f;
	int nMenuIdx = 0;

	for (int nMainMenuIdx = 0; nMainMenuIdx < m_vecLabel.size(); ++nMainMenuIdx)
	{
		fCurHeight -= fMenuHeight;

		//���˵�Label
		Label* pMainTitle = m_vecLabel.at(nMainMenuIdx);
		assert(pMainTitle != nullptr);
		Size mainTitleSize = GET_CONTENTSIZE(pMainTitle);
		pMainTitle->setRotation(0);
		pMainTitle->setPosition(mainTitleSize.width * 0.5f + MENU_X_PADDING, fCurHeight - mainTitleSize.height);

		fCurHeight -= mainTitleSize.height * 1.5f;
		float fCurWidth = MENU_X_PADDING;
		fMenuHeight = 0;

		int nMenuCount = getMenuCountByMainMenuIdx(nMainMenuIdx);
		for (int nCount = 0; nCount < nMenuCount; ++nCount, ++nMenuIdx)
		{
			MenuItem* pMenuItem = m_vecMenuItem.at(nMenuIdx);
			assert(pMenuItem != nullptr);
			Size menuItemSize = GET_CONTENTSIZE(pMenuItem);
			pMenuItem->setPosition(fCurWidth + menuItemSize.width * 0.5f, fCurHeight - menuItemSize.height * 0.5f - MENU_Y_PADDING);
			pMenuItem->setRotation(0);

			Node* pLabelNode = pMenuItem->getChildByTag(TITLE_TAG);
			assert(pLabelNode != nullptr);
			Size labelSize = GET_CONTENTSIZE(pLabelNode);

			//��ȵ���
			if (fCurWidth + menuItemSize.width >= visibleSize.width)
			{
				fCurWidth = MENU_X_PADDING;
				//�߶ȼ�ȥһ���˵��߶Ⱥͱ�ǩ�߶�
				fCurHeight -= menuItemSize.height + labelSize.height + MENU_Y_PADDING * 2;
				//����λ��
				pMenuItem->setPosition(fCurWidth + menuItemSize.width * 0.5f, fCurHeight - menuItemSize.height * 0.5f - MENU_Y_PADDING);
			}

			//���²˵��ܸ߶�
			if (FLOAT_EQ(fMenuHeight, 0))
			{
				fMenuHeight = menuItemSize.height + labelSize.height + MENU_Y_PADDING * 2;
			}
			fCurWidth += menuItemSize.width * 1.2f + MENU_X_PADDING;
		}
	}
}


void CSetupLayer::adjustMenuPosForLandscape()
{
	Size visibleSize = GET_VISIBLESIZE();
	float fCurWidth = visibleSize.width;
	float fMenuWidth = 0.0f;
	int nMenuIdx = 0;

	for (int nMainMenuIdx = 0; nMainMenuIdx < m_vecLabel.size(); ++nMainMenuIdx)
	{
		fCurWidth -= fMenuWidth;

		//���˵�Label
		Label* pMainTitle = m_vecLabel.at(nMainMenuIdx);
		assert(pMainTitle != nullptr);
		Size mainTitleSize = GET_CONTENTSIZE(pMainTitle);
		pMainTitle->setRotation(90);
		pMainTitle->setPosition(fCurWidth - mainTitleSize.height * 0.8f, visibleSize.height - mainTitleSize.width * 0.5f - MENU_X_PADDING);

		fCurWidth -= mainTitleSize.height * 1.3f;
		float fCurHeight = visibleSize.height - MENU_X_PADDING;
		fMenuWidth = 0;

		int nMenuCount = getMenuCountByMainMenuIdx(nMainMenuIdx);
		for (int nCount = 0; nCount < nMenuCount; ++nCount, ++nMenuIdx)
		{
			MenuItem* pMenuItem = m_vecMenuItem.at(nMenuIdx);
			assert(pMenuItem != nullptr);
			Size menuItemSize = GET_CONTENTSIZE(pMenuItem);
			pMenuItem->setPosition(fCurWidth - menuItemSize.height * 0.5f - MENU_Y_PADDING, fCurHeight - menuItemSize.width * 0.5f - MENU_X_PADDING * 2);
			pMenuItem->setRotation(90);

			Node* pLabelNode = pMenuItem->getChildByTag(TITLE_TAG);
			Size labelSize = GET_CONTENTSIZE(pLabelNode);
			assert(pLabelNode != nullptr);
			//pLabelNode->setPosition(-MENU_Y_PADDING, menuItemSize.width * 0.5f);

			//��ȵ���
			if (fCurHeight - menuItemSize.width <= 0)
			{
				fCurHeight = visibleSize.height - MENU_X_PADDING;
				//�߶ȼ�ȥһ���˵��߶Ⱥͱ�ǩ�߶�
				fCurWidth -= menuItemSize.height + labelSize.height + MENU_Y_PADDING;
				//����λ��
				pMenuItem->setPosition(fCurWidth - menuItemSize.height * 0.5f - MENU_Y_PADDING, fCurHeight - menuItemSize.width * 0.5f - MENU_X_PADDING);
			}

			//���²˵��ܸ߶�
			if (FLOAT_EQ(fMenuWidth, 0))
			{
				fMenuWidth = menuItemSize.height + labelSize.height + MENU_Y_PADDING;
			}
			fCurHeight -= menuItemSize.width * 1.0f + MENU_X_PADDING * 2;
		}
	}
}


void CSetupLayer::adjustMenuPos()
{
	int nValue = getValueByMenuIdx(MENU_ORIENTATION);
	if (nValue == 1)
	{
		adjustMenuPosForPortrait();
	}
	else
	{
		adjustMenuPosForLandscape();
	}
}

