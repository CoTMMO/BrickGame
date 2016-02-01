#pragma once

#include "BGGlobal.h"

class CGeneralManager
{
public:
	CGeneralManager();
	~CGeneralManager();

	static CGeneralManager* getInstance();

	//��ʼ����
	void Init();

	//���ض���
	bool LoadGameAnim();

	//��ȡ��߷�
	bool LoadHighScore();

	//������߷�
	bool SaveHighScoreToFile();

	//������Ч
	void LoadSound();

	//������Ϸ�����Ͷ���������ȡ��������
	vector<int>* GetAnimData(int iGameIndex, int iAnimIndex);

	//���ű�������
	void PlayMusic(const char* strName, bool bLoop = false);

	//������Ч
	void PlayEffect(const char* strName);

	//��������״̬
	void SetSoundState(bool bState);

	//��ȡ����״̬
	bool GetSoundState();

	//��ȡ��Ϸ��߷�
	int GetHighScore(int iGameIdx);

	//������߷�
	void SetHighScore(int iGameIdx, int iScore);

private:
	typedef vector<int> TVECTOR_ANIMDATA;
	typedef TVECTOR_ANIMDATA::iterator TVECTOR_ANIMDATA_ITER;

	typedef map<int, TVECTOR_ANIMDATA> TMAP_GAMEANIM;			//ѡ����Ϸ����Ķ���
	typedef TMAP_GAMEANIM::iterator TMAP_GAMEANIM_ITER;


	typedef map<int, int> TMAP_HIGHSCORE;
	typedef TMAP_HIGHSCORE::iterator TMAP_HIGHSCORE_ITER;

	//ö��
	enum
	{
		ANIM_NUM = 4,		//ÿ����Ϸ��������
	};


private:
	TMAP_GAMEANIM m_mapGameAnim;			//����ÿ����Ϸ��Ӧ�Ķ���

	TMAP_HIGHSCORE m_mapHighScore;			//��߷�

	bool m_bSoundOn;						//�Ƿ������
};

