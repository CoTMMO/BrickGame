#include "TankGame.h"

const int CORNER_POS[] = { 0, 0, 0, COLUMN_NUM - 1, ROW_NUM - 1, 0, ROW_NUM - 1, COLUMN_NUM - 1 };

//̹���ĸ�����״̬
const int TANK_POSLIST[DIR_MAX][3][3] = 
{
	{	//DIR_RIGHT
		{ true, true, false },
		{ false, true, true },
		{ true, true, false },
	},
	{	//DIR_DOWN
		{ true, false, true },
		{ true, true, true },
		{ false, true, false },
	},
	{	//DIR_LEFT
		{ false, true, true },
		{ true, true, false },
		{ false, true, true },
	},
	{	//DIR_UP
		{ false, true, false },
		{ true, true, true },
		{ true, false, true },
	},
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
	m_iCurTime += dt;
	if (m_iCurTime < TANK_REFRESHTIME)
	{
		return;
	}

	//����ʱ��
	m_iCurTime = 0;

	CreateTank();

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

		bool bPosValid = false;
		for (int i = 0; i < sizeof(CORNER_POS) / sizeof(int) - 1; i += 2)
		{
			pTankData.m_stTankPos.m_iRowIdx = CORNER_POS[i];
			pTankData.m_stTankPos.m_iColIdx = CORNER_POS[i + 1];
			if (CheckPosValid(pTankData.m_stTankPos))
			{
				bPosValid = true;
				break;
			}
		}
		
		if (!bPosValid)
		{
			return;
		}

		//��ʼ��̹��
		pTankData.m_bDead = false;
		pTankData.m_iCurStep = 0;
		pTankData.m_iMaxStep = Random(1, TANK_MAXSTEP);
		pTankData.m_iCurTime = 0;
		pTankData.m_iNextFireTime = Random(1, TANK_FIREMAXTIME);
		pTankData.m_iDirection = Random(DIR_MIN, DIR_MAX);			//�������

		//������һ��
		++i;
	}
}


bool CTankGame::CheckPosValid(const TANK_POS& stDestPos)
{
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTankList[i].m_bDead)
		{
			continue;
		}

		TANK_DATA& pData = m_arrTankList[i];
		
		

	}

	return true;
}


//����̹������
void CTankGame::TanksMove()
{
	for (int i = 0; i < TANK_MAXNUM; ++i)
	{
		if (m_arrTankList[i].m_bDead)
		{
			continue;
		}

		UpdateTankPos(i);
	}
}


//����̹��λ��
void CTankGame::UpdateTankPos(int iTankIdx)
{
	TANK_DATA& pData = m_arrTankList[iTankIdx];
	if (pData.m_iMaxStep > 0 && pData.m_iCurStep < pData.m_iMaxStep)
	{
		
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