#include "AddBrickGame.h"

const int PASS_SCORE[SPEED_MAX + 1] = {2000, 4000, 6000, 8000, 10000, 13000, 16000, 20000, 24000, 28000, 35000};

CAddBrickGame::CAddBrickGame(CGameScene* pScene, bool bSpecialMode/* = false*/) : CSceneBase(pScene), 
									m_iSpeed(0), m_iLevel(0), m_iScore(0), m_bSpecialMode(bSpecialMode)
{
}


CAddBrickGame::~CAddBrickGame()
{
}


void CAddBrickGame::Init()
{
	//��ȡ��ѡ����Ϸ�������õ��ٶȺ͵ȼ�
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);
	m_iLife = GET_INTVALUE("LIFE", 4);

	//��ʼ����ǰ����
	m_iScore = 0;

	//���µȼ����ٶ�
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSpeed(m_iSpeed);
	m_pGameScene->UpdateSmallBricks();
	m_pGameScene->UpdateScore(m_iScore, false);

	//��ʼ������
	initData();
}


void CAddBrickGame::Play(float dt)
{
	if (m_enGameState == GAMESTATE_OVER)
	{
		//ʱ�����
		m_fWaitTime += dt;
		if (m_fWaitTime < GAMEOVER_WAIT_INTERVAL)
		{
			return;
		}
		m_fWaitTime = 0;

		//����ʣ������
		if (--m_iLife <= 0)
		{
			m_pGameScene->RunScene(SCENE_GAMEOVER);
			return;
		}

		//������ʾ����
		m_pGameScene->UpdateSmallBricks();

		//��������
		initData();
	}

	if (m_enGameState == GAMESTATE_PASS)
	{
		//ʱ�����
		m_fWaitTime += dt;
		if (m_fWaitTime < GAMEPASS_WAIT_INTERVAL)
		{
			return;
		}
		m_fWaitTime = 0;

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

		//��������
		initData();
	}

	if (m_enGameState == GAMESTATE_RUNNING)
	{
		selfMove(dt);

		bool bRefreshFlag = false;
		if (bulletsMove(dt))
		{
			bRefreshFlag = true;
		}

		if (fireBricks(dt))
		{
			bRefreshFlag = true;
		}

		if (bricksMoveDown(dt))
		{
			bRefreshFlag = true;
		}

		if (!bRefreshFlag)
		{
			return;
		}
	}

	//������Ϸ״̬
	updateGameState();


	m_pGameScene->UpdateBricks();
}


bool CAddBrickGame::GetBrickState(int iRowIndex, int iColIndex)
{
	//�ҷ���������
	int nSelfRowIdx = m_stSelfPos.m_iRowIdx;
	int nSelfColIdx = m_stSelfPos.m_iColIdx;
	if ((iRowIndex == nSelfRowIdx && iColIndex >= nSelfColIdx - 1 && iColIndex <= nSelfColIdx + 1)
		|| (iRowIndex == nSelfRowIdx - 1 && iColIndex == nSelfColIdx))
	{
		return true;
	}

	//�ӵ�
	FOR_EACH_CONTAINER (TLIST_POS, m_lsBullets, itBullet)
	{
		if (itBullet->m_iRowIdx == iRowIndex && itBullet->m_iColIdx == iColIndex)
		{
			return true;
		}
	}

	return m_arrBrick[iRowIndex][iColIndex];
}


bool CAddBrickGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex == 0 && iColIndex < m_iLife)
	{
		return true;
	}

	return false;
}


SCENE_INDEX CAddBrickGame::GetSceneType()
{
	return SCENE_ADDBRICK;
}


void CAddBrickGame::OnLeftBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnPressFlag[VBTN_LEFT] = true;
}


void CAddBrickGame::OnLeftBtnReleased()
{
	m_arrBtnPressFlag[VBTN_LEFT] = false;
}


void CAddBrickGame::OnRightBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnPressFlag[VBTN_RIGHT] = true;
}


void CAddBrickGame::OnRightBtnReleased()
{
	m_arrBtnPressFlag[VBTN_RIGHT] = false;
}


void CAddBrickGame::OnFireBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnPressFlag[VBTN_FIRE] = true;
	fireBricks(FIRE_CHECK_INTERVAL * 0.5f);
}


