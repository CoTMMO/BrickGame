#include "TankGame.h"


const int CORNER_POS[8] = 
{
	1, 1, 
	1, COLUMN_NUM - 2,
	ROW_NUM - 2, 1,
	ROW_NUM - 2, COLUMN_NUM - 2,
};

const int TANK_POS_LIST[DIR_MAX][12] =
{
	{ -1, -1, -1,  0,  0,  0,  0,  1,  1, -1,  1,  0 },
	{ -1, -1, -1,  1,  0, -1,  0,  0,  0,  1,  1,  0 },
	{ -1,  0, -1,  1,  0, -1,  0,  0,  1,  0,  1,  1 },
	{ -1,  0,  0, -1,  0,  0,  0,  1,  1, -1,  1,  1 },
};

CTankGame::CTankGame(CGameScene* pGameScene) : CSceneBase(pGameScene)
{
}


CTankGame::~CTankGame()
{
}


//��ʼ��
void CTankGame::Init()
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

	InitData();
}


//����
void CTankGame::Play(float dt)
{
	//״̬�л�
	if (CheckGamePass())
	{
		m_enGameState = GAMESTATE_PASS;
	}

	if (GAMESTATE_OVER == m_enGameState)
	{
		//ʱ�����
		m_fWaitRefreshTime += dt;
		if (m_fWaitRefreshTime < BOOM_REFRESH_INTERVAL)
		{
			return;
		}
		m_fWaitRefreshTime = 0;

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
	else if (GAMESTATE_PASS == m_enGameState)
	{
		//ʱ�����
		m_fWaitRefreshTime += dt;
		if (m_fWaitRefreshTime < GAMEPASS_REFRESH_INTERVAL)
		{
			return;
		}
		m_fWaitRefreshTime = 0;
		
		if (m_iAddScoreCount < GAMEPASS_ADDCOUNT)
		{
			++m_iAddScoreCount;
			m_iScore += TANK_KILL_ADD_SCORE;
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

			//��������
			InitData();
		}
	}
	else
	{
		//�ӵ��ƶ�
		bool bRefreshFlag = BulletMove(dt);

		//�ҷ�̹���ƶ�
		bRefreshFlag = SelfTankMove(dt) || bRefreshFlag;

		//����̹���ƶ�
		bRefreshFlag = TankMove(dt) || bRefreshFlag;

		//̹�����
		bRefreshFlag = TankFire(dt) || bRefreshFlag;

		//����ӵ��Ƿ����̹��
		BulletShoot();

		//����̹��
		bRefreshFlag = CreateTank(dt) || bRefreshFlag;

		if (!bRefreshFlag)
		{
			return;
		}
	}

	m_pGameScene->UpdateBricks();
}


//��ȡ��ǰBrick״̬
bool CTankGame::GetBrickState(int iRowIndex, int iColIndex)
{
	bool bState;
	if (GAMESTATE_OVER == m_enGameState && ShowBoom(iRowIndex, iColIndex, bState))
	{
		return bState;
	}


	POSITION stTargetPos;
	stTargetPos.m_iRowIdx = iRowIndex;
	stTargetPos.m_iColIdx = iColIndex;

	if (DrawTank(m_stSelfTank.m_stPos, m_stSelfTank.m_iDirection, stTargetPos))
	{
		return true;
	}

	//����̹��
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTank[i].m_bDead)
		{
			continue;
		}

		const TANK_DATA& stData = m_arrTank[i];
		if (DrawTank(stData.m_stPos, stData.m_iDirection, stTargetPos))
		{
			return true;
		}
	}

	//�ӵ�
	for (int i = 0; i < BULLET_MAXNUM; ++i)
	{
		BULLET_DATA& refData = m_arrBullet[i];
		if (refData.m_bValid && stTargetPos == refData.m_stPos)
		{
			return true;
		}
	}

	return false;
}

//��ȡС���������еķ���״̬
bool CTankGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex == 0 && iColIndex < m_iLife)
	{
		return true;
	}

	return false;
}

//��ȡ��Ϸ����
SCENE_INDEX CTankGame::GetSceneType()
{
	return SCENE_TANK;
}


