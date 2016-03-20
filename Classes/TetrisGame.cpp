#include "TetrisGame.h"

//��������Ͷ�Ӧ״̬
const bool TETRIS_SHAPE[][4][4] = 
{
	{
		{false, true, true, false},		//0110
		{ true, true, false, false},	//1100
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ true, false, false, false },	//1000
		{ true, true, false, false },	//1100
		{ false, true, false, false },	//0100
		{ false, false, false, false },
	},

	{
		{ true, true, false, false },	//1100
		{ false, true, true, false },	//0110
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ false, true, false, false },	//0100
		{ true, true, false, false },	//1100
		{ true, false, false, false },	//1000
		{ false, false, false, false },
	},

	{
		{false, true, false, false},	//0100
		{true, true, true, false},		//1110
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ true, false, false, false },	//1000
		{ true, true, false, false },	//1100
		{ true, false, false, false },	//1000
		{ false, false, false, false },
	},
	{
		{ true, true, true, false },	//1110
		{ false, true, false, false },	//0100
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ false, true, false, false },	//0100
		{ true, true, false, false },	//1100
		{ false, true, false, false },	//0100
		{ false, false, false, false },
	},

	{
		{ true, true, false, false },	//1100
		{ true, false, false, false },	//1000
		{ true, false, false, false },	//1000
		{ false, false, false, false },
	},
	{
		{ true, true, true, false },	//1110
		{ false, false, true, false },	//0010
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ false, true, false, false },	//0100
		{ false, true, false, false },	//0100
		{ true, true, false, false },	//1100
		{ false, false, false, false },
	},
	{
		{ true, false, false, false },	//1000
		{ true, true, true, false },	//1110
		{ false, false, false, false },
		{ false, false, false, false },
	},

	{
		{ true, true, false, false },	//1100
		{ false, true, false, false },	//0100
		{ false, true, false, false },	//0100
		{ false, false, false, false },
	},
	{
		{ false, false, true, false },	//0010
		{ true, true, true, false },	//1110
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ true, false, false, false },	//1000
		{ true, false, false, false },	//1000
		{ true, true, false, false },	//1100
		{ false, false, false, false },
	},
	{
		{ true, true, true, false },	//1110
		{ true, false, false, false },	//1000
		{ false, false, false, false },
		{ false, false, false, false },
	},

	{
		{ true, true, false, false },	//1100
		{ true, true, false, false },	//1100
		{ false, false, false, false },
		{ false, false, false, false },
	},

	{
		{ true, false, false, false },	//1000
		{ true, false, false, false },	//1000
		{ true, false, false, false },	//1000
		{ true, false, false, false },	//1000
	},
	{
		{ true, true, true, true },		//1111
		{ false, false, false, false },
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{true, false, false, false},	//1000
		{ true, false, false, false },	//1000
		{ false, false, false, false },	
		{ false, false, false, false },
	},
	{
		{ true, false, false, false },	//1000
		{ true, false, false, false },	//1000
		{ false, false, false, false },
		{ false, false, false, false },
	},
	{
		{ true, false, false, true },	//1001
		{ false, true, true, false },	//0110
		{ false, true, true, false },	//0110
		{ true, false, false, true },	//1001
	},
};

//ƫ�Ƶ���
const int TETRIS_COLOFFSET[] = { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0 };

//���򳤶�
const int TETRIS_ROWCOUNT[] = { 2, 3, 2, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3, 2, 3, 2, 2, 4, 1, 2, 2, 4 };

//���򳤶�
const int TETRIS_COLCOUNT[] = { 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1, 4, 1, 1, 4 };

//ͬ���Ϳ�ʼ����
const int TETRIS_TYPE_START_IDX[] = { 0, 2, 4, 8, 12, 16, 17, 19, 20, 21 };


CTetrisGame::CTetrisGame(CGameScene* pGameScene, bool bMode) : CSceneBase(pGameScene), m_bExtraMode(bMode)
{
}


CTetrisGame::~CTetrisGame()
{
}


void CTetrisGame::Init()
{
	//��ȡ��ѡ����Ϸ�������õ��ٶȺ͵ȼ�
	m_iSpeed = GET_INTVALUE("SPEED", 0);
	m_iLevel = GET_INTVALUE("LEVEL", 0);

	//��ʼ����ǰ����
	m_iScore = 0;

	//���½��棬�������ȼ�������
	m_pGameScene->UpdateScore(m_iScore, false);
	m_pGameScene->UpdateLevel(m_iLevel);

	InitData();
}