void CAddBrickGame::OnFireBtnReleased()
{
	m_arrBtnPressFlag[VBTN_FIRE] = false;
}


void CAddBrickGame::initData()
{
	//��ʼ��
	for (int nRowIdx = 0; nRowIdx < ROW_NUM; ++nRowIdx)
	{
		//ȷ��һ�еĿ�λ
		int nEmptyColIdx = Random(0, COLUMN_NUM);
		for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
		{
			if (nEmptyColIdx == nColIdx || nRowIdx >= m_iLevel)
			{
				m_arrBrick[nRowIdx][nColIdx] = false;
			}
			else
			{
				m_arrBrick[nRowIdx][nColIdx] = randState();
			}
		}
	}

	//��ʼ���ҷ�����λ��
	m_stSelfPos.m_iColIdx = COLUMN_NUM / 2;
	m_stSelfPos.m_iRowIdx = ROW_NUM - 1;

	//��ʼ����ť���±��
	for (int nIdx = 0; nIdx < VBTN_MAX; ++nIdx)
	{
		m_arrBtnPressFlag[nIdx] = false;
	}

	//��Ϸ״̬
	m_enGameState = GAMESTATE_RUNNING;

	//ʱ�����
	m_fBulletMoveTime = 0;
	m_fFireBtnTime = 0;
	m_fSelfMoveTime = 0;
	m_fWaitTime = 0;

	//����ӵ�
	m_lsBullets.clear();
}


bool CAddBrickGame::bricksMoveDown(float dt)
{
	m_fWaitTime += dt;
	if (m_fWaitTime < BRICKS_MOVE_INTERVAL - 150 * m_iSpeed)
	{
		return false;
	}

	m_fWaitTime = 0;

	//����һ�з���
	for (int nRowIdx = ROW_NUM - 1; nRowIdx > 0; --nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
		{
			m_arrBrick[nRowIdx][nColIdx] = m_arrBrick[nRowIdx - 1][nColIdx];
			
			//�����һ��λ��������ĳ���ӵ�����λ�ã���ɾ���ӵ������ø�λ��״̬
			int nNextRowIdx = nRowIdx + 1;
			if (nNextRowIdx < ROW_NUM && m_arrBrick[nRowIdx][nColIdx])
			{
				FOR_EACH_CONTAINER(TLIST_POS, m_lsBullets, itBullet)
				{
					if (nNextRowIdx == itBullet->m_iRowIdx && nColIdx == itBullet->m_iColIdx)
					{
						//ɾ������ӵ�
						m_lsBullets.erase(itBullet);
						
						//����״̬���������
						m_arrBrick[nNextRowIdx][nColIdx] = true;
						deleteLine(nNextRowIdx);
						break;
					}
				}
			}
		}
	}

	//���ɵ�һ�з���
	int nRandColIdx = Random(0, COLUMN_NUM);
	for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
	{
		m_arrBrick[0][nColIdx] = (nRandColIdx == nColIdx ? false : randState());
	}

	return true;
}


bool CAddBrickGame::randState()
{
	return Random(1, 20) >= 10;
}


void CAddBrickGame::updateGameState()
{
	//����Լ��������Ƿ��з���
	int nSelfRowIdx = m_stSelfPos.m_iRowIdx;
	int nSelfColIdx = m_stSelfPos.m_iColIdx;
	if (m_arrBrick[nSelfRowIdx - 1][nSelfColIdx]
		|| m_arrBrick[nSelfRowIdx][nSelfColIdx] 
		|| (nSelfColIdx > 0 && m_arrBrick[nSelfRowIdx][nSelfColIdx - 1])
		|| (nSelfColIdx + 1 < COLUMN_NUM && m_arrBrick[nSelfRowIdx][nSelfColIdx + 1]))
	{
		m_enGameState = GAMESTATE_OVER;
		return;
	}

	//����Ƿ��з����е��ﵹ���ڶ���
	for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
	{
		if (m_arrBrick[ROW_NUM - 1][nColIdx])
		{
			m_enGameState = GAMESTATE_OVER;
			return;
		}
	}

	//������
	if (!m_bSpecialMode && m_iScore >= PASS_SCORE[m_iSpeed])
	{
		m_enGameState = GAMESTATE_PASS;
		return;
	}
}


