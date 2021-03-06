#include "stdafx.h"
#include "AddBrickGame.h"

const static POSITION SELF_SHAPE[] = 
{
			 {0, 0},
	{1, -1}, {1, 0}, {1, 1},
};


void CAddBrickGame::Start()
{
	CGameBase::Start();

	// Init self data
	m_stSelfData.bFireFlag = false;
	m_stSelfData.nDir = DIR_MAX;
	m_stSelfData.nColIdx = COLUMN_COUNT / 2;
	m_stSelfData.nFireInterval = 0;
	m_stSelfData.nMoveInterval = 0;
	m_stSelfData.nHitBrickCount = 0;
	__DrawSelf(m_stSelfData.nColIdx);

	// Init bullet data
	m_stBulletData.nMoveInterval = 0;
	m_stBulletData.lsPos.clear();

	// Init bricks data
	__InitBricks();

	// Update immediately
	UpdateBrickState(0, GetBrickState(0), true);
}


void CAddBrickGame::Update(float dt)
{
	bool bUpdateFlag = false;

	switch (m_enGameStage)
	{
	case STAGE_FAIL:
	{
		UpdateBoomAnim(dt, bUpdateFlag);
		DrawBoom();
	}
	break;

	case STAGE_PASS:
	{
		// loop add score util the count is arrived
		AddScoreInPassStage(dt, DELETE_ROW_ADD_SCORE);
		return;
	}
	break;

	case STAGE_NORMAL:
	{
		__UpdateBullets(dt, bUpdateFlag);
		__UpdateBricks(dt, bUpdateFlag);
		__SelfMove(dt, bUpdateFlag);
		__SelfFire(dt, bUpdateFlag);
		if (bUpdateFlag)
		{
			__DrawSelf(m_stSelfData.nColIdx);
		}
	}
	break;

	default:
		return;
		break;
	}

	if (bUpdateFlag)
	{
		UpdateBrickState(0, GetBrickState(0), true);
	}
}


EnGameID CAddBrickGame::GetGameID()
{
	return GAMEID_ADDBRICK;
}


void CAddBrickGame::OnButtonEvent(const SEventContextButton* pButtonEvent)
{
	if (m_enGameStage != STAGE_NORMAL)
	{
		return;
	}

	if (pButtonEvent->nButtonID == BTNID_FIRE)
	{
		m_stSelfData.bFireFlag = pButtonEvent->bPressedFlag;
		bool bUpdateFlag = false;
		
		// Fire
		if (m_stSelfData.bFireFlag)
		{
			m_stSelfData.nFireInterval = CONTROL_FIRE_INTERVAL;
			Update(0);
		}
		
		return;
	}

	if (pButtonEvent->nButtonID >= BTNID_DIRMAX)
	{
		return;
	}

	int nDir = BTNID_2_DIR[pButtonEvent->nButtonID];
	if (nDir == DIR_UP)
	{
		SEventContextButton stContext = { BTNID_FIRE, pButtonEvent->bPressedFlag };
		OnButtonEvent(&stContext);
		return;
	}

	if (nDir != DIR_LEFT && nDir != DIR_RIGHT)
	{
		return;
	}

	if (m_stSelfData.nDir != nDir && pButtonEvent->bPressedFlag)
	{
		m_stSelfData.nDir = nDir;
		m_stSelfData.nMoveInterval = CONTROL_MOVE_INTERVAL;
		Update(0);
		return;
	}

	if (m_stSelfData.nDir == nDir && !pButtonEvent->bPressedFlag)
	{
		m_stSelfData.nDir = DIR_MAX;
		m_stSelfData.nMoveInterval = 0;
		return;
	}
}


void CAddBrickGame::__InitBricks()
{
	m_stBricksData.nMoveInterval = 0;

	int nTotalBricksCount = COLUMN_COUNT * ROW_COUNT;
	for (int nRowIdx = 0; nRowIdx <= m_nLevel; ++nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_COUNT; ++nColIdx)
		{
			UpdateBrickState(GET_BRICKID(0, nColIdx), Random(0, nTotalBricksCount) <= nTotalBricksCount / 2);
		}
	}
}


