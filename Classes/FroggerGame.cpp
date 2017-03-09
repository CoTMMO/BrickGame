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

	//��ʼ����ǰ����
	m_iScore = 0;

	//���½��棬�������ȼ�������
	m_pGameScene->UpdateScore(m_iScore, false);
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSmallBricks();

	//��ʼ�ӵ�״̬����
	const bool RIVER_DEFAULT_STATE[5][20] =
	{
		{ false, true, true, true, false, false, true, true, true, false, false, true, true, true, false, false, true, true, true, false },
		{ true, true, true, false, false, false, false, false, true, true, true, true, true, false, false, false, false, false, true, true },
		{ false, false, true, true, true, false, false, true, true, false, false, false, true, true, true, false, false, true, true, false },
		{ false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, true, true, false, false },
		{ false, false, true, true, true, false, false, false, false, false, false, false, true, true, true, false, false, false, false, false },
	};

	//��ʼ���ӵ�����
	bool bLeft = false;
	for (int i = RIVER_ROWTOP_INDEX + 1, iRiverCount = 0; i < ROW_NUM - 1; i += 2)
	{
		RIVER& stRiver = m_mapRiverData[i];
		bLeft = !bLeft;
		stRiver.bLeft = bLeft;
		
		for (int j = 0; j < RIVER_LEN; ++j)
		{
			stRiver.arrDefaultState[j] = RIVER_DEFAULT_STATE[iRiverCount][j];
		}

		++iRiverCount;
	}

	//��ʼ��ͨ������
	m_iPassCount = 0;

	InitData();
}

//����
void CFroggerGame::Play(float dt)
{
	if (m_enGameState == GAMESTATE_PASS)
	{
		m_fPassCurTime += dt;
		if (m_fPassCurTime < GAMEPASS_WAITTIME)
		{
			return;
		}

		//����ͨ������
		m_iPassCount = 0;

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
		InitData();

		//�������
		m_pGameScene->UpdateBricks();
		return;
	}

	//������
	if (m_enGameState == GAMESTATE_RUNNING)
	{
		//�����Լ�
		bool bUpdateFlag = UpdateSelf(dt);

		//���ºӵ�
		bUpdateFlag = UpdateRivers(dt) || bUpdateFlag;

		if (!bUpdateFlag)
		{
			return;
		}

		//������Ϸ״̬
		UpdateGameState();
	}

	if (m_enGameState == GAMESTATE_OVER)
	{
		if (!SetBoom(dt))
		{
			return;
		}

		if (m_iShowBoomCount >= BOOM_SHOWCOUNT)
		{
			//����ʣ������
			--m_iLife;
			m_pGameScene->UpdateSmallBricks();
			
			//����Ƿ���ʣ��������û���򷵻���Ϸ��������
			if (m_iLife == 0)
			{
				m_pGameScene->RunScene(SCENE_GAMEOVER);
				return;
			}

			//��������
			InitData();

			m_pGameScene->UpdateSmallBricks();
		}
	}

	//�������
	m_pGameScene->UpdateBricks();
}

//��ȡ��ǰBrick״̬
bool CFroggerGame::GetBrickState(int nRowIdx, int nColIdx)
{
	//������Ϸ����ʱ��ʾ�Լ���λ��
	if (m_enGameState == GAMESTATE_RUNNING && nRowIdx == m_iSelfRowIdx && nColIdx == m_iSelfColIdx)
	{
		return m_bSelfState;
	}

	return m_arrBrickState[nRowIdx][nColIdx];
}

//������
bool CFroggerGame::GetSmallBrickState(int nRowIdx, int nColIdx)
{
	if (nRowIdx == 0 && nColIdx < m_iLife)
	{
		return true;
	}

	return false;
}

//��ȡ��Ϸ����
SCENE_INDEX CFroggerGame::GetSceneType()
{
	return SCENE_FROGGER;
}


