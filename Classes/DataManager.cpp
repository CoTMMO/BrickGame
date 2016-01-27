#include "DataManager.h"

CDataManager* _dataManager = nullptr;


CDataManager::CDataManager()
{
}


CDataManager::~CDataManager()
{
}


CDataManager* CDataManager::getInstance()
{
	if (_dataManager == nullptr)
	{
		_dataManager = new CDataManager();
		_dataManager->Init();
	}

	return _dataManager;
}

//��ʼ����
void CDataManager::Init()
{
	LoadGameAnim();
	
	//��ȡ��һ�ε���������
	m_bSoundOn = GET_BOOLVALUE("SOUND", true);
}

//���ض���
bool CDataManager::LoadGameAnim()
{
	//�����ļ�
	const string arrAnimFilePath[ANIM_NUM * GAME_MAX] =
	{
		"Anims/a1_1.txt",
		"Anims/a1_2.txt",
		"Anims/a1_3.txt",
		"Anims/a1_4.txt",
		"Anims/b1_1.txt",
		"Anims/b1_2.txt",
		"Anims/b1_3.txt",
		"Anims/b1_4.txt",
		"Anims/e1_1.txt",
		"Anims/e1_2.txt",
		"Anims/e1_3.txt",
		"Anims/e1_4.txt",
	};

	for (int i = 0; i < GAME_MAX * ANIM_NUM; ++i)
	{
		string strPath = FileUtils::getInstance()->fullPathForFilename(arrAnimFilePath[i]);
		string strContent = FileUtils::getInstance()->getStringFromFile(strPath);

		TVECTOR_ANIMDATA& vecAnimData = m_mapGameAnim[i];
		for (unsigned int i = 0; i < strContent.size(); ++i)
		{
			if (strContent[i] == '0')
			{
				vecAnimData.push_back(1);
			}
			else if (strContent[i] == '-')
			{
				vecAnimData.push_back(0);
			}
		}
	}

	return true;
}


vector<int>* CDataManager::GetAnimData(int iGameIndex, int iAnimIndex)
{
	int iIndex = iGameIndex * ANIM_NUM + iAnimIndex;
	return &m_mapGameAnim[iIndex];
}


//���ű�������
void CDataManager::PlayMusic(const char* strName, bool bLoop)
{
	if (m_bSoundOn)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(strName, bLoop);
	}
}

//������Ч
void CDataManager::PlayEffect(const char* strName)
{
	if (m_bSoundOn)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(strName);
	}
}


//��������״̬
void CDataManager::SetSoundState(bool bState)
{
	m_bSoundOn = bState;
	SET_BOOLVALUE("SOUND", m_bSoundOn);
}


//��ȡ����״̬
bool CDataManager::GetSoundState()
{
	return m_bSoundOn;
}
