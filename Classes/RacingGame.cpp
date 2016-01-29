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
	//��ȡ��ѡ����Ϸ�������õ��ٶȺ͵ȼ�
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);

	//Ĭ��������Ϊ4
	m_iLife = GET_INTVALUE("LIFE", 4);

	//��ʼ����ǰ����
	m_iScore = 0;

	//���½��棬�������ȼ�������
	m_pGameScene->UpdateScore(m_iScore);
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSmallBricks();

	InitData();
}


void CRacingGame::InitData()
{
	//��ʼ����������������
	m_iPassCarCount = 0;

	//Ĭ�϶�����������·��
	m_iRoadSignCount = 3;

	//�ȴ�����ʱ��
	m_fWaitTime = 0;

	//��ʼ����һ����ʾ���
	m_bFirstShow = true;

	//��ʼ����Ϸ״̬
	m_enGameState = GAMESTATE_RUNNING;

	//���ü�¼���������������λ��
	m_arrRowIdx[0] = -1;
	m_arrRowIdx[1] = -1;

	//��ʼ�����ٱ��
	m_bImproveSpeed = false;

	//��ʼ����ը��ʾ/���ر�ǣ�Ĭ����ʾ
	m_bShowBoom = true;

	//��ʼ����˸��ըЧ������
	m_iShowBoomCount = 0;

	InitBrick();
}

//����
void CRacingGame::Play(float dt)
{
	//����Ƿ���Ϸ����
	if (m_arrCurBrick[ROW_NUM - 4][m_iCarPos * 3 + 2] == 1 && m_arrCurBrick[ROW_NUM - 5][m_iCarPos * 3 + 2] == 1)
	{
		m_enGameState = GAMESTATE_OVER;
	}

	if (!m_bFirstShow)
	{
		m_fWaitTime += dt;
		if (m_fWaitTime < GetWaitInterval())
		{
			return;
		}

		//����ʱ��
		m_fWaitTime = 0;
	}
	else
	{
		RandCreateCars();
		m_bFirstShow = false;
	}

	if (m_enGameState == GAMESTATE_RUNNING)
	{
		UpdateBricks();
	}
	else if (m_enGameState == GAMESTATE_OVER)
	{
		if (m_iShowBoomCount < BOOM_SHOWCOUNT)
		{
			m_bShowBoom = !m_bShowBoom;
			++m_iShowBoomCount;
		}
		else
		{
			//����ʣ������
			--m_iLife;
			m_pGameScene->UpdateSmallBricks();

			//����Ƿ���ʣ��������û���򷵻���Ϸ��������
			if (m_iLife <= 0)
			{
				m_pGameScene->RunScene(SCENE_GAMEOVER);
				return;
			}

			//��������
			InitData();
		}
	}
	else if (m_enGameState == GAMESTATE_PASS)
	{
		if (m_iAddScoreCount < GAMEPASS_ADDCOUNT)
		{
			++m_iAddScoreCount;
			m_iScore += GAMEPASS_ADDSCORE;
			m_pGameScene->UpdateScore(m_iScore);
			return;
		}
		else
		{
			//�����ٶȺ͵ȼ�
			if (++m_iSpeed >= 10)
			{
				m_iSpeed = 0;
				if (++m_iLevel >= 10)
				{
					m_iLevel = 0;
				}
			}

			//������ʾ
			m_pGameScene->UpdateLevel(m_iLevel);
			m_pGameScene->UpdateSpeed(m_iSpeed);

			//��������
			InitData();
		}
	}

	m_pGameScene->UpdateBricks();
}


