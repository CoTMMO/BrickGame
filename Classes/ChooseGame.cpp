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
		if (m_iCurTime < 1000)
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
	return m_pAnimData->at(iIndex);
}

//��ȡ��Ϸ����
SCENE_INDEX CChooseGame::GetSceneType()
{
	return SCENE_CHOOSEGAME;
}

//��
void CChooseGame::OnLeft()
{
	if (m_iLevel > 0)
	{
		--m_iLevel;
		m_pGameScene->UpdateLevel(m_iLevel);
	}
}

//��
void CChooseGame::OnRight()
{
	if (m_iLevel < 10)
	{
		++m_iLevel;
		m_pGameScene->UpdateLevel(m_iLevel);
	}
}

//��
void CChooseGame::OnUp()
{
	if (m_iSpeed < 10)
	{
		++m_iSpeed;
		m_pGameScene->UpdateSpeed(m_iSpeed);
	}
}

//��
void CChooseGame::OnDown()
{
	if (m_iSpeed > 0)
	{
		--m_iSpeed;
		m_pGameScene->UpdateSpeed(m_iSpeed);
	}
}

//Fire
void CChooseGame::OnFire()
{

}


//��Ϸ����ת����������
const int GAMEIDX_TO_SCENEIDX[] = 
{
	SCENE_RACING,	//��ӦGAME_RACING
};

//��ʼ
void CChooseGame::OnStart()
{
	//������Ϸ�������ȼ����ٶ�
	SET_INTVALUE("GAME", m_iGameIndex);
	SET_INTVALUE("SPEED", m_iSpeed);
	SET_INTVALUE("LEVEL", m_iLevel);

	//�л�����Ϸ
	m_pGameScene->ShowNewScene(GAMEIDX_TO_SCENEIDX[m_iGameIndex]);
}
