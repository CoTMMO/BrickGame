#include "RacingGame.h"


CRacingGame::CRacingGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{
}


CRacingGame::~CRacingGame()
{
}


//��ʼ��
void CRacingGame::Init()
{
	m_iSpeed = GET_INTVALUE("Speed", 0);
	m_iLevel = GET_INTVALUE("Level", 0);

	//Ĭ��������Ϊ4
	m_iLife = 4;

	//��ʼ��Brick
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrBrickState[i][j] = false;
		}
	}
}

//����
void CRacingGame::Play(float dt)
{
	m_pGameScene->UpdateBricks();
}

//��ȡ��ǰBrick״̬
bool CRacingGame::GetBrickState(int iRowIndex, int iColIndex)
{
	return m_arrBrickState[iRowIndex][iColIndex];
}


//��ȡ��Ϸ����
SCENE_INDEX CRacingGame::GetSceneType()
{
	return SCENE_RACING;
}


//��
void CRacingGame::OnLeft()
{

}

//��
void CRacingGame::OnRight()
{

}

//��
void CRacingGame::OnUp()
{

}

//��
void CRacingGame::OnDown()
{

}

//Fire
void CRacingGame::OnFire()
{

}