void CTetrisGame::Play(float dt)
{
	if (m_enGameState == GAMESTATE_RUNNING)
	{
		//��˸״̬����
		bool bUpdateFlag = UpdateSelfState(dt);

		//�����ƶ�
		bUpdateFlag = BrickMove(dt) || bUpdateFlag;
		
		if (!bUpdateFlag)
		{
			return;
		}
	}

	if (m_enGameState == GAMESTATE_OVER)
	{
		m_pGameScene->RunScene(SCENE_GAMEOVER);
		return;
	}
	
	m_pGameScene->UpdateBricks();
}


bool CTetrisGame::GetBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex >= m_stCurPos.m_iRowIdx && iRowIndex < m_stCurPos.m_iRowIdx + 4
		&& iColIndex >= m_stCurPos.m_iColIdx && iColIndex < m_stCurPos.m_iColIdx + 4)
	{
		int iActRowIdx = iRowIndex - m_stCurPos.m_iRowIdx;
		int iActColIdx = iColIndex - m_stCurPos.m_iColIdx;

		//��λ���Ƿ���������ռ��
		if (m_arrBrick[iRowIndex][iColIndex])
		{
			return true;
		}

		//�����������˸Ч��������Ҫ��������״̬�����Ƿ���ʾ
		bool bState = TETRIS_SHAPE[m_iCurShape][iActRowIdx][iActColIdx];
		if (m_bFlashFlag)
		{
			bState = m_bSelfShowFlag && bState;
		}

		return bState;
	}
	else
	{
		return m_arrBrick[iRowIndex][iColIndex];
	}
}


bool CTetrisGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	return TETRIS_SHAPE[m_iNextShape][iRowIndex][iColIndex];
}


SCENE_INDEX CTetrisGame::GetSceneType()
{
	return SCENE_TETRIS;
}


void CTetrisGame::OnLeftBtnPressed()
{
	//��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	//�ƶ�һ��
	m_fBtnCheckTime = BTN_CHECK_INTERVAL;

	//���������ƶ�״̬
	m_bLeftBtnPressed = true;
}


void CTetrisGame::OnLeftBtnReleased()
{
	m_bLeftBtnPressed = false;
}


void CTetrisGame::OnRightBtnPressed()
{
	//��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	//�ƶ�һ��
	m_fBtnCheckTime = BTN_CHECK_INTERVAL;

	//���������ƶ�״̬
	m_bRightBtnPressed = true;
}


void CTetrisGame::OnRightBtnReleased()
{
	m_bRightBtnPressed = false;
}

void CTetrisGame::OnDownPressed()
{
	PLAY_EFFECT(EFFECT_CHANGE2);
	m_bFastMoveDown = true;
}


void CTetrisGame::OnDownReleased()
{
	m_bFastMoveDown = false;
}


void CTetrisGame::OnFireBtnPressed()
{
	PLAY_EFFECT(EFFECT_CHANGE2);

	//�������ⷽ��
	if (m_iCurShape == 19 || m_iCurShape == 20)
	{
		bool bAddFlag = (m_iCurShape == 19);

		//��ȡ��ǰλ�ö�Ӧ�а����ķ�������
		int iRowIdx = GetNextAddOrSubRowIdx(m_stCurPos.m_iColIdx);
		
		//Ҫ�����ķ���λ��
		iRowIdx += (bAddFlag ? -1 : 0);
		if (iRowIdx < m_stCurPos.m_iRowIdx + TETRIS_ROWCOUNT[m_iCurShape] || iRowIdx > ROW_NUM - 1)
		{
			return;
		}
		int iColIdx = m_stCurPos.m_iColIdx;

		//����״̬
		m_arrBrick[iRowIdx][iColIdx] = bAddFlag;
		m_pGameScene->UpdateBrick(iRowIdx, iColIdx, false, bAddFlag);

		//����Ǽӷ��飬��Ҫ����Ƿ����������
		if (bAddFlag)
		{
			DeleteLine(false);
		}

		return;
	}


	//��鵱ǰ��״��������
	int iAllTypeCount = sizeof(TETRIS_TYPE_START_IDX) / sizeof(int);
	int iStartIdx = TETRIS_TYPE_START_IDX[iAllTypeCount - 1];
	int iEndIdx = GetShapeCount();
	for (int i = 0; i < iAllTypeCount; ++i)
	{
		if (m_iCurShape < TETRIS_TYPE_START_IDX[i])
		{
			iStartIdx = TETRIS_TYPE_START_IDX[i - 1];
			iEndIdx = TETRIS_TYPE_START_IDX[i];
			break;
		}
	}
	
	int iShape = m_iCurShape;
	if (++iShape >= iEndIdx)
	{
		iShape = iStartIdx;
	}

	//����Ƿ���Ա任
	if (CheckBrickPos(iShape, m_stCurPos.m_iRowIdx, m_stCurPos.m_iColIdx))
	{
		//���µ�ǰ��״
		m_iCurShape = iShape;

		//λ������
		if (m_stCurPos.m_iColIdx + TETRIS_COLCOUNT[m_iCurShape] > COLUMN_NUM)
		{
			m_stCurPos.m_iColIdx = COLUMN_NUM - TETRIS_COLCOUNT[m_iCurShape];
		}

		//������ʾ
		m_pGameScene->UpdateBricks(m_stCurPos.m_iRowIdx, m_stCurPos.m_iColIdx,
			m_stCurPos.m_iRowIdx + 4, m_stCurPos.m_iColIdx + 4);
	}
}