//�������кӵ�
bool CFroggerGame::UpdateRivers(float dt)
{
	m_fRiverCurTime += dt;
	if (m_fRiverCurTime < DEFAULT_REFRESHTIME - 30 * m_iSpeed)
	{
		return false;
	}
	
	//����
	m_fRiverCurTime = 0;

	//������¼����ӵ�
	int iUpdateCount = 2 + Random(0, RIVER_COUNT - 2);
	ClearInvalidNums();
	for (int i = 0; i < iUpdateCount; ++i)
	{
		int nIndex = Random(0, RIVER_COUNT);
		int nRowIdx = RIVER_ROWTOP_INDEX + 1 + nIndex * 2;
		UpdateRiver(nRowIdx);
		AddInvalidNum(nIndex);
	}
	ClearInvalidNums();

	return iUpdateCount > 0;
}

//����ָ���еĺӵ�
void CFroggerGame::UpdateRiver(int nRowIdx)
{
	RIVER& stRiver = m_mapRiverData[nRowIdx];

	//����
	if (stRiver.bLeft)
	{
		stRiver.iOffset += 1;
		if (stRiver.iOffset >= RIVER_LEN)
		{
			stRiver.iOffset = 0;
		}

		int nColIdx = 0;
		for (int i = stRiver.iOffset; i < RIVER_LEN && nColIdx < COLUMN_NUM; ++i, ++nColIdx)
		{
			m_arrBrickState[nRowIdx][nColIdx] = stRiver.arrDefaultState[i];

		}

		for (int i = 0; i < RIVER_LEN && nColIdx < COLUMN_NUM; ++i, ++nColIdx)
		{
			m_arrBrickState[nRowIdx][nColIdx] = stRiver.arrDefaultState[i];
		}
	}
	else
	{
		stRiver.iOffset -= 1;
		if (stRiver.iOffset <= -RIVER_LEN)
		{
			stRiver.iOffset = 0;
		}

		int nColIdx = 0;
		for (int i = stRiver.iOffset + RIVER_LEN; i < RIVER_LEN && nColIdx < COLUMN_NUM; ++i, ++nColIdx)
		{
			m_arrBrickState[nRowIdx][nColIdx] = stRiver.arrDefaultState[i];
		}

		for (int i = 0; i < RIVER_LEN && nColIdx < COLUMN_NUM; ++i, ++nColIdx)
		{
			m_arrBrickState[nRowIdx][nColIdx] = stRiver.arrDefaultState[i];
		}
	}
}


//�����Լ�
bool CFroggerGame::UpdateSelf(float dt)
{
	m_fSelfCurTime += dt;
	if (m_fSelfCurTime >= SELF_REFRESHTIME)
	{
		m_fSelfCurTime = 0;
		m_bSelfState = !m_bSelfState;
		return true;
	}

	return false;
}


//��ʼ�����ݡ�������
void CFroggerGame::InitData()

{
	//���ó�ʼ����λ��
	m_iSelfRowIdx = ROW_NUM - 1;
	m_iSelfColIdx = COLUMN_NUM / 2 - 1;

	//��ʼ�����ܵ�ʱ���״̬
	m_fSelfCurTime = 0;
	m_bSelfState = false;

	//��ʼ����ը״̬
	m_iShowBoomCount = 0;
	m_fBoomCurTime = 0;

	//��ʼ���ӵ���ǰʱ��
	m_fRiverCurTime = 0;

	//��ʼ����Ϸͨ����ǰʱ��
	m_fPassCurTime = 0;

	//��ʼ����Ϸ״̬
	m_enGameState = GAMESTATE_RUNNING;

	//��ʼ�������ӵ�״̬����
	int iRiverCount = 0;
	for (int i = ROW_NUM - 2; i >= RIVER_ROWTOP_INDEX; --i)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < COLUMN_NUM; ++j)
			{
				m_arrBrickState[i][j] = true;
			}
		}
		else
		{
			RIVER& stRiver = m_mapRiverData[i];
			stRiver.iOffset = 0;

			//���ó�ʼ״̬
			for (int j = 0; j < COLUMN_NUM; ++j)
			{
				m_arrBrickState[i][j] = stRiver.arrDefaultState[j];
			}

			++iRiverCount;
		}
	}

	//��ʼ��������
	for (int i = RIVER_ROWTOP_INDEX - 1; i >= 0; --i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			m_arrBrickState[i][j] = false;
		}
	}

	//���һ��
	for (int j = 0; j < COLUMN_NUM; ++j)
	{
		m_arrBrickState[ROW_NUM - 1][j] = false;
	}
}


