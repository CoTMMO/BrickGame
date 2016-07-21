#include "MatchGame.h"

const bool BRICK_STATE[][2][2] =
{
	{
		{ false, false },
		{ true, false, },
	},
	{
		{ true, false },
		{ true, false, },
	},
	{
		{ true, false },
		{ true, true, },
	},
	{
		{ true, true },
		{ true, true, },
	},
};

CMatchGame::CMatchGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{
}


CMatchGame::~CMatchGame()
{
}


//��ʼ��
void CMatchGame::Init()
{
	//��ȡ��ѡ����Ϸ�������õ��ٶȺ͵ȼ�
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);

	//Ĭ��������Ϊ4
	m_iLife = GET_INTVALUE("LIFE", 4);

	//��ʼ����ǰ����
	m_iScore = 0;

	//���½��棬�������ȼ�������
	m_pGameScene->UpdateScore(m_iScore, false);
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSmallBricks();

	//��ʼ��ƥ��ɹ�����
	m_iMatchSuccCount = 0;

	InitData();
}


//����
void CMatchGame::Play(float dt)
{
	if (m_enGameState ==  GAMESTATE_PASS)
	{
		//ʱ�����
		m_fWaitTime += dt;
		if (m_fWaitTime < GAMEPASS_REFRESH_INTERVAL)
		{
			return;
		}
		m_fWaitTime = 0;

		if (m_iAddScoreCount < GAMEPASS_ADDCOUNT)
		{
			++m_iAddScoreCount;
			m_iScore += MACTHSUCC_ADDSCORE;
			m_pGameScene->UpdateScore(m_iScore);
			return;
		}
		else
		{
			//�����ٶȺ͵ȼ�
			if (++m_iSpeed > 10)
			{
				m_iSpeed = 0;
				if (++m_iLevel > 10)
				{
					m_iLevel = 0;
				}
			}

			//������ʾ
			m_pGameScene->UpdateLevel(m_iLevel);
			m_pGameScene->UpdateSpeed(m_iSpeed);

			//����ƥ�����
			m_iMatchSuccCount = 0;

			//��������
			InitData();
		}
	}

	if (m_enGameState == GAMESTATE_RUNNING)
	{
		//�����ƶ�
		bool bUpdateFlag = DestBricksMove(dt);
		bUpdateFlag = MyBricksMove(dt) || bUpdateFlag;
		if (!bUpdateFlag)
		{
			return;
		}
	}

	if (m_enGameState == GAMESTATE_OVER)
	{
		//ʱ�����
		m_fWaitTime += dt;
		if (m_fWaitTime < BOOM_REFRESH_INTERVAL)
		{
			return;
		}
		m_fWaitTime = 0;

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

	m_pGameScene->UpdateBricks();
}


//��ȡ��ǰBrick״̬
bool CMatchGame::GetBrickState(int iRowIndex, int iColIndex)
{
	if (m_enGameState == GAMESTATE_OVER)
	{
		int iBoomStartRowIdx = (m_iMyRowIdx > ROW_NUM - 4 ? ROW_NUM - 4 : m_iMyRowIdx);
		if (iRowIndex >= iBoomStartRowIdx && iRowIndex < iBoomStartRowIdx + 4)
		{
			int iIndex = iColIndex / 5;
			for (int i = 0; i < BRICK_MATCH_NUM; ++i)
			{
				if ((m_arrBoomIndex[i] == iColIndex / 5) && (iColIndex % 5 < 4))
				{
					return m_bShowBoom && BOOM_STATE[iRowIndex - iBoomStartRowIdx][iColIndex % 5];
				}
			}
		}
	}

	do 
	{
		bool bMyFlag = false;
		int iAcutalRowIdx = 0;

		if (iRowIndex < m_iDestRowIdx + 2 && iRowIndex >= m_iDestRowIdx)
		{
			iAcutalRowIdx = iRowIndex - m_iDestRowIdx;
		}
		else if (iRowIndex < m_iMyRowIdx + 2 && iRowIndex >= m_iMyRowIdx)
		{
			iAcutalRowIdx = iRowIndex - m_iMyRowIdx;
			bMyFlag = true;
		}
		else
		{
			break;
		}

		int iIndex = iColIndex / 5;
		if (iColIndex % 5 < 2)
		{
			int iType = bMyFlag ? m_arrMyBrick[iIndex] : m_arrDestBrick[iIndex];
			int iActualColIdx = iColIndex - iIndex * 5;
			return BRICK_STATE[iType][iAcutalRowIdx][iActualColIdx];
		}
	} while (0);

	return false;
}


//��ȡС���������еķ���״̬
bool CMatchGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex == 0 && iColIndex < m_iLife)
	{
		return true;
	}

	return false;
}


//��ȡ��Ϸ����
SCENE_INDEX CMatchGame::GetSceneType()
{
	return SCENE_MATCH;
}


//����
void CMatchGame::OnLeftBtnPressed()
{
	ChangeType(DIR_LEFT, true);
}


//���ͷ�
void CMatchGame::OnLeftBtnReleased()
{
	ChangeType(DIR_LEFT, false);
}