//��ȡ��ǰBrick״̬
bool CRacingGame::GetBrickState(int iRowIndex, int iColIndex)
{
	//����λ��
	int iCarColIdx = m_iCarPos * 3 + 2;
	int iCarRowIdx = ROW_NUM - 2;

	if (m_enGameState == GAMESTATE_OVER)
	{
		//��ը
		if (iRowIndex - iColIndex == iCarRowIdx - iCarColIdx && iRowIndex >= iCarRowIdx - 2 && iRowIndex <= iCarRowIdx + 1)
		{
			return m_bShowBoom;
		}

		if (iRowIndex + iColIndex == iCarColIdx + iCarRowIdx - 1 && iRowIndex >= iCarRowIdx - 2 && iRowIndex <= iCarRowIdx + 1)
		{
			return m_bShowBoom;
		}

		if ((iRowIndex == iCarRowIdx		&& iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx		&& iColIndex == iCarColIdx - 2)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx - 2)
			|| (iRowIndex == iCarRowIdx - 2 && iColIndex == iCarColIdx)
			|| (iRowIndex == iCarRowIdx - 2 && iColIndex == iCarColIdx - 1)
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx)
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx - 1)
			)
		{
			return false;
		}
	}
	else
	{
		//�������Լ�
		if ((iRowIndex == iCarRowIdx		&& iColIndex == iCarColIdx)
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx)
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx - 1)
			|| (iRowIndex == iCarRowIdx + 1 && iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx - 1)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx)
			|| (iRowIndex == iCarRowIdx - 1 && iColIndex == iCarColIdx + 1)
			|| (iRowIndex == iCarRowIdx - 2 && iColIndex == iCarColIdx)
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
void CRacingGame::OnLeftBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING || m_iCarPos == 0)
	{
		return;
	}

	--m_iCarPos;

	//���Ŀ�공���Ƿ�ռ��
	if (m_arrCurBrick[ROW_NUM - 2][m_iCarPos * 3 + 2] == 1)
	{
		m_enGameState = GAMESTATE_OVER;
	}

	m_pGameScene->UpdateBricks(ROW_NUM - 4, m_iCarPos * 3 + 1, ROW_NUM, (m_iCarPos + 1) * 3 + 4);
}


//��
void CRacingGame::OnRightBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING || m_iCarPos == ROAD_COUNT - 1)
	{
		return;
	}

	++m_iCarPos;

	//���Ŀ�공���Ƿ�ռ��
	if (m_arrCurBrick[ROW_NUM - 2][m_iCarPos * 3 + 2] == 1)
	{
		m_enGameState = GAMESTATE_OVER;
	}

	m_pGameScene->UpdateBricks(ROW_NUM - 4, (m_iCarPos - 1) * 3 + 1, ROW_NUM, m_iCarPos * 3 + 4);
}


//��
void CRacingGame::OnUpBtnPressed()
{

}


//��
void CRacingGame::OnDownPressed()
{

}


//Fire
void CRacingGame::OnFireBtnPressed()
{
	//����
	m_bImproveSpeed = true;
}


void CRacingGame::OnFireBtnReleased()
{
	m_bImproveSpeed = false;
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
		++m_iPassCarCount;
		m_iScore += 100;
		m_pGameScene->UpdateScore(m_iScore);

		if (m_iPassCarCount >= GAMEPASS_CARCOUNT)
		{
			m_enGameState = GAMESTATE_PASS;
			m_iAddScoreCount = 0;
		}
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

	int iCount = Random(1, CAR_MAXNUM);
	for (int i = 0; i < iCount; ++i)
	{
		int iRoadIdx = Random(0, ROAD_COUNT);
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
	m_iCarPos = Random(0, ROAD_COUNT);
}


//��ȡ�ȴ�ʱ��
int CRacingGame::GetWaitInterval()
{
	if (m_enGameState == GAMESTATE_PASS)
	{
		return DEFAULT_INTERVAL;
	}

	//��Ϸ����ʱ���Ž�������
	if (m_enGameState == GAMESTATE_OVER)
	{
		return 40;
	}

	//����
	if (m_bImproveSpeed)
	{
		return 30;
	}
	else
	{
		//�����ٶ�
		return DEFAULT_INTERVAL - 13 * m_iSpeed;
	}
}


//������
bool CRacingGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex == 0 && iColIndex < m_iLife)
	{
		return true;
	}

	return false;
}
