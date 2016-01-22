#include "TankGame.h"


CTankGame::CTankGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{
}


CTankGame::~CTankGame()
{
}


//��ʼ��
void CTankGame::Init()
{
	//��ȡ��ѡ����Ϸ�������õ��ٶȺ͵ȼ�
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);

	//Ĭ��������Ϊ4
	m_iLife = GET_INTVALUE("LIFE", 4);

	//��ʼ����ǰ��������������������
	m_iScore = 0;

	//���½��棬�������ȼ�������
	m_pGameScene->UpdateScore(m_iScore);
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSmallBricks();

	InitData();
}


//����
void CTankGame::Play(float dt)
{

}

//�ṩ��ÿ�θ��µ���Brick��Ϸ����ǰֻ����Ϸ������ʹ�ã���ȡ��ǰ�ı��Brick��������
void CTankGame::GetCurPos(int& iRowIndex, int& iColIndex)
{

}

//��ȡ��ǰBrick״̬
bool CTankGame::GetBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//��ȡС���������еķ���״̬
bool CTankGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//��ȡ��Ϸ����
SCENE_INDEX CTankGame::GetSceneType()
{
	return SCENE_TANK;
}

//����
void CTankGame::OnLeftBtnPressed()
{

}

//���ͷ�
void CTankGame::OnLeftBtnReleased()
{

}

//�Ұ���
void CTankGame::OnRightBtnPressed()
{

}

//���ͷ�
void CTankGame::OnRightBtnReleased()
{

}
//�ϰ���
void CTankGame::OnUpBtnPressed()
{

}

//���ͷ�
void CTankGame::OnUpBtnReleased()
{

}

//�°���
void CTankGame::OnDownPressed()
{

}

//���ͷ�
void CTankGame::OnDownReleased()
{

}

//Fire����
void CTankGame::OnFireBtnPressed()
{

}

//Fire�ͷ�
void CTankGame::OnFireBtnReleased()
{

}


void CTankGame::InitData()
{

}