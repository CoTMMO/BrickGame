#pragma once

#include "GlobalDef.h"

class CDataManager
{
public:
	CDataManager();
	~CDataManager();

	static CDataManager* getInstance();

	//��ʼ����
	void Init();

	//���ض���
	bool LoadGameAnim();

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

private:
	typedef vector<int> TVECTOR_ANIMDATA;
	typedef TVECTOR_ANIMDATA::iterator TVECTOR_ANIMDATA_ITER;

	typedef map<int, TVECTOR_ANIMDATA> TMAP_GAMEANIM;			//ѡ����Ϸ����Ķ���
	typedef TMAP_GAMEANIM::iterator TMAP_GAMEANIM_ITER;

	//ö��
	enum
	{
		ANIM_NUM = 4,		//ÿ����Ϸ��������
		GAME_NUM = 2,		//��Ϸ����
	};


private:
	TMAP_GAMEANIM m_mapGameAnim;			//����ÿ����Ϸ��Ӧ�Ķ���

	bool m_bSoundOn;						//�Ƿ������
};

