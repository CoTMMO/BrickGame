#include "ChooseGame.h"
#include "DataManager.h"

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
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);

	m_iAnimIndex = 0;
	m_pAnimData = nullptr;
	m_bFirstAnim = false;
	m_iCurTime = 0;
}


//����
void CChooseGame::Play(float dt)
{
	m_iCurTime += dt * 1000;
	if (!m_bFirstAnim)
	{
		m_bFirstAnim = true;
	}
	else
	{
		if (m_iCurTime < REFRESH_INTERVAL)
		{
			return;
		}

		m_iCurTime = 0;
	}

	m_pAnimData = CDataManager::getInstance()->GetAnimData(m_iGameIndex, m_iAnimIndex);
	
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

//��ȡ��Ϸ����
SCENE_INDEX CChooseGame::GetSceneType()
{
	return SCENE_CHOOSEGAME;
}

//��
void CChooseGame::OnLeftBtnPressed()
{
	if (m_iLevel > 0)
	{
		--m_iLevel;
		m_pGameScene->UpdateLevel(m_iLevel);
	}
}


//��
void CChooseGame::OnRightBtnPressed()
{
	if (m_iLevel < LEVEL_MAX)
	{
		++m_iLevel;
		m_pGameScene->UpdateLevel(m_iLevel);
	}
}


//��
void CChooseGame::OnUpBtnPressed()
{
	if (m_iSpeed < SPEED_MAX)
	{
		++m_iSpeed;
		m_pGameScene->UpdateSpeed(m_iSpeed);
	}
}


//��
void CChooseGame::OnDownPressed()
{
	if (m_iSpeed > 0)
	{
		--m_iSpeed;
		m_pGameScene->UpdateSpeed(m_iSpeed);
	}
}


//Fire
void CChooseGame::OnFireBtnPressed()
{
	if (++m_iGameIndex >= GAME_MAX)
	{
		m_iGameIndex = 0;
	}

	m_iAnimIndex = 0;

	Play(REFRESH_INTERVAL);
}


//��Ϸ����ת����������
const int GAMEIDX_TO_SCENEIDX[] = 
{
	SCENE_RACING,	//��ӦGAME_RACING
	SCENE_FROGGER,	//��ӦGAME_FROGGER
	SCENE_TANK,		//��ӦGAME_TANK
};

//��ʼ
void CChooseGame::OnStart()
{
	//������Ϸ�������������ȼ����ٶ�
	SET_INTVALUE("GAME", m_iGameIndex);
	SET_INTVALUE("SPEED", m_iSpeed);
	SET_INTVALUE("LEVEL", m_iLevel);
	SET_INTVALUE("LIFE", 4);			//Ĭ��������4

	//�л�����Ϸ
	m_pGameScene->RunScene(GAMEIDX_TO_SCENEIDX[m_iGameIndex]);
}