//��ʼ������
void CTankGame::InitData()
{
	//��ʼ��̹���ƶ��ȴ�ʱ��
	m_fTankMoveTime = 0;
	m_fTankCreateTime = 0;
	m_fSelfMoveTime = 0;
	m_fWaitRefreshTime = 0;

	//��ը��ʾ����
	m_iShowBoomCount = 0;
	//�������Ӵ�������
	m_iAddScoreCount = 0;

	//��ը��ʾ״̬
	m_bShowBoom = true;

	//̹�˴���������ʼ��
	m_iTankCreateCount = 0;

	//��Ϸ״̬
	m_enGameState = GAMESTATE_RUNNING;

	//����״̬
	m_bFireState = false;

	//��ʼ���Լ�
	m_stSelfTank.m_bDead = false;
	m_stSelfTank.m_iCamp = CAMP_A;
	m_stSelfTank.m_fFireWaitTime = 0;
	m_stSelfTank.m_fFireMaxTime = TANK_SELF_FIRE_TIME - 5 * m_iSpeed;
	m_stSelfTank.m_stPos.m_iRowIdx = ROW_NUM / 2 - 1;
	m_stSelfTank.m_stPos.m_iColIdx = COLUMN_NUM / 2 - 1;
	m_stSelfTank.m_iDirection = DIR_UP;

	//��ʼ������̹��
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		//̹��
		m_arrTank[i].m_bDead = true;
		m_arrTank[i].m_iCamp = CAMP_B;
		m_arrTank[i].m_bNeedReset = false;
	}

	//��ʼ����ť״̬
	for (int i = DIR_MIN; i < DIR_MAX; ++i)
	{
		m_arrBtnState[i] = false;
	}

	//��ʼ�������ӵ�״̬
	for (int i = 0; i < BULLET_MAXNUM; ++i)
	{
		m_arrBullet[i].m_bValid = false;
	}

	//��ʼ���ĸ�����̹�˴���״̬
	for (int i = 0; i < 4; ++i)
	{
		m_arrCornerState[i] = false;
	}

	m_pGameScene->UpdateBricks();
}


//����̹��
bool CTankGame::CreateTank(float dt)
{
	//������ָ������̹��
	if (m_iTankCreateCount >= TANK_CREATE_MAXCOUNT)
	{
		return false;
	}

	m_fTankCreateTime += dt;
	if (m_fTankCreateTime < TANK_CREATE_TIME - 40 * m_iSpeed)
	{
		return false;
	}

	m_fTankCreateTime = 0;

	//��Ҫʹ�õ�̹������
	int iTankIdx = 0;
	
	for (; iTankIdx < TANK_MAXNUM; iTankIdx++)
	{
		if (!m_arrTank[iTankIdx].m_bDead)
		{
			continue;
		}

		//λ����Ч���
		bool bPosValidFlag = false;

		TANK_DATA& stData = m_arrTank[iTankIdx];
		if (m_iTankCreateCount < TANK_MAXNUM)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (m_arrCornerState[i])
				{
					continue;
				}
				
				//ȡ�ý���λ��
				stData.m_stPos.m_iRowIdx = CORNER_POS[2 * i]; 
				stData.m_stPos.m_iColIdx = CORNER_POS[2 * i + 1];
				if (CheckPos(iTankIdx, stData.m_stPos))
				{
					//����״̬
					bPosValidFlag = true;
					m_arrCornerState[i] = true;
					break;
				}
			}
		}
		
		//�����һ�����䴴��
		if (!bPosValidFlag)
		{
			bPosValidFlag = GetCornerPos(iTankIdx);
		}

		if (bPosValidFlag)
		{
			break;
		}
	}

	if (iTankIdx >= TANK_MAXNUM)
	{
		return false;
	}

	TANK_DATA& stData = m_arrTank[iTankIdx];

	//�������
	stData.m_iDirection = Random(DIR_MIN, DIR_MAX);

	//�����������
	stData.m_bDead = false;
	stData.m_iCurStep = 0;
	stData.m_iMaxStep = Random(0, TANK_MOVE_MAXSTEP);
	stData.m_fFireWaitTime = 0;
	stData.m_fFireMaxTime = Random(0, BULLET_CREATE_MAXTIME - 450 * m_iSpeed);

	//̹�˴�����������
	++m_iTankCreateCount;

	return true;
}