bool CAddBrickGame::fireBricks(float dt)
{
	if (!m_arrBtnPressFlag[VBTN_FIRE])
	{
		m_fFireBtnTime = 0;
		return false;
	}

	m_fFireBtnTime += dt;
	if (m_fFireBtnTime < FIRE_CHECK_INTERVAL - 5 * m_iSpeed)
	{
		return false;
	}

	m_fFireBtnTime = 0;

	//������ö�Ӧ����һ���и����飬������״̬������
	int nBulletRowIdx = m_stSelfPos.m_iRowIdx - 2;
	int nBulletColIdx = m_stSelfPos.m_iColIdx;
	if (m_arrBrick[nBulletRowIdx - 1][nBulletColIdx])
	{
		m_arrBrick[nBulletRowIdx][nBulletColIdx] = true;
		m_pGameScene->UpdateBrick(nBulletRowIdx, nBulletRowIdx, false, true);

		//�������
		deleteLine(nBulletRowIdx);

		return false;
	}

	//����ӵ�
	m_lsBullets.push_back(POSITION(nBulletRowIdx, nBulletColIdx));
	return true;
}


bool CAddBrickGame::selfMove(float dt)
{
	if (!m_arrBtnPressFlag[VBTN_LEFT] && !m_arrBtnPressFlag[VBTN_RIGHT])
	{
		m_fSelfMoveTime = 0;
		return false;
	}

	//ʱ�����
	m_fSelfMoveTime += dt;
	if (m_fSelfMoveTime < MOVE_CHECK_INTERVAL)
	{
		return false;
	}

	m_fSelfMoveTime = 0;

	//��ť���
	if (m_arrBtnPressFlag[VBTN_LEFT] && m_stSelfPos.m_iColIdx > 0)
	{
		if (m_arrBrick[m_stSelfPos.m_iRowIdx - 1][m_stSelfPos.m_iColIdx - 1])
		{
			return false;
		}

		--m_stSelfPos.m_iColIdx;
	}
	else if (m_arrBtnPressFlag[VBTN_RIGHT] && m_stSelfPos.m_iColIdx < COLUMN_NUM - 1)
	{
		if (m_arrBrick[m_stSelfPos.m_iRowIdx][m_stSelfPos.m_iColIdx + 1])
		{
			return false;
		}

		++m_stSelfPos.m_iColIdx;
	}

	//ˢ�µ�������
	m_pGameScene->UpdateBricks(ROW_NUM - 2, 0);

	return true;
}


bool CAddBrickGame::bulletsMove(float dt)
{
	m_fBulletMoveTime += dt;
	if (m_fBulletMoveTime < BULLET_MOVE_INTERVAL - 3 * m_iSpeed)
	{
		return false;
	}

	m_fBulletMoveTime = 0;

	//���������ӵ�
	for (TLIST_POS_ITER itBullet = m_lsBullets.begin(); itBullet != m_lsBullets.end(); )
	{
		int nRowIdx = itBullet->m_iRowIdx;
		int nColIdx = itBullet->m_iColIdx;
		int nNextRowIdx = nRowIdx - 1;

		if (nNextRowIdx == 0 || (nNextRowIdx - 1 >= 0 && m_arrBrick[nNextRowIdx - 1][nColIdx]))
		{
			//����״̬���������
			m_arrBrick[nNextRowIdx][nColIdx] = true;
			deleteLine(nNextRowIdx);

			itBullet = m_lsBullets.erase(itBullet);
		}
		else
		{
			//�ƶ�
			--itBullet->m_iRowIdx;
			++itBullet;
		}
	}

	return true;
}


void CAddBrickGame::deleteLine(int nRowIdx)
{
	for (int nIdx = 0; nIdx < COLUMN_NUM; ++nIdx)
	{
		if (!m_arrBrick[nRowIdx][nIdx])
		{
			return;
		}
	}

	//����֮�����з���
	int nBrickCount = 0;
	for (; nRowIdx < ROW_NUM; ++nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_NUM; ++nColIdx)
		{
			if (m_arrBrick[nRowIdx][nColIdx])
			{
				m_arrBrick[nRowIdx][nColIdx] = false;
				++nBrickCount;
			}
		}
	}

	m_iScore += nBrickCount * 10;
	m_pGameScene->UpdateScore(m_iScore, true);
}

