#include "FroggerGame.h"

const bool RIVER_DEFAULT_STATE[5][20] =
{
	{ false, true, true, true, false, false, true, true, true, false, false, true, true, true, false, false, true, true, true, false},
	{ true, true, true, false, false, false, false, false, true, true, true, true, true, false, false, false, false, false, true, true },
	{ false, false, true, true, true, false, false, true, true, false, false, false, true, true, true, false, false, true, true, false },
	{ false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, true, true, false, false },
	{ false, false, true, true, true, false, false, false, false, false, false, false, true, true, true, false, false, false, false, false },
};

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

	//��ʼ����ǰ��������������������
	m_iScore = 0;

	//���½��棬�������ȼ�������
	m_pGameScene->UpdateScore(m_iScore);
	m_pGameScene->UpdateLevel(m_iLevel);
	m_pGameScene->UpdateSmallBricks();

	InitData();
}

//����
void CFroggerGame::Play(float dt)
{
	//�����Լ�
	UpdateSelf(dt);

	//�ӵ�����
	UpdateRivers(dt);

	//�������
	m_pGameScene->UpdateBricks();
}

//��ȡ��ǰBrick״̬
bool CFroggerGame::GetBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex == m_iSelfRowIdx && iColIndex == m_iSelfColIdx)
	{
		return m_bSelfState;
	}

	return m_arrBrickState[iRowIndex][iColIndex];
}

//������
bool CFroggerGame::GetSmallBrickState(int iRowIndex, int iColIndex)
{
	if (iRowIndex == 0 && iColIndex < m_iLife)
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

//����
void CFroggerGame::OnLeftBtnPressed()
{

}

//�Ұ���
void CFroggerGame::OnRightBtnPressed()
{

}

//�ϰ���
void CFroggerGame::OnUpBtnPressed()
{

}

//�°���
void CFroggerGame::OnDownPressed()
{

}

//Fire����
void CFroggerGame::OnFireBtnPressed()
{

}


//�������кӵ�
void CFroggerGame::UpdateRivers(float dt)
{
	for (int i = ROW_NUM - 2; i >= RIVER_TOP_ROWINDEX; --i)
	{
		//ż���ӵ�Ĭ��ȫ����䣬�������
		if (i % 2 == 0)
		{
			continue;
		}

		UpdateRiver(i, dt);
	}
}

//����ָ���еĺӵ�
void CFroggerGame::UpdateRiver(int iRowIndex, float dt)
{
	RIVER& stRiver = m_mapRiverData[iRowIndex];
	stRiver.iCurTime += dt;

	//�Ƿ�ﵽˢ��ʱ��
	if (stRiver.iCurTime >= stRiver.iRefreshTime)
	{
		stRiver.iCurTime = 0;

		//��������Ƿ���Ҫˢ��
		srand((unsigned)time(nullptr));
		int iRandom = ((int)(CCRANDOM_0_1() * 100)) % 2;
		if (iRandom == 0)
		{
			return;
		}

		//����
		if (stRiver.bLeft)
		{
			bool bTemp = m_arrBrickState[iRowIndex][0];
			for (int i = 1; i < COLUMN_NUM; ++i)
			{

			}
			stRiver.iOffset -= 1;
		}
		
	}
}


//�����Լ�
void CFroggerGame::UpdateSelf(float dt)
{
	m_iSelfCurTime += dt;
	if (m_iSelfCurTime >= SELF_REFRESHTIME)
	{
		m_iSelfCurTime = 0;
		m_bSelfState = !m_bSelfState;
	}
}


//��ʼ�����ݡ�������
void CFroggerGame::InitData()
{
	//���ó�ʼ����λ��
	m_iSelfRowIdx = ROW_NUM - 1;
	m_iSelfColIdx = COLUMN_NUM / 2 - 1;

	m_iSelfCurTime = 0;
	m_bSelfState = false;

	//��ʼ�������ӵ�״̬����
	int iRiverCount = 0;
	bool bLeft = false;
	for (int i = ROW_NUM - 2; i >= RIVER_TOP_ROWINDEX; --i)
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
			bLeft = !bLeft;
			RIVER& stRiver = m_mapRiverData[i];
			stRiver.bLeft = bLeft;
			stRiver.iCurTime = 0;
			stRiver.iOffset = 0;
			stRiver.iRefreshTime = DEFAULT_REFRESHTIME - 30 * m_iSpeed;

			//���ó�ʼ״̬
			for (int j = 0, int iCount = 0; j < COLUMN_NUM; ++j)
			{
				m_arrBrickState[i][j] = RIVER_DEFAULT_STATE[iRiverCount][iCount];
			}

			++iRiverCount;
		}
	}
}
