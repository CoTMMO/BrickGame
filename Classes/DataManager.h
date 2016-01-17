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

	vector<int>* GetAnimData(int iGameIndex, int iAnimIndex);

private:
	typedef vector<int> TVECTOR_ANIMDATA;
	typedef TVECTOR_ANIMDATA::iterator TVECTOR_ANIMDATA_ITER;

	typedef map<int, TVECTOR_ANIMDATA> TMAP_GAMEANIM;			//ѡ����Ϸ����Ķ���
	typedef TMAP_GAMEANIM::iterator TMAP_GAMEANIM_ITER;

	//ö��
	enum
	{
		ANIM_NUM = 4,		//ÿ����Ϸ��������
		GAME_NUM = 1,		//��Ϸ����
	};


private:
	TMAP_GAMEANIM m_mapGameAnim;			//����ÿ����Ϸ��Ӧ�Ķ���

};