bool CTankGame::DrawTank(const POSITION& stPos, int iDirection, const POSITION& stTargetPos)
{
	for (int j = 0; j < 12; j += 2)
	{
		if (stPos.m_iRowIdx + TANK_POS_LIST[iDirection][j] == stTargetPos.m_iRowIdx
			&& stPos.m_iColIdx + TANK_POS_LIST[iDirection][j + 1] == stTargetPos.m_iColIdx)
		{
			return true;
		}
	}

	return false;
}


//���λ���Ƿ���Ч
bool CTankGame::CheckPos(int iTankIdx, const POSITION& stPos)
{
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTank[i].m_bDead || (iTankIdx >= 0 && i == iTankIdx))
		{
			continue;
		}

		POSITION& stTankPos = m_arrTank[i].m_stPos;
		if (abs(stPos.m_iRowIdx - stTankPos.m_iRowIdx) < 3 && abs(stPos.m_iColIdx - stTankPos.m_iColIdx) < 3)
		{
			return false;
		}
	}

	if (iTankIdx >= 0)
	{
		POSITION& stSelfPos = m_stSelfTank.m_stPos;
		if (abs(stPos.m_iRowIdx - stSelfPos.m_iRowIdx) < 3 && abs(stPos.m_iColIdx - stSelfPos.m_iColIdx) < 3)
		{
			return false;
		}
	}

	return true;
}


//̹���ƶ�
bool CTankGame::TankMove(float dt)
{
	//ʱ�����
	m_fTankMoveTime += dt;
	if (m_fTankMoveTime < TANK_MOVE_INTERVAL - 70 * m_iSpeed)
	{
		return false;
	}

	m_fTankMoveTime = 0;

	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTank[i].m_bDead)
		{
			continue;
		}

		UpdateTankPos(i);
	}

	return true;
}


//����̹��λ��
void CTankGame::UpdateTankPos(int iTankIdx)
{
	TANK_DATA& refData = iTankIdx < 0 ? m_stSelfTank : m_arrTank[iTankIdx];

	//�Ƿ���Ҫ���ò����ͷ���
	if (refData.m_bNeedReset || refData.m_iCurStep == refData.m_iMaxStep)	//���������maxstepΪ0�����
	{
		refData.m_iDirection = Random(DIR_MIN, DIR_MAX);
		refData.m_iCurStep = 0;
		refData.m_iMaxStep = Random(0, TANK_MOVE_MAXSTEP);
		refData.m_bNeedReset = false;
		return;
	}

	POSITION stNextPos;
	if (GetNextPos(iTankIdx, stNextPos) && CheckPos(iTankIdx, stNextPos))
	{
		//����λ��
		refData.m_stPos = stNextPos;

		//Step����
		if (++refData.m_iCurStep >= refData.m_iMaxStep)
		{
			refData.m_bNeedReset = true;
		}
	}
	else
	{
		refData.m_bNeedReset = true;
	}

}

//��ȡ��һ��λ��
bool CTankGame::GetNextPos(int iTankIdx, POSITION& stOutPos)
{
	const TANK_DATA& refData = iTankIdx < 0 ? m_stSelfTank : m_arrTank[iTankIdx];
	return GetNextPos(refData.m_stPos, refData.m_iDirection, stOutPos);
}


