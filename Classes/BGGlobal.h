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
#include "../cocos/audio/include/SimpleAudioEngine.h"

#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <fstream>

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

#define FLOAT_EQ(a, b) (fabs(a - b) < 1e-6)

#define CC_RETURN_FALSE_IF(exp) if (exp){return false;}

#define FOR_EACH_CONTAINER(type, container, it) for (type::iterator it = container.begin(); it != container.end(); ++it)


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

#define PLAY_BGMUSIC(name, loop) CGeneralManager::getInstance()->PlayMusic(name, loop)

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

	POSITION() : m_iRowIdx(0), m_iColIdx(0)
	{

	};

	POSITION(int iRowIdx, int iColIdx) : m_iRowIdx(iRowIdx), m_iColIdx(iColIdx)
	{

	};

	bool operator== (const POSITION& rhs) const
	{
		return this->m_iColIdx == rhs.m_iColIdx && this->m_iRowIdx == rhs.m_iRowIdx;
	}

	POSITION& operator+= (const POSITION& rhs)
	{
		this->m_iColIdx += rhs.m_iColIdx;
		this->m_iRowIdx += rhs.m_iRowIdx;

		return *this;
	}

	const POSITION operator+ (const POSITION& rhs) const
	{
		POSITION temp(*this);
		temp += rhs;
		return temp;
	}


	POSITION& operator-= (const POSITION& rhs)
	{
		this->m_iColIdx -= rhs.m_iColIdx;
		this->m_iRowIdx -= rhs.m_iRowIdx;

		return *this;
	}

	const POSITION operator- (const POSITION& rhs) const
	{
		POSITION temp(*this);
		temp -= rhs;
		return temp;
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

	SCENE_PINBALL,				//��Ϸ���� - ����

	SCENE_TETRIS,				//��Ϸ���� - ����˹����

	SCENE_FLAPPYBIRD,			//��Ϸ���� - flappybird

	SCENE_TETRIS2,				//��Ϸ���� - ����˹����2

	SCENE_PINBALL2,				//��Ϸ���� - ����2

	SCENE_HITBRICK,				//��Ϸ���� - ��ש��

	SCENE_ADDBRICK,				//��Ϸ���� - ��ש��

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

	GAME_PINBALL,				//����

	GAME_TETRIS,				//����˹����

	GAME_FLAPPYBIRD,			//FlappyBird

	GAME_TETRIS2,				//����˹����2

	GAME_PINBALL2,				//����2

	GAME_HITBRICK,				//��ש��

	GAME_ADDBRICK,				//��ש��

	GAME_MAX,					//���ֵ
};

enum GAME_STATE
{
	GAMESTATE_RUNNING,				//������

	GAMESTATE_PAUSE,				//��ͣ

	GAMESTATE_OVER,					//����

	GAMESTATE_PASS,					//ͨ��
};

//��ʾ����
enum TIPS_TYPE
{
	TIPS_INVALID,
	TIPS_EXIT,
	TIPS_SAVEOPEN,
	TIPS_SAVECLOSE,
	TIPS_SAVEOK,
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

//�����Ч������
void ClearInvalidNums();

//�����Ч������
void AddInvalidNum(int iNum);

//��ȡ����
double GetMillSecond();
