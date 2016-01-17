#include "ChooseGame.h"
#include "DataManager.h"

CChooseGame::CChooseGame() : m_pAnimData(nullptr), m_iAnimIndex(0), m_bFirstAnim(false)
{

}


CChooseGame::~CChooseGame()
{

}


//��ʼ��
void CChooseGame::Init()
{

}


//��Ϸ���У�����falseʱ��ʾ��Ϸ����
bool CChooseGame::Play()
{
	m_pAnimData = CDataManager::getInstance()->GetAnimData(RACING, m_iAnimIndex);
	
	//��һ������
	if (++m_iAnimIndex >= ANIM_NUM)
	{
		m_iAnimIndex = 0;
	}

	return true;
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
	return CHOOSE_GAME;
}


//��ȡÿ��ִ����Play��ȴ���ʱ��
float CChooseGame::GetRefreshTime()
{
	if (!m_bFirstAnim)
	{
		m_bFirstAnim = true;
		return 0;
	}
	return 1000;
}