//��ȡ��һ��λ��
bool CTankGame::GetNextPos(const POSITION& stCurPos, int iDirection, POSITION& stOutPos, bool bTankFlag)
{
	stOutPos = stCurPos;
	switch (iDirection)
	{
	case DIR_UP:
		--stOutPos.m_iRowIdx;
		break;
	case DIR_DOWN:
		++stOutPos.m_iRowIdx;
		break;
	case DIR_LEFT:
		--stOutPos.m_iColIdx;
		break;
	case DIR_RIGHT:
		++stOutPos.m_iColIdx;
		break;
	default:
		log("%s  Wrong Dirction Type. refData.m_iDirection=%d", __FUNCTION__, iDirection);
		break;
	}

	int iPadding = bTankFlag ? 1 : 0;

	if (stOutPos.m_iColIdx < iPadding || stOutPos.m_iColIdx > COLUMN_NUM - 1 - iPadding
		|| stOutPos.m_iRowIdx < iPadding || stOutPos.m_iRowIdx > ROW_NUM - 1 - iPadding)
	{
		return false;
	}

	return true;
}


//����
void CTankGame::OnLeftBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnState[DIR_LEFT] = true;
}

//���ͷ�
void CTankGame::OnLeftBtnReleased()
{
	m_arrBtnState[DIR_LEFT] = false;
}

//�Ұ���
void CTankGame::OnRightBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnState[DIR_RIGHT] = true;
}

//���ͷ�
void CTankGame::OnRightBtnReleased()
{
	m_arrBtnState[DIR_RIGHT] = false;
}
//�ϰ���
void CTankGame::OnUpBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnState[DIR_UP] = true;
}

//���ͷ�
void CTankGame::OnUpBtnReleased()
{
	m_arrBtnState[DIR_UP] = false;
}

//�°���
void CTankGame::OnDownPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	m_arrBtnState[DIR_DOWN] = true;
}

//���ͷ�
void CTankGame::OnDownReleased()
{
	m_arrBtnState[DIR_DOWN] = false;
}

//Fire����
void CTankGame::OnFireBtnPressed()
{
	if (m_enGameState != GAMESTATE_RUNNING)
	{
		return;
	}

	//��ť��Ч
	PLAY_EFFECT(EFFECT_CHANGE2);

	m_bFireState = true;
}

//Fire�ͷ�
void CTankGame::OnFireBtnReleased()
{
	m_bFireState = false;
}


const int POS_CHANGE_LIST[16] = 
{
	-1, -2, 1, -2,
	-2, -1, -2, 1,
	-1, 2, 1, 2,
	2, -1, 2, 1
};

bool CTankGame::SelfTankMove( float dt )
{
	m_fSelfMoveTime += dt;
	if (m_fSelfMoveTime < TANK_SELF_MOVE_INTERVAL - 3 * m_iSpeed)
	{
		return false;
	}
	
	//����
	m_fSelfMoveTime = 0;

	for (int i = DIR_MIN; i < DIR_MAX; ++i)
	{
		if (!m_arrBtnState[i])
		{
			continue;
		}

		POSITION stNextPos;

		if (m_stSelfTank.m_iDirection != i)
		{
			m_stSelfTank.m_iDirection = i;

			stNextPos = m_stSelfTank.m_stPos;
		}
		else
		{
			//�����뵱ǰ����һ�£������һ��λ���Ƿ���Ч
			if (!GetNextPos(-1, stNextPos) || !CheckPos(-1, stNextPos))
			{
				return false;
			}

			//����λ��
			m_stSelfTank.m_stPos = stNextPos;

			//���һ��/�в���ʾ
			m_pGameScene->UpdateBrick(stNextPos.m_iRowIdx + POS_CHANGE_LIST[i * 4], stNextPos.m_iColIdx + POS_CHANGE_LIST[i * 4 + 1], false, false);
			m_pGameScene->UpdateBrick(stNextPos.m_iRowIdx + POS_CHANGE_LIST[i * 4 + 2], stNextPos.m_iColIdx + POS_CHANGE_LIST[i * 4 + 3], false, false);
		}

		//���ҷ�̹��
		m_pGameScene->UpdateBricks(stNextPos.m_iRowIdx - 1, stNextPos.m_iColIdx - 1, stNextPos.m_iRowIdx + 2, stNextPos.m_iColIdx + 2);
		return true;
	}

	return false;
}