//������Ϸ״̬������Ƿ���Ϸ����
void CFroggerGame::UpdateGameState()
{
	if (m_arrBrickState[m_iSelfRowIdx][m_iSelfColIdx])
	{
		m_enGameState = GAMESTATE_OVER;
		PLAY_EFFECT(EFFECT_BOOM);

		//��
		m_pGameScene->OnLongVibrate();
	}
}


//���ñ�ը
bool CFroggerGame::SetBoom( float dt )
{
	m_fBoomCurTime += dt;
	if (m_fBoomCurTime < BOOM_REFRESHTIME)
	{
		return false;
	}

	//����
	m_fBoomCurTime = 0;

	int iColStartIdx = m_iSelfColIdx;
	if (iColStartIdx > COLUMN_NUM - 4)
	{
		iColStartIdx = COLUMN_NUM - 4;
	}

	bool bShow = (m_iShowBoomCount % 2 == 0);
	for (int i = m_iSelfRowIdx - 3; i <= m_iSelfRowIdx; ++i)
	{
		int iIndex = i - (m_iSelfRowIdx - 3);
		for (int j = iColStartIdx; j < iColStartIdx + 4; ++j)
		{
			m_arrBrickState[i][j] = bShow && BOOM_STATE[iIndex][j - iColStartIdx];
		}
	}

	++m_iShowBoomCount;
	return true;
}


//����
void CFroggerGame::OnLeftBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING || m_iSelfColIdx == 0)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	//����ɵ�λ��
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, false);

	--m_iSelfColIdx;
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, true);

	//������Ϸ״̬
	UpdateGameState();
}

//�Ұ���
void CFroggerGame::OnRightBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING || m_iSelfColIdx == COLUMN_NUM - 1)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	//����ɵ�λ��
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, false);

	++m_iSelfColIdx;
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, true);

	//������Ϸ״̬
	UpdateGameState();
}

//�ϰ���
void CFroggerGame::OnUpBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING || m_iSelfRowIdx < RIVER_ROWTOP_INDEX)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	//����ɵ�λ��
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, false);

	m_iSelfRowIdx -= 2;
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, true);

	UpdateGameState();

	if (m_iSelfRowIdx == RIVER_ROWTOP_INDEX - 1 && m_enGameState != GAMESTATE_OVER)
	{
		//���ﶥ�˵ķ��鲻����˸��ʾ
		m_arrBrickState[m_iSelfRowIdx][m_iSelfColIdx] = true;

		//������ˣ���������
		m_iScore += 30;
		m_pGameScene->UpdateScore(m_iScore);

		//����ͨ������������
		++m_iPassCount;

		//����Ƿ�ͨ���ؿ�
		if (m_iPassCount == GAMEPASS_COUNT)
		{
			m_enGameState = GAMESTATE_PASS;

			//��
			m_pGameScene->OnLongVibrate();
		}
		else
		{
			//����λ�ú�״̬
			m_iSelfRowIdx = ROW_NUM - 1;
			m_iSelfColIdx = 6;
			m_fSelfCurTime = 0;
			m_bSelfState = true;
		}
	}
}

//�°���
void CFroggerGame::OnDownBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING || m_iSelfRowIdx >= ROW_NUM - 1)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	//����ɵ�λ��
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, false);

	m_iSelfRowIdx += 2;
	m_pGameScene->UpdateBrick(m_iSelfRowIdx, m_iSelfColIdx, false, true);

	//������Ϸ״̬
	UpdateGameState();
}

//Fire����
void CFroggerGame::OnFireBtnPressed()
{
	OnUpBtnPressed();
}


void CFroggerGame::SaveGameData()
{
	
}