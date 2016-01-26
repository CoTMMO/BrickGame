#pragma once
#include "SceneBase.h"

class CTank;
class CBullet;
struct TANK_POS;

class CTankGame : public CSceneBase
{
public:
	CTankGame(CGameScene* pGameScene);
	~CTankGame();

	//---------------------    CSceneBase    ----------------------
	//��ʼ��
	void Init();

	//����
	void Play(float dt);

	//��ȡ��ǰBrick״̬
	bool GetBrickState(int iRowIndex, int iColIndex);

	//��ȡС���������еķ���״̬
	bool GetSmallBrickState(int iRowIndex, int iColIndex);

	//��ȡ��Ϸ����
	SCENE_INDEX GetSceneType();

	//����
	void OnLeftBtnPressed();

	//���ͷ�
	void OnLeftBtnReleased();

	//�Ұ���
	void OnRightBtnPressed();

	//���ͷ�
	void OnRightBtnReleased();

	//�ϰ���
	void OnUpBtnPressed();

	//���ͷ�
	void OnUpBtnReleased();

	//�°���
	void OnDownPressed();

	//���ͷ�
	void OnDownReleased();

	//Fire����
	void OnFireBtnPressed();

	//Fire�ͷ�
	void OnFireBtnReleased();

	//---------------------    CSceneBase    ----------------------

private:
	//��ʼ�����ݣ���Init��ͬ��Init���л����ó���ʱ���ã�InitData������ʱ����
	void InitData();

	//�������̹��λ��֮���Ƿ����ص�
	bool CheckTankPos(const TANK_POS& stSrcPos, int iSrcDir, const TANK_POS& stDestPos, int iDestDir);
	
	//���
	bool CheckNewPos(int iTankIdx);

	//����̹��λ��
	void UpdateTankPos(float dt);

	//����̹��
	void CreateTank();

private:
	enum
	{
		TANK_MAXNUM = 4,			//̹���������
	};

private:
	CTank* m_pArrTank[5];						//̹���б�

	CBullet* m_pArrBullet[5];					//�ӵ��б�

	int m_iSpeed;								//�ٶ�

	int m_iLevel;								//�ؿ�

	int m_iLife;								//ʣ������

	int m_iScore;								//����
};

