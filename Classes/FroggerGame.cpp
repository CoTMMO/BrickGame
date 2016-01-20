#include "FroggerGame.h"


CFroggerGame::CFroggerGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{
}


CFroggerGame::~CFroggerGame()
{
}


//��ʼ��
void CFroggerGame::Init();

//����
void CFroggerGame::Play(float dt);

//��ȡ��ǰBrick״̬
bool CFroggerGame::GetBrickState(int iRowIndex, int iColIndex);

//������
bool CFroggerGame::GetSmallBrickState(int iRowIndex, int iColIndex);

//��ȡ��Ϸ����
SCENE_INDEX CFroggerGame::GetSceneType();

//����
void CFroggerGame::OnLeftBtnPressed();

//�Ұ���
void CFroggerGame::OnRightBtnPressed();

//�ϰ���
void CFroggerGame::OnUpBtnPressed();

//�°���
void CFroggerGame::OnDownPressed();

//Fire����
void CFroggerGame::OnFireBtnPressed();
