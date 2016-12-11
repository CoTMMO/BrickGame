#pragma once

#include "BGGlobal.h"

class CGeneralManager
{
public:
	CGeneralManager();
	~CGeneralManager();

	static CGeneralManager* getInstance();

	//������Ϸ�����Ͷ���������ȡ��������
	vector<int>* GetAnimData(int iGameIndex, int iAnimIndex);

	//���ű�������
	void PlayMusic(const char* strName, bool bLoop = false);

	//������Ч
	void PlayEffect(const char* strName);

	//��ȡ��Ϸ��߷�
	int GetHighScore(int iGameIdx);

	//������߷�
	void SetHighScore(int iGameIdx, int iScore);

	//�������˹��������
	void SaveTetrisData(const bool(&arrState)[ROW_NUM][COLUMN_NUM]);

	//���ض���˹��������
	void LoadTetrisData(bool(&arrState)[ROW_NUM][COLUMN_NUM]);

	//������߷�
	bool SaveHighScoreToFile();

	//��ȡ�˵�����
	const char* GetStringByID(int nLangID, int nStrID);

private:
	//��ʼ����
	void Init();

	//���ض���
	bool LoadGameAnim();

	//��ȡ��߷�
	bool LoadHighScore();

	//������Ч
	void LoadSound();

	//�����ַ���
	void LoadStrings();

private:
	typedef vector<int> TVECTOR_ANIMDATA;
	typedef TVECTOR_ANIMDATA::iterator TVECTOR_ANIMDATA_ITER;

	typedef map<int, TVECTOR_ANIMDATA> TMAP_GAMEANIM;			//ѡ����Ϸ����Ķ���
	typedef TMAP_GAMEANIM::iterator TMAP_GAMEANIM_ITER;


	typedef map<int, int> TMAP_HIGHSCORE;
	typedef TMAP_HIGHSCORE::iterator TMAP_HIGHSCORE_ITER;


	typedef map<int, std::string> TMAP_STRING;
	typedef map<int, TMAP_STRING>	TMAP_LANGUAGESTRING;

private:
	TMAP_GAMEANIM m_mapGameAnim;			//����ÿ����Ϸ��Ӧ�Ķ���

	TMAP_HIGHSCORE m_mapHighScore;			//��߷�

	TMAP_LANGUAGESTRING	m_mapStrings;		//�ַ����б�
};