//�з�̹�˷����ӵ�
bool CTankGame::TankFire(float dt)
{
	//ˢ�±��
	bool bRefreshFlag = false;

	//�ҷ�̹��
	if (m_bFireState)
	{
		m_stSelfTank.m_fFireWaitTime += dt;
		if (m_stSelfTank.m_fFireWaitTime >= m_stSelfTank.m_fFireMaxTime)
		{
			m_stSelfTank.m_fFireWaitTime = 0;

			//�����ӵ�
			CreateBullet(-1);

			//����ˢ�±��
			bRefreshFlag = true;
		}
	}

	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		TANK_DATA& refData = m_arrTank[i];

		if (refData.m_bDead)
		{
			continue;
		}

		refData.m_fFireWaitTime += dt;
		if (refData.m_fFireWaitTime < refData.m_fFireMaxTime)
		{
			continue;
		}

		//���ʱ��
		refData.m_fFireMaxTime = Random(0, BULLET_CREATE_MAXTIME - 450 * m_iSpeed);
		refData.m_fFireWaitTime = 0;

		//�����ӵ�
		CreateBullet(i);

		//ˢ�±��
		bRefreshFlag = true;
	}

	return bRefreshFlag;
}


//�ӵ�����
void CTankGame::CreateBullet(int iTankIdx)
{
	TANK_DATA& refTankData = iTankIdx < 0 ? m_stSelfTank : m_arrTank[iTankIdx];

	for (int i = 0; i < BULLET_MAXNUM; ++i)
	{
		BULLET_DATA& refData = m_arrBullet[i];
		if (!refData.m_bValid)
		{
			//��ʼ���ӵ�
			refData.m_bValid = true;
			refData.m_fMoveTime = 0;
			refData.m_iCamp = refTankData.m_iCamp;
			refData.m_stPos = refTankData.m_stPos;
			refData.m_iDirection = refTankData.m_iDirection;
			return;
		}
	}
}


//�ӵ��ƶ�
bool CTankGame::BulletMove(float dt)
{
	//ˢ�±��
	bool bRefreshFlag = false;

	for (int i = 0; i < BULLET_MAXNUM; ++i)
	{
		BULLET_DATA& refData = m_arrBullet[i];
		if (!refData.m_bValid)
		{
			continue;
		}

		//ʱ�����
		refData.m_fMoveTime += dt;
		if ( refData.m_fMoveTime < BULLET_MOVE_INTERVAL - 2 * m_iSpeed )
		{
			continue;
		}
		refData.m_fMoveTime = 0;

		//��һ��λ��
		POSITION stNextPos;
		if (GetNextPos(refData.m_stPos, refData.m_iDirection, stNextPos, false))
		{
			refData.m_stPos = stNextPos;
		}
		else
		{
			//�ӵ�״̬
			refData.m_bValid = false;

			//����ʾ
			m_pGameScene->UpdateBrick(refData.m_stPos.m_iRowIdx, refData.m_stPos.m_iColIdx, false, false);
		}

		bRefreshFlag = true;
	}

	return bRefreshFlag;
}


//�ӵ��Ƿ����ĳ̹��
int CTankGame::GetBulletFireTankIndex(const POSITION& stBulletPos, int iCamp)
{
	if (iCamp == CAMP_A)
	{
		for (int i = 0; i < TANK_MAXNUM; ++i)
		{
			if (m_arrTank[i].m_bDead)
			{
				continue;
			}

			TANK_DATA& refData = m_arrTank[i];
			int iTankDir = refData.m_iDirection;
			
			//����Ƿ����
			for (int j = 0; j < 12; j += 2)
			{
				POSITION stPos = refData.m_stPos;
				stPos.m_iRowIdx += TANK_POS_LIST[iTankDir][j];
				stPos.m_iColIdx += TANK_POS_LIST[iTankDir][j + 1];
				if (stPos == stBulletPos)
				{
					return i;
				}
			}
		}
	}
	else if (iCamp == CAMP_B)
	{
		//����Ƿ����
		for (int j = 0; j < 12; j += 2)
		{
			POSITION stPos = m_stSelfTank.m_stPos;
			stPos.m_iRowIdx += TANK_POS_LIST[m_stSelfTank.m_iDirection][j];
			stPos.m_iColIdx += TANK_POS_LIST[m_stSelfTank.m_iDirection][j + 1];
			if (stPos == stBulletPos)
			{
				return 1;
			}
		}
	}

	return -1;
}


