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

	//���µ�����ǩ
	void UpdateSingleMenuAndLabel(int nMenuIdx);

	CREATE_FUNC(CSetupLayer);

private:
	//�����˵��ͱ�ǩ
	void CreateAllMenuAndLabel();
	
	//���²˵��ͱ�ǩ
	void UpdateAllMenuAndLabel();

	//�����˵��ͱ�ǩλ��
	void AdjustMenuLabelPos();

	//��ȡ����
	int GetValueByMenuIdx(int nMenuIdx);

	//����˵�����
	void OnClickMenu(Ref* pSender, int nMenuIdx);

	//�˵�ö��ת��ΪStrID
	int GetStrIDByMenuIdx(int nMenuIdx);

	//���˵��Ƿ�Ϊ����
	bool CheckMenuTitleFlag(int nMenuIdx);

private:
	enum
	{
		MENU_X_PADDING = 10,
		MENU_Y_PADDING = 10,

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
		TITLE_FONT_SIZE = 36,
		NORMAL_FONT_SIZE = 29,
#else
		TITLE_FONT_SIZE = 36,
		NORMAL_FONT_SIZE = 29,
#endif
	};

private:
	Vector<Label*>				m_vecLabel;		//��ǩ�б�
	
	Vector<MenuItem*>			m_vecMenuItem;	//�˵��б�

	CGameScene*					m_pGameScene;	//CGameScene
};