void CAddBrickGame::__UpdateBricks(float dt, bool& bUpdateFlag)
{
	m_stBricksData.nMoveInterval += dt;
	if (m_stBricksData.nMoveInterval < __GetBricksMoveInterval())
	{
		return;
	}

	m_stBricksData.nMoveInterval = 0;
	bUpdateFlag = true;

	// Move rows
	for (int nRowIdx = ROW_COUNT - 1; nRowIdx > 0; --nRowIdx)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_COUNT; ++nColIdx)
		{
			UpdateBrickState(GET_BRICKID(nRowIdx, nColIdx), GetBrickState(GET_BRICKID(nRowIdx - 1, nColIdx)));
		}
	}

	// Generate new row
	int nTotalBricksCount = COLUMN_COUNT * ROW_COUNT;
	for (int nColIdx = 0; nColIdx < COLUMN_COUNT; ++nColIdx)
	{
		UpdateBrickState(GET_BRICKID(0, nColIdx), Random(0, nTotalBricksCount) <= nTotalBricksCount / 2);
	}

	// Check game over
	if (__CheckGameOver())
	{
		m_enGameStage = STAGE_FAIL;
		POSITION stPos = { SELF_ROW_INDEX, m_stSelfData.nColIdx - 1 };
		GameOverWithBoomAnim(stPos);
		return;
	}
}


void CAddBrickGame::__UpdateBullets(float dt, bool& bUpdateFlag)
{
	m_stBulletData.nMoveInterval += dt;
	if (m_stBulletData.nMoveInterval < __GetBulletMoveInterval())
	{
		return;
	}

	m_stBulletData.nMoveInterval = 0;
	bUpdateFlag = true;

	TList_BulletPos::iterator itBullet = m_stBulletData.lsPos.begin();
	for (; itBullet != m_stBulletData.lsPos.end(); )
	{
		int nExtRowIdx = itBullet->x - 1;
		if (nExtRowIdx >= 0
			&& GetBrickState(GET_BRICKID(nExtRowIdx, itBullet->y)))
		{
			UpdateBrickState(GET_BRICKIDBYPOS(*itBullet), true);
			__DeleteRow(itBullet->x);
			itBullet = m_stBulletData.lsPos.erase(itBullet);
			continue;
		}

		// Hide old
		int nBrickID = GET_BRICKIDBYPOS(*itBullet);
		m_mapUpdateBricks[nBrickID] = false;

		itBullet->x = nExtRowIdx;
		if (itBullet->x == 0
			|| GetBrickState(GET_BRICKID(itBullet->x - 1, itBullet->y)))
		{
			UpdateBrickState(GET_BRICKIDBYPOS(*itBullet), true);
			__DeleteRow(itBullet->x);
			itBullet = m_stBulletData.lsPos.erase(itBullet);
			continue;
		}

		// Show new
		nBrickID = GET_BRICKIDBYPOS(*itBullet);
		m_mapUpdateBricks[nBrickID] = true;

		++itBullet;
	}
}


void CAddBrickGame::__SelfMove(float dt, bool& bUpdateFlag)
{
	if (m_stSelfData.nDir != DIR_LEFT
		&& m_stSelfData.nDir != DIR_RIGHT)
	{
		return;
	}

	m_stSelfData.nMoveInterval += dt;
	if (m_stSelfData.nMoveInterval < CONTROL_MOVE_INTERVAL)
	{
		return;
	}

	m_stSelfData.nMoveInterval = 0;

	int nNextColIdx = m_stSelfData.nColIdx + ((m_stSelfData.nDir == DIR_LEFT) ? -1 : 1);
	if (nNextColIdx < COLUMN_COUNT && nNextColIdx >= 0)
	{
		__DrawSelf(nNextColIdx);
		m_stSelfData.nColIdx = nNextColIdx;
		bUpdateFlag = true;
	}

	// Check game over
	if (__CheckGameOver())
	{
		m_enGameStage = STAGE_FAIL;
		POSITION stPos = { SELF_ROW_INDEX, m_stSelfData.nColIdx - 1 };
		GameOverWithBoomAnim(stPos);
		return;
	}
}