//��ʾ��ըЧ��
bool CTankGame::ShowBoom(int iRowIndex, int iColIndex, bool& bState)
{
	POSITION stPos = m_stSelfTank.m_stPos;

	//�߽����
	if (stPos.m_iRowIdx == ROW_NUM - 2)
	{
		stPos.m_iRowIdx = ROW_NUM - 3;
	}
	if (stPos.m_iColIdx == COLUMN_NUM - 2)
	{
		stPos.m_iColIdx = COLUMN_NUM - 3;
	}
	
	int iActualRowIdx = iRowIndex - (stPos.m_iRowIdx - 1);
	int iActualColIdx = iColIndex - (stPos.m_iColIdx - 1);

	if (iActualRowIdx >= 0 && iActualRowIdx < 4
		&& iActualColIdx >= 0 && iActualColIdx < 4)
	{
		bState = BOOM_STATE[iActualRowIdx][iActualColIdx] && m_bShowBoom;
		return true;
	}

	return false;
}


void CTankGame::BulletShoot()
{
	for (int i = 0; i < BULLET_MAXNUM; ++i)
	{
		BULLET_DATA& refData = m_arrBullet[i];
		if (!refData.m_bValid)
		{
			continue;
		}

		int iTankIdx = GetBulletFireTankIndex(refData.m_stPos, refData.m_iCamp);
		if (iTankIdx >= 0)
		{
			if (refData.m_iCamp == CAMP_A)
			{
				TANK_DATA& refTankData = m_arrTank[iTankIdx];

				//�з�̹������
				refTankData.m_bDead = true;

				//�ػ���Ӧ����״̬
				POSITION& stDeadTankPos = refTankData.m_stPos;
				m_pGameScene->UpdateBricks(stDeadTankPos.m_iRowIdx - 1, stDeadTankPos.m_iColIdx - 1,
					stDeadTankPos.m_iRowIdx + 2, stDeadTankPos.m_iColIdx + 2);

				//��������
				m_iScore += TANK_KILL_ADD_SCORE;
				m_pGameScene->UpdateScore(m_iScore);
			}
			else if (refData.m_iCamp == CAMP_B)
			{
				//�ҷ�̹������
				m_enGameState = GAMESTATE_OVER;
				PLAY_EFFECT(EFFECT_BOOM);
			}

			//�ӵ�״̬
			refData.m_bValid = false;

			//����ʾ
			m_pGameScene->UpdateBrick(refData.m_stPos.m_iRowIdx, refData.m_stPos.m_iColIdx, false, false);
		}
	}
}

//�Ƿ�ͨ����ǰ�ȼ�
bool CTankGame::CheckGamePass()
{
	if (m_enGameState == GAMESTATE_OVER || m_iTankCreateCount < TANK_CREATE_MAXCOUNT)
	{
		return false;
	}

	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (!m_arrTank[i].m_bDead)
		{
			return false;
		}
	}

	return true;
}


//��ȡһ����Ч�Ľ���λ��
bool CTankGame::GetCornerPos( int iTankIdx )
{
	int arrValidPosIdx[4] = { 0 };
	int iValidCount = 0;
	POSITION stTempPos;

	for (int i = 0; i < 8; i += 2)
	{
		stTempPos.m_iRowIdx = CORNER_POS[i];
		stTempPos.m_iColIdx = CORNER_POS[i + 1];
		if (CheckPos(iTankIdx, stTempPos))
		{
			arrValidPosIdx[iValidCount++] = i;
		}
	}

	if (iValidCount <= 0)
	{
		return false;
	}

	//����λ��
	int iRandIdx = Random(0, iValidCount);
	int iValidIdx = arrValidPosIdx[iRandIdx];
	POSITION& stPos = m_arrTank[iTankIdx].m_stPos;
	stPos.m_iRowIdx = CORNER_POS[iValidIdx];
	stPos.m_iColIdx = CORNER_POS[iValidIdx + 1];
	return true;
}
