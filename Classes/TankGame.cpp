#include "TankGame.h"
#include "Tank.h"
#include "Bullet.h"
#include "TankCommon.h"

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
	for (int i = 0; i < 5; ++i)
	{
		CC_SAFE_DELETE(m_pArrTank[i]);
		CC_SAFE_DELETE(m_pArrBullet[i]);
	}
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

	//̹�˺��ӵ�����
	for (int i = 0; i < 5; ++i)
	{
		m_pArrTank[i] = new CTank();
		m_pArrBullet[i] = new CBullet();
	}

	InitData();
}


//����
void CTankGame::Play(float dt)
{
	

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


//��ʼ������
void CTankGame::InitData()
{
	//��������̹����Ч���ӵ���Ч
	for (int i = 0; i < 5; ++i)
	{
		if (i == 0)
		{
			//�Լ�����ʼ��
			m_pArrTank[i]->Init(ROW_NUM / 2 - 1, COLUMN_NUM / 2 - 1, CAMP_A);
		}
		else
		{
			m_pArrTank[i]->SetDead(true);
		}

		m_pArrBullet[i]->SetValid(false);
	}
}


bool CTankGame::CheckTankPos(const TANK_POS& stSrcPos, int iSrcDir, const TANK_POS& stDestPos, int iDestDir)
{
	for (int i = 0; i < 12; i += 2)
	{
		int iSrcRowIdx = stSrcPos.m_iRowIdx + TANK_POS_LIST[iSrcDir][i];
		int iSrcColIdx = stSrcPos.m_iColIdx + TANK_POS_LIST[iSrcDir][i + 1];
		for (int j = 0; j < 12; j += 2)
		{
			int iDestRowIdx = stDestPos.m_iRowIdx + TANK_POS_LIST[iDestDir][i];
			int iDestColIdx = stDestPos.m_iColIdx + TANK_POS_LIST[iDestDir][i + 1];
			if (iDestRowIdx == iSrcRowIdx && iDestColIdx == iSrcColIdx)
			{
				return false;
			}
		}
	}

	return true;
}


//����̹��λ��
void CTankGame::UpdateTankPos()
{
	for (int i = 0; i < 5; ++i)
	{
		m_pArrTank[i]->UpdateTime();
		if (m_pArrTank[i]->CanMove())
		{
			
		}
	}
}


//����̹��
void CTankGame::CreateTank()
{

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