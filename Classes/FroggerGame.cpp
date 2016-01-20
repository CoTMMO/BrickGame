#include "FroggerGame.h"


CFroggerGame::CFroggerGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{
}


CFroggerGame::~CFroggerGame()
{
}


//��ʼ��
void CFroggerGame::Init()
{

}

//����
void CFroggerGame::Play(float dt)
{
	m_pGameScene->UpdateBricks();
}

//��ȡ��ǰBrick״̬
bool CFroggerGame::GetBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//������
bool CFroggerGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//��ȡ��Ϸ����
SCENE_INDEX CFroggerGame::GetSceneType()
{
	return SCENE_FROGGER;
}

//����
void CFroggerGame::OnLeftBtnPressed()
{

}

//�Ұ���
void CFroggerGame::OnRightBtnPressed()
{

}

//�ϰ���
void CFroggerGame::OnUpBtnPressed()
{

}

//�°���
void CFroggerGame::OnDownPressed()
{

}

//Fire����
void CFroggerGame::OnFireBtnPressed()
{

}
