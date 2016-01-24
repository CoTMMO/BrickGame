#include "TankGame.h"

const int CORNER_POS[] = { 1, 1, 1, COLUMN_NUM - 2, ROW_NUM - 2, 1, ROW_NUM - 2, COLUMN_NUM - 2 };

/*
const TANK_POS TANK_POSLIST[DIR_MAX][6] = 
{
	{ TANK_POS(-1, -1), TANK_POS(-1, 0), TANK_POS(0, 0), TANK_POS(0, 1), TANK_POS(1, -1), TANK_POS(1, 0), },
	{ TANK_POS(-1, -1), TANK_POS(-1, 1), TANK_POS(0, -1), TANK_POS(0, 0), TANK_POS(0, 1), TANK_POS(1, 0), },
	{ TANK_POS(-1, 0), TANK_POS(-1, 1), TANK_POS(0, -1), TANK_POS(0, 0), TANK_POS(1, 0), TANK_POS(1, 1), },
	{ TANK_POS(-1, 0), TANK_POS(0, -1), TANK_POS(0, 0), TANK_POS(0, 1), TANK_POS(1, -1), TANK_POS(1, 1), },
};*/


const int TANK_POS_LIST[DIR_MAX][12] =
{
	{ -1, -1,   -1, 0,     0, 0,    0, 1,    1, -1,    1, 0 },
	{ -1, -1,   -1, 1,    0, -1,    0, 0,     0, 1,    1, 0 },
	{ -1, 0,    -1, 1,    0, -1,    0, 0,     1, 0,    1, 1 },
	{ -1, 0,    0, -1,     0, 0,    0, 1,    1, -1,    1, 1 },
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
	m_pGameScene->UpdateScore(m_iScore);
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSmallBricks();

	InitData();
}


//����
void CTankGame::Play(float dt)
{
	m_iCurTime += dt * 1000;
	if (m_iCurTime < TANK_REFRESH_TIME)
	{
		return;
	}

	//����ʱ��
	m_iCurTime = 0;

	//CreateTank();

}

//�ṩ��ÿ�θ��µ���Brick��Ϸ����ǰֻ����Ϸ������ʹ�ã���ȡ��ǰ�ı��Brick��������
void CTankGame::GetCurPos(int& iRowIndex, int& iColIndex)
{

}

//��ȡ��ǰBrick״̬
bool CTankGame::GetBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//��ȡС���������еķ���״̬
bool CTankGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	return false;
}

//��ȡ��Ϸ����
SCENE_INDEX CTankGame::GetSceneType()
{
	return SCENE_TANK;
}


void CTankGame::InitData()
{
	//��ʼ��̹���Լ����ڵ�λ��
	m_stSelf.m_iRowIdx = ROW_NUM / 2 - 1;
	m_stSelf.m_iColIdx = COLUMN_NUM / 2;

	//��ʼ��̹��λ�����У���������������
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		m_arrTankList[i].m_bDead = true;
	}
	
	//��ʼ����ǰ�ȴ���ʱ��
	m_iCurTime = 0;
}


//��������ʱ����̹��
void CTankGame::CreateTank()
{
	//����������̹������
	int arrDeadTankIdx[TANK_MAXNUM] = { -1 };

	int iTankCurCount = 0;
	for (int i = 0, iIndex = 0; i < TANK_MAXNUM; ++i)
	{
		if (!m_arrTankList[i].m_bDead)
		{
			++iTankCurCount;
		}
		else
		{
			arrDeadTankIdx[iIndex++] = i;
		}
	}

	//������������������µ�̹��
	for (int i = iTankCurCount, iIndex = 0; i <= TANK_MAXNUM, iIndex < TANK_MAXNUM;)
	{
		if (arrDeadTankIdx[iIndex] == -1)
		{
			++iIndex;
			continue;
		}

		TANK_DATA& pTankData = m_arrTankList[iIndex];

		//����Ч����λ��
		bool bPosValid = false;
		for (int i = 0; i < 8; i += 2)
		{
			pTankData.m_stTankPos.m_iRowIdx = CORNER_POS[i];
			pTankData.m_stTankPos.m_iColIdx = CORNER_POS[i + 1];
			pTankData.m_iDirection = Random(DIR_MIN, DIR_MAX);		//�������
			if (CheckPosValid(pTankData.m_stTankPos, pTankData.m_iDirection))
			{
				bPosValid = true;
				break;
			}
		}
		
		//���û���ҵ���Чλ�þͲ�����̹��
		if (!bPosValid)
		{
			return;
		}

		//��ʼ��̹��
		pTankData.m_bDead = false;
		pTankData.m_iCurStep = 0;
		pTankData.m_iMaxStep = Random(1, TANK_MOVE_MAXSTEP);
		pTankData.m_iCurTime = 0;
		pTankData.m_iNextFireTime = Random(0, TANK_FIRE_MAXTIME);
		pTankData.m_iRetryNum = 0;
		pTankData.m_iLastStep = -1;

		//������һ��
		++i;
	}
}


//�������̹��λ���Ƿ����ص�
bool CTankGame::CheckTankOverlap(const TANK_POS& stSrcPos, int iSrcDir, const TANK_POS& stDestPos, int iDestDir)
{
	for (int i = 0; i < 12; i += 2)
	{
		int iSrcRowIdx = stSrcPos.m_iRowIdx + TANK_POS_LIST[iSrcDir][i];
		int iSrcColIdx = stSrcPos.m_iColIdx + TANK_POS_LIST[iSrcDir][i + 1];

		for (int j = 0; j < 12; j += 2)
		{
			int iDestRowIdx = stDestPos.m_iRowIdx + TANK_POS_LIST[iDestDir][j];
			int iDestColIdx = stDestPos.m_iColIdx + TANK_POS_LIST[iDestDir][j + 1];
			if (iSrcRowIdx == iDestRowIdx && iSrcColIdx == iDestColIdx)
			{
				return true;
			}
		}
	}

	return false;
}


//���λ���Ƿ���Ч
bool CTankGame::CheckPosValid(const TANK_POS& stDestPos, int iDirection)
{
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTankList[i].m_bDead)
		{
			continue;
		}
		
		TANK_DATA& pData = m_arrTankList[i];
		if (CheckTankOverlap(stDestPos, iDirection, pData.m_stTankPos, pData.m_iDirection))
		{
			return false;
		}
	}

	return true;
}


//����̹������
void CTankGame::UpdateTankPos()
{
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTankList[i].m_bDead)
		{
			continue;
		}

		TANK_DATA& pData = m_arrTankList[i];
		

	}
}


//����
void CTankGame::OnLeftBtnPressed()
{

}

//���ͷ�
void CTankGame::OnLeftBtnReleased()
{

}

//�Ұ���
void CTankGame::OnRightBtnPressed()
{

}

//���ͷ�
void CTankGame::OnRightBtnReleased()
{

}
//�ϰ���
void CTankGame::OnUpBtnPressed()
{

}

//���ͷ�
void CTankGame::OnUpBtnReleased()
{

}

//�°���
void CTankGame::OnDownPressed()
{

}

//���ͷ�
void CTankGame::OnDownReleased()
{

}

//Fire����
void CTankGame::OnFireBtnPressed()
{

}

//Fire�ͷ�
void CTankGame::OnFireBtnReleased()
{

}