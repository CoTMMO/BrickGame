#pragma once
#include "BGGlobal.h"

class CGameScene;

class CSetupLayer : public cocos2d::Layer
{
public:
	CSetupLayer();
	~CSetupLayer();

	//init
	bool Init(CGameScene* pGameScene);

	//���µ����˵�
	void UpdateSingleMenu(int nMenuIdx);

	CREATE_FUNC(CSetupLayer);

private:
	//�����˵�
	void initAllMenu();
	
	//��ȡ����
	int getValueByMenuIdx(int nMenuIdx);

	//����˵�����
	void onClickMenu(Ref* pSender, int nMenuIdx);

	//�˵�ö��ת��ΪStrID
	int getStrIDByMenuIdx(int nMenuIdx);

	//���˵�ö��ת��ΪStrID
	int getStrIDByMainMenuIdx(int nMainMenuIdx);

	//�����˵��ͱ�ǩλ��(Port)
	void adjustMenuPosForPortrait();

	//�����˵��ͱ�ǩλ��(Land)
	void adjustMenuPosForLandscape();

	//�����˵��ͱ�ǩλ��
	void adjustMenuPos();

	//���²˵�
	void updateSingleMenu(MenuItem* pMenuItem, int nMenuIdx);

	//���²˵��ͱ�ǩ
	void updateAllMenu();

	//�������˵�������ȡ�˵�����
	int getMenuCountByMainMenuIdx(int nMainMenuIdx);

public:
	enum
	{
		MENU_X_PADDING = 35,
		MENU_Y_PADDING = 10,

		TITLE_FONT_SIZE = 32,
		NORMAL_FONT_SIZE = 26,

		TITLE_TAG = 1420,
		BARRIER_TAG = 1421,
	};

private:
	Vector<Label*>				m_vecLabel;		//��ǩ�б�
	
	Vector<MenuItem*>			m_vecMenuItem;	//�˵��б�

	CGameScene*					m_pGameScene;	//CGameScene
};