void CTetrisGame::InitData()
{
	//��ʼ�����з���״̬
	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrBrick[i][j] = false;
		}
	}

	//�����һ����������
	m_iNextShape = Random(0, GetShapeCount());

	//�����µķ���
	RandNewShape();

	//��Ϸ״̬
	m_enGameState = GAMESTATE_RUNNING;

	//ʱ�����
	m_fMoveDownTime = 0;
	m_fBtnCheckTime = 0;
	m_fSelfFlashTime = 0;

	//���
	m_bLeftBtnPressed = false;
	m_bRightBtnPressed = false;
	m_bFastMoveDown = false;
	m_bSelfShowFlag = true;

	m_pGameScene->UpdateBricks();
}


void CTetrisGame::RandNewShape()
{
	//���õ�ǰ�������ͣ����������һ����������
	int iShape = m_iNextShape;
	m_iNextShape = Random(0, GetShapeCount());

	//����С����������ʾ
	m_pGameScene->UpdateSmallBricks();

	//���λ���Ƿ���Ч
	int iColIdx = COLUMN_NUM / 2 - 2 + TETRIS_COLOFFSET[iShape];
	if (!CheckBrickPos(iShape, 0, iColIdx))
	{
		m_enGameState = GAMESTATE_OVER;
	}
	else
	{
		m_iCurShape = iShape;
		m_stCurPos.m_iRowIdx = 0;
		m_stCurPos.m_iColIdx = iColIdx;
	}

	//���ⷽ����˸��ʾ
	m_bFlashFlag = (m_iCurShape >= 19);
}


bool CTetrisGame::BrickMove(float dt)
{
	//��һ��λ��
	int iNextRowIdx = m_stCurPos.m_iRowIdx;
	int iNextColIdx = m_stCurPos.m_iColIdx;

	//��ť״̬���
	m_fBtnCheckTime += dt;
	if (m_fBtnCheckTime >= BTN_CHECK_INTERVAL)
	{
		m_fBtnCheckTime = 0;

		if (m_bLeftBtnPressed)
		{
			if (--iNextColIdx < 0)
			{
				iNextColIdx = 0;
			}
		}
		else if (m_bRightBtnPressed)
		{
			int iMaxColIdx = COLUMN_NUM - TETRIS_COLCOUNT[m_iCurShape];
			if (++iNextColIdx > iMaxColIdx)
			{
				iNextColIdx = iMaxColIdx;
			}
		}
	}

	//����
	m_fMoveDownTime += dt;
	if (m_fMoveDownTime >= (m_bFastMoveDown ? 30 : (BRICK_MOVE_INTERVAL - 40 * m_iSpeed)))
	{
		m_fMoveDownTime = 0;
		++iNextRowIdx;
	}

	//û�з���λ�ñ����������
	if (iNextRowIdx == m_stCurPos.m_iRowIdx && iNextColIdx == m_stCurPos.m_iColIdx)
	{
		return false;
	}

	//�����һ��λ���Ƿ���Ч
	bool bNextPosValidFlag = CheckBrickPos(m_iCurShape, iNextRowIdx, iNextColIdx);
	if (!bNextPosValidFlag)
	{
		if (m_stCurPos.m_iRowIdx == 0 && iNextRowIdx == 1)
		{
			//���û���ƶ���������ʱ���޷��������ƶ�����Ϸ����
			m_enGameState = GAMESTATE_OVER;
			return true;
		}

		//�ָ���λ�ã��ٴμ��λ���Ƿ���Ч
		iNextColIdx = m_stCurPos.m_iColIdx;
		if (!CheckBrickPos(m_iCurShape, iNextRowIdx, iNextColIdx))
		{
			//��������ⷽ��
			if (m_iCurShape < 19)
			{
				//���޷��������ƶ����ѵ������һ�У����浱ǰ����
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						if (TETRIS_SHAPE[m_iCurShape][i][j])
						{
							m_arrBrick[m_stCurPos.m_iRowIdx + i][m_stCurPos.m_iColIdx + j] = true;
						}
					}
				}
			}
			else
			{
				//����Ǳ�ը���飬�������µ�ָ������
				if (m_iCurShape == 21)
				{
					int iStartRowIdx = m_stCurPos.m_iRowIdx;
					int iEndRowIdx = iStartRowIdx + TETRIS_ROWCOUNT[m_iCurShape] + BOOM_SHAPE_DELETE_LINE_COUNT + m_iSpeed / 4;
					iEndRowIdx = (iEndRowIdx > ROW_NUM ? ROW_NUM : iEndRowIdx);
					for (int i = iStartRowIdx; i < iEndRowIdx; ++i)
					{
						for (int j = m_stCurPos.m_iColIdx; j < m_stCurPos.m_iColIdx + TETRIS_COLCOUNT[m_iCurShape]; ++j)
						{
							m_arrBrick[i][j] = false;
							m_pGameScene->UpdateBrick(i, j, false, false);
						}
					}
					
					//��Ч
					PLAY_EFFECT(EFFECT_BOOM);
				}
			}

			//���ü���������
			m_bFastMoveDown = false;

			//�������
			DeleteLine(true);

			//�����µķ���
			RandNewShape();
			return true;
		}
	}

	//����λ��
	m_stCurPos.m_iRowIdx = iNextRowIdx;
	m_stCurPos.m_iColIdx = iNextColIdx;

	return true;
}


