#pragma once
#include "cocos2d.h"
class CLoadScene : public cocos2d::LayerColor
{
public:
	CLoadScene();
	~CLoadScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	//��ת����Ϸ����
	void ToGameScene(float dt);

	CREATE_FUNC(CLoadScene);
};

