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


//�������кӵ�
void CFroggerGame::UpdateRivers(float dt)
{
	for (int i = ROW_NUM - 2; i >= m_iEndRiverIdx; --i)
	{
		//ż���ӵ�Ĭ��ȫ����䣬�������
		if (i % 2 == 0)
		{
			continue;
		}

		UpdateRiver(i, dt);
	}
}

//����ָ���еĺӵ�
void CFroggerGame::UpdateRiver(int iRowIndex, float dt)
{
	RIVER& stRiver = m_mapRiver[iRowIndex];
	
	//����ʱ��
	stRiver.iCurTime += dt;

	//�ж��Ƿ��˸���ʱ��
	if (stRiver.iCurTime >= stRiver.arrRefreshTime[stRiver.iCurState])
	{
		//����ʱ��
		stRiver.iCurTime = 0;

		//��鷽��
		if (stRiver.bLeft)
		{
			//�����ƶ��������ұ߲�����Brick
			for (int i = 0; i < COLUMN_NUM - 1; ++i)
			{
				m_arrBrickState[iRowIndex][i] = m_arrBrickState[iRowIndex][i + 1];
			}
			m_arrBrickState[iRowIndex][COLUMN_NUM - 1] = stRiver.iCurState;
		}
		else
		{
			//�����ƶ���������߲�����Brick
			for (int i = COLUMN_NUM - 1; i > 0; --i)
			{
				m_arrBrickState[iRowIndex][i] = m_arrBrickState[iRowIndex][i - 1];
			}
			m_arrBrickState[iRowIndex][0] = stRiver.iCurState;
		}

		//�������ӣ�����ﵽ���ޣ�������CurState
		++stRiver.iCount;
		if (stRiver.iCount == stRiver.arrMaxCount[stRiver.iCurState])
		{
			stRiver.iCurState = !stRiver.iCurState;
			//���ü���
			stRiver.iCount = 0;
		}
	}
}


//��ʼ�����ݡ�������
void CFroggerGame::InitData()
{
	//���ó�ʼ����λ��
	m_iSelfRowIdx = ROW_NUM - 1;
	m_iSelfColIdx = COLUMN_NUM / 2 - 1;

	//��ʼ�ӵ�������
	m_iEndRiverIdx = ROW_NUM / 2;

	//��ʼ�������ӵ�״̬����

}
