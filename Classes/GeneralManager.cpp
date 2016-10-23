#include "GeneralManager.h"

CGeneralManager* _dataManager = nullptr;


const string HIGHSCORE_FILEPATH = "./HighScore.json";

CGeneralManager::CGeneralManager()
{
}


CGeneralManager::~CGeneralManager()
{
}


CGeneralManager* CGeneralManager::getInstance()
{
	if (_dataManager == nullptr)
	{
		_dataManager = new CGeneralManager();
		_dataManager->Init();
	}

	return _dataManager;
}

//��ʼ����
void CGeneralManager::Init()
{
	LoadGameAnim();
	
	LoadHighScore();

	LoadSound();

	//��ȡ��һ�ε���������
	m_bSoundOn = GET_BOOLVALUE("SOUND", true);

	//���֮ǰ��¼��һЩ����
	SET_INTVALUE("GAME", 0);
	SET_INTVALUE("SPEED", 0);
	SET_INTVALUE("LEVEL", 0);
}

//���ض���
bool CGeneralManager::LoadGameAnim()
{
	//���ض����ļ�
	for (int i = 0; i < GAME_MAX; ++i)
	{
		for (int j = 0; j < ANIM_NUM; ++j)
		{
			string strFilePath = StringUtils::format("Anims/%c1_%d.txt", i + 'a', j + 1);
			string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
			string strContent = FileUtils::getInstance()->getStringFromFile(strFullPath);

			TVECTOR_ANIMDATA& vecAnimData = m_mapGameAnim[i * ANIM_NUM + j];
			for (unsigned int k = 0; k < strContent.size(); ++k)
			{
				if (strContent[k] == '0')
				{
					vecAnimData.push_back(1);
				}
				else if (strContent[k] == '-')
				{
					vecAnimData.push_back(0);
				}
			}
		}
	}

	return true;
}


//������߷�
bool CGeneralManager::LoadHighScore()
{
	string strPath = FileUtils::getInstance()->getWritablePath() + string(HIGHSCORE_FILEPATH);

	string strContent = FileUtils::getInstance()->getStringFromFile(strPath);
	rapidjson::Document oDoc;
	oDoc.Parse<0>(strContent.c_str());
	if (oDoc.HasParseError() || oDoc.IsNull())
	{
		TRACE("CGeneralManager::LoadUserData Load 'oDoc' Error.");
		return false;
	}

	for (int i = 0; i < oDoc["HighScore"].Size(); i++)
	{
		if (oDoc["HighScore"][i].IsNull())
		{
			TRACE("CGeneralManager::LoadUserData Load 'oDoc[HighScore][%d]' Error.", i);
			return false;
		}

		int iValue = oDoc["HighScore"][i].GetInt();
		m_mapHighScore[i] = iValue;
	}

	return true;
}


//������߷ֵ��ļ���
bool CGeneralManager::SaveHighScoreToFile()
{
	string strPath = FileUtils::getInstance()->getWritablePath() + string(HIGHSCORE_FILEPATH);
	string strContent = FileUtils::getInstance()->getStringFromFile(strPath);
	rapidjson::Document oDoc;
	oDoc.Parse<0>(strContent.c_str());
	if (oDoc.HasParseError() || oDoc.IsNull())
	{
		oDoc.SetObject();
		rapidjson::Document::AllocatorType& allocator = oDoc.GetAllocator();
		rapidjson::Value oArray(rapidjson::kArrayType);

		for (int i = 0; i < GAME_MAX; ++i)
		{
			oArray.PushBack(m_mapHighScore[i], allocator);
		}
		oDoc.AddMember("HighScore", oArray, allocator);
	}
	else
	{
		//��������
		for (rapidjson::SizeType i = 0; i < oDoc["HighScore"].Capacity(); i++)
		{
			if (oDoc["HighScore"][i].IsNull())
			{
				return false;
			}
			oDoc["HighScore"][i].SetInt(m_mapHighScore[i]);
		}
	}

	rapidjson::StringBuffer oBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> oWriter(oBuffer);
	oDoc.Accept(oWriter);

	FILE* pFile = fopen(strPath.c_str(), "wb+");
	if (pFile == NULL)
	{
		TRACE("Open File '%s' Failed.", strPath.c_str());
		return false;
	}

	fputs(oBuffer.GetString(), pFile);
	fclose(pFile);

	return true;
}


//������Ч
void CGeneralManager::LoadSound()
{
	PRELOAD_BGMUSIC(BGM_START);

	const char* EFFECT_LIST[] =
	{
		EFFECT_ADD,
		EFFECT_BOOM,
		EFFECT_CHANGE,
		EFFECT_CHANGE2,
		EFFECT_DELETE,
		EFFECT_NEXT,
		EFFECT_PAUSE,
		EFFECT_SOUNDOFF,
		EFFECT_SOUNDON,
		EFFECT_WALL,
	};

	for (int i = 0; i < 10; ++i)
	{
		PRELOAD_EFFECT(EFFECT_LIST[i]);
	}
}


vector<int>* CGeneralManager::GetAnimData(int iGameIndex, int iAnimIndex)
{
	int iIndex = iGameIndex * ANIM_NUM + iAnimIndex;
	return &m_mapGameAnim[iIndex];
}


//���ű�������
void CGeneralManager::PlayMusic(const char* strName, bool bLoop)
{
	if (m_bSoundOn)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(strName, bLoop);
	}
}

//������Ч
void CGeneralManager::PlayEffect(const char* strName)
{
	if (m_bSoundOn)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(strName);
	}
}


//��������״̬
void CGeneralManager::SetSoundState(bool bState)
{
	m_bSoundOn = bState;
	SET_BOOLVALUE("SOUND", m_bSoundOn);
}


//��ȡ����״̬
bool CGeneralManager::GetSoundState()
{
	return m_bSoundOn;
}


int CGeneralManager::GetHighScore(int iGameIdx)
{
	return m_mapHighScore[iGameIdx];
}


void CGeneralManager::SetHighScore(int iGameIdx, int iScore)
{
	int& iHighScore = m_mapHighScore[iGameIdx];
	if (iHighScore < iScore)
	{
		iHighScore = iScore;
	}
}


void CGeneralManager::SaveTetrisData(const bool(&arrState)[ROW_NUM][COLUMN_NUM])
{
	string strPath = FileUtils::getInstance()->getWritablePath() + "/record.txt";
	fstream oFile(strPath.c_str(), ios::out | ios::binary);
	if (!oFile.is_open())
	{
		TRACE("Open %s Error.", strPath.c_str());
		return;
	}

	for (int i = 0; i < ROW_NUM; ++i)
	{
		for (int j = 0; j < COLUMN_NUM; ++j)
		{
			oFile << arrState[i][j];
		}
	}

	oFile.close();
}


void CGeneralManager::LoadTetrisData(bool(&arrState)[ROW_NUM][COLUMN_NUM])
{
	string strPath = FileUtils::getInstance()->getWritablePath() + "/record.txt";
	TRACE("%s", strPath.c_str());

	fstream oFile(strPath.c_str(), ios::in | ios::binary);
	if (!oFile.is_open())
	{
		TRACE("Open %s Error.", strPath.c_str());
		return;
	}

	int iCount = 0;
	while (!oFile.eof())
	{
		char ch = '\0';
		oFile.get(ch);

		int iRowIdx = iCount / COLUMN_NUM;
		int iColIdx = iCount - iRowIdx * COLUMN_NUM;
		arrState[iRowIdx][iColIdx] = ch - '0';
		++iCount;
	}

	oFile.close();
}

