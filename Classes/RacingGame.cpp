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

}

//����
void CRacingGame::Play(float dt)
{
	return ;
}

//��ȡ��ǰBrick״̬
bool CRacingGame::GetBrickState(int iRowIndex, int iColIndex)
{
	return true;
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