void CAddBrickGame::__SelfFire(float dt, bool& bUpdateFlag)
{
	if (!m_stSelfData.bFireFlag)
	{
		return;
	}

	m_stSelfData.nFireInterval += dt;
	if (m_stSelfData.nFireInterval < CONTROL_FIRE_INTERVAL)
	{
		return;
	}

	m_stSelfData.nFireInterval = 0;
	bUpdateFlag = true;

	// Generate new bullet
	POSITION stPos = { SELF_ROW_INDEX, m_stSelfData.nColIdx };
	m_stBulletData.lsPos.push_back(stPos);
	m_mapUpdateBricks[GET_BRICKIDBYPOS(stPos)] = true;
}


void CAddBrickGame::__DrawSelf(int nNewColIdx)
{
	// Hide old
	for (int nIndex = 0; nIndex < _countof(SELF_SHAPE); ++nIndex)
	{
		const POSITION& stOffset = SELF_SHAPE[nIndex];
		int nColIdx = m_stSelfData.nColIdx + stOffset.y;
		if (nColIdx < 0 || nColIdx >= COLUMN_COUNT)
		{
			continue;
		}

		int nBrickID = GET_BRICKID(SELF_ROW_INDEX + stOffset.x, nColIdx);
		m_mapUpdateBricks[nBrickID] = false;
	}

	// Draw new
	for (int nIndex = 0; nIndex < _countof(SELF_SHAPE); ++nIndex)
	{
		const POSITION& stOffset = SELF_SHAPE[nIndex];
		int nColIdx = nNewColIdx + stOffset.y;
		if (nColIdx < 0 || nColIdx >= COLUMN_COUNT)
		{
			continue;
		}

		int nBrickID = GET_BRICKID(SELF_ROW_INDEX + stOffset.x, nColIdx);
		m_mapUpdateBricks[nBrickID] = true;
	}
	
}


void CAddBrickGame::__DeleteRow(int nRowIdx)
{
	for (int nColIdx = 0; nColIdx < COLUMN_COUNT; ++nColIdx)
	{
		if (!GetBrickState(GET_BRICKID(nRowIdx, nColIdx)))
		{
			return;
		}
	}

	// Delete rows
	int nAddScoreCount = 0;
	for (int nIndex = nRowIdx; nIndex < ROW_COUNT - 1; ++nIndex)
	{
		for (int nColIdx = 0; nColIdx < COLUMN_COUNT; ++nColIdx)
		{
			int nBrickID = GET_BRICKID(nIndex, nColIdx);
			if (GetBrickState(nBrickID))
			{
				UpdateBrickState(GET_BRICKID(nIndex, nColIdx), false);
				++nAddScoreCount;
			}
		}
	}

	// Add score
	AddScore(DELETE_ROW_ADD_SCORE * nAddScoreCount);
	m_stSelfData.nHitBrickCount += nAddScoreCount;
	if (m_stSelfData.nHitBrickCount >= PASS_HIT_BRICK_COUNT)
	{
		m_enGameStage = STAGE_PASS;
		return;
	}
}


bool CAddBrickGame::__CheckGameOver()
{
	for (int nIndex = 0; nIndex < _countof(SELF_SHAPE); ++nIndex)
	{
		const POSITION& stOffset = SELF_SHAPE[nIndex];
		int nColIdx = m_stSelfData.nColIdx + stOffset.y;
		if (nColIdx < 0 || nColIdx >= COLUMN_COUNT)
		{
			continue;
		}

		int nBrickID = GET_BRICKID(SELF_ROW_INDEX + stOffset.x, nColIdx);
		if (GetBrickState(nBrickID))
		{
			return true;
		}
	}

	for (int nIndex = 0; nIndex < COLUMN_COUNT; ++nIndex)
	{
		if (GetBrickState(GET_BRICKID(ROW_COUNT - 1, nIndex)))
		{
			return true;
		}
	}

	return false;
}


int CAddBrickGame::__GetBricksMoveInterval()
{
	return BRICKS_MOVE_INTERVAL - 150 * m_nSpeed;
}


int CAddBrickGame::__GetBulletMoveInterval()
{
	return BULLET_MOVE_INTERVAL - 3 * m_nSpeed;
}