bool CTetrisGame::CheckBrickPos(int iShapeIdx, int iSrcRowIdx, int iSrcColIdx)
{
	if (iSrcRowIdx > ROW_NUM - TETRIS_ROWCOUNT[iShapeIdx])
	{
		return false;
	}

	if (iSrcColIdx > ROW_NUM - TETRIS_COLCOUNT[iShapeIdx])
	{
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		int iRowIdx = iSrcRowIdx + i;
		if (iRowIdx >= ROW_NUM)
		{
			continue;
		}

		for (int j = 0; j < 4; ++j)
		{
			int iColIdx = iSrcColIdx + j;
			if (iColIdx >= COLUMN_NUM)
			{
				continue;
			}

			if (m_arrBrick[iRowIdx][iColIdx] && TETRIS_SHAPE[iShapeIdx][i][j])
			{
				return false;
			}
		}
	}

	return true;
}


void CTetrisGame::DeleteLine(bool bEnd)
{
	int iDelCount = 0;

	if (!bEnd)
	{
		//������һ��
		int iRowIdx = GetNextAddOrSubRowIdx(m_stCurPos.m_iColIdx);
		for (int i = 0; i < COLUMN_NUM; ++i)
		{
			if (!m_arrBrick[iRowIdx][i])
			{
				return;
			}
		}

		DeleteSingleLine(iRowIdx);
		iDelCount = 1;
	}
	else
	{
		for (int i = m_stCurPos.m_iRowIdx; i < m_stCurPos.m_iRowIdx + TETRIS_ROWCOUNT[m_iCurShape]; ++i)
		{
			bool bCanDeleteFlag = true;
			for (int j = 0; j < COLUMN_NUM; ++j)
			{
				if (!m_arrBrick[i][j])
				{
					bCanDeleteFlag = false;
					break;
				}
			}

			//��������
			if (bCanDeleteFlag)
			{
				DeleteSingleLine(i);
				++iDelCount;
			}
		}

		if (iDelCount == 0)
		{
			return;
		}
	}

	//�ӷ�
	m_iScore += iDelCount * iDelCount * DELETE_LINE_ADD_SCORE;
	m_pGameScene->UpdateScore(m_iScore, false);
	PLAY_EFFECT(EFFECT_DELETE);
}


void CTetrisGame::DeleteSingleLine(int iRowIdx)
{
	for (int i = iRowIdx; i > 0; --i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrBrick[i][j] = m_arrBrick[i - 1][j];
		}
	}

	for (int j = 0; j < COLUMN_NUM; ++j)
	{
		m_arrBrick[0][j] = false;
	}
}


int CTetrisGame::GetShapeCount()
{
	int iCount = sizeof(TETRIS_SHAPE) / sizeof(bool) / 16;
	return (m_bExtraMode ? iCount : iCount - 3);
}


int CTetrisGame::GetNextAddOrSubRowIdx(int iColIdx)
{
	int iIndex = ROW_NUM;
	for (int i = 0; i < ROW_NUM; ++i)
	{
		if (m_arrBrick[i][iColIdx])
		{
			iIndex = i;
			break;
		}
	}

	return iIndex;
}


bool CTetrisGame::UpdateSelfState(float dt)
{
	if (m_iCurShape < 19)
	{
		return false;
	}

	m_fSelfFlashTime += dt;
	if (m_fSelfFlashTime < SELF_FLASH_INTERVAL)
	{
		return false;
	}

	//����
	m_fSelfFlashTime = 0;

	//����״̬
	m_bSelfShowFlag = !m_bSelfShowFlag;

	return true;
}

