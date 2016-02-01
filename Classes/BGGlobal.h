#pragma once

// ---- ͷ�ļ� ----
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../cocos/ui/CocosGUI.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

#include <map>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

#define FLOAT_EQ(a, b) (fabs(a - b) < 1e-6)

#define CC_RETURN_FALSE_IF(exp) if (exp){return false;}


// ---- cocos ���ú����궨�� ----
#define DIRECTOR_INSTANCE Director::getInstance

#define GET_VISIBLESIZE Director::getInstance()->getVisibleSize

#define REPLACE_SCENE Director::getInstance()->replaceScene

#define PAUSE_SCENE Director::getInstance()->pause

#define RESUME_SCENE Director::getInstance()->resume

#define SET_TIMESCALE(s) Director::getInstance()->getScheduler()->setTimeScale(s)

#define ADD_ANIM(anim, name) AnimationCache::getInstance()->addAnimation(anim, name)

#define GET_ANIM(name) AnimationCache::getInstance()->getAnimation(name)

#define GET_SPRITEFRAME(name) SpriteFrameCache::getInstance()->getSpriteFrameByName(name)

#define ADD_SPRITEFRAME(name) SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name)

#define CREATE_SPRITEWITHNAME(name) Sprite::createWithSpriteFrameName(name)

#define CREATE_SPRITE(name) Sprite::create(name)

#define AUDIO_INSTANCE CocosDenshion::SimpleAudioEngine::getInstance

#define PRELOAD_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name)

#define PLAY_BGMUSIC(name) CGeneralManager::getInstance()->PlayMusic(name)

#define LOOP_PLAY_BGMUSIC(name) CGeneralManager::getInstance()->PlayMusic(name, true)

#define STOP_BGMUSIC CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic

#define PAUSE_BGMUSIC CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic

#define PRELOAD_EFFECT(name) CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(name)

#define PLAY_EFFECT(name) CGeneralManager::getInstance()->PlayEffect(name)

#define SET_SOUNDSTATE(state) CGeneralManager::getInstance()->SetSoundState(state)

#define GET_SOUNDSTATE CGeneralManager::getInstance()->GetSoundState

#define GET_CONTENTSIZE(sprite) sprite->getContentSize()

#define USERDEFAULT_INSTANCE UserDefault::getInstance

#define GET_INTVALUE(key, value) UserDefault::getInstance()->getIntegerForKey(key, value)

#define SET_INTVALUE(key, value) UserDefault::getInstance()->setIntegerForKey(key, value)

#define GET_BOOLVALUE(key, value) UserDefault::getInstance()->getBoolForKey(key, value)

#define SET_BOOLVALUE(key, value) UserDefault::getInstance()->setBoolForKey(key, value)


//ͨ�ýṹ��
struct POSITION
{
	int m_iRowIdx;			//��λ��

	int m_iColIdx;			//��λ��

	bool operator== (const POSITION& rhs) const
	{
		return this->m_iColIdx == rhs.m_iColIdx && this->m_iRowIdx == rhs.m_iRowIdx;
	}
};


//����ö��
enum
{
	//����
	ROW_NUM = 20,
	COLUMN_NUM = 14,

	//������
	BRICK_WIDTH = 32,
	BRICK_HEIGHT = 32,

	//�ٶȺ͵ȼ����ֵ
	SPEED_MAX = 10,
	LEVEL_MAX = 10,
};

//����ö��
enum DIRECTION
{
	DIR_MIN = 0,
	DIR_RIGHT = DIR_MIN,
	DIR_DOWN,
	DIR_LEFT,
	DIR_UP,
	DIR_MAX,
};


//��Ϸ����ö��
enum SCENE_INDEX
{
	SCENE_INVALID = -1,

	SCENE_GAMEOVER,				//��Ϸ��������

	SCENE_CHOOSEGAME,			//ѡ�����

	SCENE_TANK,					//��Ϸ���� - ̹�˴�ս

	SCENE_RACING,				//��Ϸ���� - ����

	SCENE_SNAKE,				//��Ϸ���� - ̰����

	SCENE_MATCH,				//��Ϸ���� - ƥ��

	SCENE_FROGGER,				//��Ϸ���� - ���ܹ���

	SCENE_MAX,					//���ֵ
};

enum GAME_LIST
{
	GAME_INVALID = -1,			//��Ч

	GAME_TANK,					//̹�˴�ս
	
	GAME_RACING,				//����

	GAME_SNAKE,					//̰����

	GAME_MATCH,					//ƥ��

	GAME_FROGGER,				//���ܹ���

	GAME_MAX,					//���ֵ
};

enum GAME_STATE
{
	GAMESTATE_RUNNING,				//������

	GAMESTATE_OVER,					//����

	GAMESTATE_PASS,					//ͨ��
};


//ȫ�ֳ���
extern const bool BOOM_STATE[4][4];

//�ַ�������
extern const char* BGM_START;

extern const char* EFFECT_ADD;
extern const char* EFFECT_BOOM;
extern const char* EFFECT_CHANGE;
extern const char* EFFECT_CHANGE2;
extern const char* EFFECT_DELETE;
extern const char* EFFECT_NEXT;
extern const char* EFFECT_PAUSE;
extern const char* EFFECT_SOUNDOFF;
extern const char* EFFECT_SOUNDON;
extern const char* EFFECT_WALL;

// ---- ͨ�ú��� ---- 
int Random(int iStart, int iEnd, int iStep = 1);

