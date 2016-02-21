#include "ChooseGame.h"
#include "GeneralManager.h"

CChooseGame::CChooseGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{

}


CChooseGame::~CChooseGame()
{

}


//��ʼ��
void CChooseGame::Init()
{
	m_iGameIndex = GET_INTVALUE("GAME", GAME_RACING);
	
	//�����ٶȺ͵ȼ���ʾ
	m_iSpeed = 0;
	m_iLevel = 0;
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSpeed(m_iSpeed);

	m_iAnimIndex = 0;
	m_pAnimData = nullptr;
	m_bFirstAnim = false;
	m_fCurTime = 0;

	//���÷���
	m_pGameScene->UpdateScore(0, false);
	m_pGameScene->UpdateHighScore(m_iGameIndex);

	//��������
	if (!AUDIO_INSTANCE()->isBackgroundMusicPlaying())
	{
		PLAY_BGMUSIC(BGM_START, true);
	}

	//����С����״̬
	m_pGameScene->UpdateSmallBricks();
}


//����
void CChooseGame::Play(float dt)
{
	m_fCurTime += dt;
	if (!m_bFirstAnim)
	{
		m_bFirstAnim = true;
	}
	else
	{
		if (m_fCurTime < REFRESH_INTERVAL)
		{
			return;
		}

		m_fCurTime = 0;
	}

	m_pAnimData = CGeneralManager::getInstance()->GetAnimData(m_iGameIndex, m_iAnimIndex);

	//��һ������
	if (++m_iAnimIndex >= ANIM_NUM)
	{
		m_iAnimIndex = 0;
	}

	//��������Brick
	m_pGameScene->UpdateBricks();
}

//��ȡ��ǰBrick״̬
bool CChooseGame::GetBrickState(int iRowIndex, int iColIndex)
{
	int iIndex = iRowIndex * COLUMN_NUM + iColIndex;
	return m_pAnimData->at(iIndex) == 1;
}


bool CChooseGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//��ȡ��Ϸ����
SCENE_INDEX CChooseGame::GetSceneType()
{
	return SCENE_CHOOSEGAME;
}

//��
void CChooseGame::OnLeftBtnPressed()
{
	if (--m_iLevel < 0)
	{
		m_iLevel = LEVEL_MAX;
	}

	m_pGameScene->UpdateLevel(m_iLevel);
}


//��
void CChooseGame::OnRightBtnPressed()
{
	if (++m_iLevel > LEVEL_MAX)
	{
		m_iLevel = 0;
	}

	m_pGameScene->UpdateLevel(m_iLevel);
}


//��
void CChooseGame::OnUpBtnPressed()
{
	if (++m_iSpeed > SPEED_MAX)
	{
		m_iSpeed = 0;
	}

	m_pGameScene->UpdateSpeed(m_iSpeed);
}


//��
void CChooseGame::OnDownPressed()
{
	if (--m_iSpeed < 0)
	{
		m_iSpeed = SPEED_MAX;
	}

	m_pGameScene->UpdateSpeed(m_iSpeed);
}


//Fire
void CChooseGame::OnFireBtnPressed()
{
	if (++m_iGameIndex >= GAME_MAX)
	{
		m_iGameIndex = 0;
	}

	m_iAnimIndex = 0;

	//������߷���ʾ
	m_pGameScene->UpdateHighScore(m_iGameIndex);

	Play(REFRESH_INTERVAL);
}


//��Ϸ����ת����������
const int GAMEIDX_TO_SCENEIDX[] =
{
	SCENE_TANK,			//��ӦGAME_TANK
	SCENE_RACING,		//��ӦGAME_RACING
	SCENE_SNAKE,		//��ӦGAME_SNAKE
	SCENE_MATCH,		//��ӦGAME_MATCH
	SCENE_FROGGER,		//��ӦGAME_FROGGER
	SCENE_PINBALL,		//��ӦGAME_PINBALL
	SCENE_TETRIS,		//��ӦGAME_TETRIS
};

//��ʼ
void CChooseGame::OnStart()
{
	//ֹͣ��������
	STOP_BGMUSIC();

	//���ſ�ʼ��Ч
	PLAY_EFFECT(EFFECT_PAUSE);

	//������Ϸ�������������ȼ����ٶ�
	SET_INTVALUE("GAME", m_iGameIndex);
	SET_INTVALUE("SPEED", m_iSpeed);
	SET_INTVALUE("LEVEL", m_iLevel);
	SET_INTVALUE("LIFE", 4);			//Ĭ��������4

	//�л�����Ϸ
	m_pGameScene->RunScene(GAMEIDX_TO_SCENEIDX[m_iGameIndex]);
}