//�Ұ���
void CMatchGame::OnRightBtnPressed()
{
	ChangeType(DIR_RIGHT, true);
}


//���ͷ�
void CMatchGame::OnRightBtnReleased()
{
	ChangeType(DIR_RIGHT, false);
}


//�ϰ���
void CMatchGame::OnUpBtnPressed()
{
	ChangeType(DIR_UP, true);
}


//���ͷ�
void CMatchGame::OnUpBtnReleased()
{
	ChangeType(DIR_UP, false);
}


//�°���
void CMatchGame::OnDownPressed()
{
	ChangeType(DIR_DOWN, true);
}


//���ͷ�
void CMatchGame::OnDownReleased()
{
	ChangeType(DIR_DOWN, false);
}


//Fire����
void CMatchGame::OnFireBtnPressed()
{
	m_bConfirmMatch = true;
}


//��ʼ������
void CMatchGame::InitData()
{
	//��ʼ��4������
	int iTypeCount = sizeof(BRICK_STATE) / sizeof(bool) / 4;
	for (int i = 0; i < BRICK_MATCH_NUM; ++i)
	{
		m_arrDestBrick[i] = Random(0, iTypeCount);
		m_arrMyBrick[i] = Random(0, iTypeCount);

		//��ըλ������
		m_arrBoomIndex[i] = -1;
	}

	//Ŀ�귽��������
	m_iDestRowIdx = m_iLevel;

	//�ҷ�����������
	m_iMyRowIdx = ROW_NUM - 2;

	//ʱ�����
	m_fDestBrickMoveTime = 0;
	m_fWaitTime = 0;

	//��Ϸ״̬
	m_enGameState = GAMESTATE_RUNNING;

	//��ը��ʾ����
	m_iShowBoomCount = 0;

	//�������Ӵ�������
	m_iAddScoreCount = 0;

	//��ը��ʾ״̬
	m_bShowBoom = true;

	//�Ƿ����
	m_bConfirmMatch = false;

	//���½���
	m_pGameScene->UpdateBricks();
}


//Ŀ�귽���ƶ�
bool CMatchGame::DestBricksMove( float dt )
{
	m_fDestBrickMoveTime += dt;
	if (m_fDestBrickMoveTime < BRICK_MOVE_INTERVAL - 70 * m_iSpeed)
	{
		return false;
	}

	//����
	m_fDestBrickMoveTime = 0;

	//Ŀ�귽���½�һ��
	if (++m_iDestRowIdx <= m_iMyRowIdx - 2)
	{
		return true;
	}

	//������Ϸ״̬
	UpdateGameState();

	return true;
}


//���ķ�������
void CMatchGame::ChangeType(DIRECTION enDirection, bool bPressed)
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	//��ť��Ч
	if (bPressed)
	{
		PLAY_EFFECT(EFFECT_CHANGE2);
		UpdateMyBricks(enDirection);
	}
}



void CMatchGame::UpdateMyBricks(DIRECTION enDirection)
{
	const int arrRelation[DIR_MAX] = { 2, -1, 0, 1 };
	int iTypeCount = sizeof(BRICK_STATE) / sizeof(bool) / 4;

	int iBrickIndex = arrRelation[enDirection];
	if (iBrickIndex == -1)
	{
		return;
	}

	if (++m_arrMyBrick[iBrickIndex] > iTypeCount - 1)
	{
		m_arrMyBrick[iBrickIndex] = 0;
	}

	m_pGameScene->UpdateBricks(m_iMyRowIdx, 0, m_iMyRowIdx + 2, COLUMN_NUM);
}


//�ҷ������ƶ�
bool CMatchGame::MyBricksMove(float dt)
{
	if (!m_bConfirmMatch)
	{
		return false;
	}

	m_fWaitTime += dt;
	if (m_fWaitTime < 30)
	{
		return false;
	}

	//����
	m_fWaitTime = 0;

	if (--m_iMyRowIdx >= m_iDestRowIdx + 2)
	{
		return true;
	}

	//�Ѿ���Ŀ�귽���غϣ�������Ϸ״̬
	UpdateGameState();
	
	return true;
}


void CMatchGame::UpdateGameState()
{
	//����Ƿ�ƥ��
	int iBoomIndex = 0;
	for (int i = 0; i < BRICK_MATCH_NUM; ++i)
	{
		if (m_arrMyBrick[i] != m_arrDestBrick[i])
		{
			m_enGameState = GAMESTATE_OVER;
			PLAY_EFFECT(EFFECT_BOOM);
			m_arrBoomIndex[iBoomIndex++] = i;
		}
	}

	//�����ƥ�䣬��ӷ֣�����Ƿ�ͨ����ǰ�ȼ�
	if (iBoomIndex == 0)
	{
		m_iScore += MACTHSUCC_ADDSCORE;
		m_pGameScene->UpdateScore(m_iScore);

		if (++m_iMatchSuccCount >= GAMEPASS_MATCHCOUNT)
		{
			m_enGameState = GAMESTATE_PASS;
		}
		else
		{
			//���²���Ŀ�귽����ҷ�����
			InitData();
		}
	}
}


void CMatchGame::SaveGameData()
{
	
}