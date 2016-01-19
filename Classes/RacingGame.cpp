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

	//��Ϸ�������
	m_bGameOver = false;

	//��ʼ����ǰ����
	m_iScore = 0;

	m_arrRowIdx[0] = -1;
	m_arrRowIdx[1] = -1;

	InitBrick();


}

//����
void CRacingGame::Play(float dt)
{
	RandSeed();

	if (!m_bFirstShow)
	{
		m_fWaitTime += dt * 1000;
		if (m_fWaitTime < DEFAULT_INTERVAL)
		{
			return;
		}

		//����ʱ��
		m_fWaitTime = 0;
		UpdateBricks();
	}
	else
	{
		RandCreateCars();
		m_bFirstShow = false;
	}

	m_pGameScene->UpdateBricks();
}


//��ȡ��ǰBrick״̬
bool CRacingGame::GetBrickState(int iRowIndex, int iColIndex)
{
	//����λ��
	int iCarColIdx = m_iCarPos * 3 + 2;
	int iCarRowIdx = ROW_NUM - 2;

	if (m_bGameOver)
	{
		//��ը
		if (   (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx + 1)	//�ĸ���
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx - 2)
			|| (iRowIndex == iCarRowIdx - 2 && iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx - 2 && iColIndex == iCarColIdx - 2)
			|| (iRowIndex == iCarRowIdx		&& iColIndex == iCarColIdx - 1)	//�м�
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx	  )
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx - 1)
			|| (iRowIndex == iCarRowIdx		&& iColIndex == iCarColIdx	  )
			)
		{
			return true;
		}
	}
	else
	{
		//�������Լ�
		if (   (iRowIndex == iCarRowIdx		&& iColIndex == iCarColIdx	  )
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx	  )
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx - 1)
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx - 1)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx	  )
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx - 2 && iColIndex == iCarColIdx	  )
			)
		{
			return true;
		}

	}
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
	if (m_iCarPos > 0)
	{
		--m_iCarPos;
		m_pGameScene->UpdateBricks();
	}
}

//��
void CRacingGame::OnRight()
{
	if (m_iCarPos < ROAD_COUNT - 1)
	{
		++m_iCarPos;
		m_pGameScene->UpdateBricks();
	}
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
	//����
}


//����Brick���������
void CRacingGame::UpdateBricks()
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

	m_arrRowIdx[0] += m_arrRowIdx[0] > 0 ? 1 : 0;
	m_arrRowIdx[1] += m_arrRowIdx[1] > 0 ? 1 : 0;
	if (m_arrRowIdx[1] == ROW_DISTANCE * 2)
	{
		m_iScore += 100;
		m_pGameScene->UpdateScore(m_iScore);
	}
	
	if (m_arrRowIdx[0] == 2 + ROW_DISTANCE)
	{
		RandCreateCars();
	}
}


//������
void CRacingGame::RandCreateCars()
{
	//����
	//�ڿڿ�
	//����		λ���Ը���Ϊ׼
	//�ڡ���

	int iCount = rand() % CAR_MAXNUM + 1;
	for (int i = 0; i < iCount; ++i)
	{
		int iRoadIdx = rand() % ROAD_COUNT;
		int iColIdx = iRoadIdx * 3 + 2;

		//������
		m_arrCurBrick[CAR_DEFAULTROW + 1][iColIdx - 1] = 1;
		m_arrCurBrick[CAR_DEFAULTROW + 1][iColIdx + 1] = 1;
		//������
		m_arrCurBrick[CAR_DEFAULTROW][iColIdx] = 1;
		//�ڶ���
		m_arrCurBrick[CAR_DEFAULTROW - 1][iColIdx] = 1;
		m_arrCurBrick[CAR_DEFAULTROW - 1][iColIdx - 1] = 1;
		m_arrCurBrick[CAR_DEFAULTROW - 1][iColIdx + 1] = 1;
		//��һ��
		m_arrCurBrick[CAR_DEFAULTROW - 2][iColIdx] = 1;
	}

	m_arrRowIdx[1] = m_arrRowIdx[0];
	m_arrRowIdx[0] = CAR_DEFAULTROW;
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
	m_iCarPos = rand() % 4;
}


//��ȡ���ֵ
void CRacingGame::RandSeed()
{
	srand((unsigned)time(nullptr));
}
