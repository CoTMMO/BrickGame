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
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);

	//Ĭ��������Ϊ4
	m_iLife = GET_INTVALUE("LIFE", 4);

	//Ĭ�϶�����������·��
	m_iRoadSignCount = 3;

	//�ȴ�����ʱ��
	m_fWaitTime = 0;

	//��ʼ����һ����ʾ���
	m_bFirstShow = true;

	InitBrick();
}

//����
void CRacingGame::Play(float dt)
{
	if (!m_bFirstShow)
	{
		m_fWaitTime += dt * 1000;
		if (m_fWaitTime < 500)
		{
			return;
		}

		//����ʱ��
		m_fWaitTime = 0;
	}
	else
	{
		m_bFirstShow = false;
	}
	
	AddNewLine();
	m_pGameScene->UpdateBricks();
}

//��ȡ��ǰBrick״̬
bool CRacingGame::GetBrickState(int iRowIndex, int iColIndex)
{
	return m_arrCurBrick[iRowIndex][iColIndex];
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


//�������
void CRacingGame::AddNewLine()
{
	//����һ��Ų����һ��
	for (int i = ROW_NUM - 1; i >= 1; --i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrCurBrick[i][j] = m_arrCurBrick[i - 1][j];
		}
	}

	if (m_iRoadSignCount < 3)
	{
		//���У������ǰ·������С��3����������·��
		m_arrCurBrick[0][0] = true;
		m_arrCurBrick[0][COLUMN_NUM - 1] = true;
		for (int i = 1; i < COLUMN_NUM - 1; ++i)
		{
			m_arrCurBrick[0][i] = false;
		}
	}
	else
	{
		m_iRoadSignCount = -1;
		for (int i = 0; i < COLUMN_NUM; ++i)
		{
			m_arrCurBrick[0][i] = false;
		}
	}

	++m_iRoadSignCount;
}


//������
void CRacingGame::DrawCar(int iRoadIdx, int iRowIdx, bool bSelf)
{

}


void CRacingGame::InitBrick()
{
	//��ʼ��Brick
	int iCount = 0;
	for (int i = 0; i < ROW_NUM; ++i)
	{
		int iBeginIndex = 0;
		int iEndIndex = COLUMN_NUM - 1;
		if (iCount < 3)
		{
			m_arrCurBrick[i][0] = true;
			m_arrCurBrick[i][iEndIndex] = true;

			iBeginIndex = 1;
			iEndIndex -= 1;
		}
		else
		{
			iCount = -1;
		}

		for (int j = iBeginIndex; j <= iEndIndex; ++j)
		{
			m_arrCurBrick[i][j] = false;
		}

		++iCount;
	}

	//����Լ�������λ��
	srand((unsigned)time(nullptr));
	m_iCarPos = rand() % 4;
}


//�Ƿ���Ϸ����
bool CRacingGame::IsGameOver()
{
	return false;
}


//����Brick
void CRacingGame::UpdateBricks()
{

}
