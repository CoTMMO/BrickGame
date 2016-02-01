#include "BGGlobal.h"

const bool BOOM_STATE[4][4] =
{
	{ true, false, false, true },
	{ false, true, true, false },
	{ false, true, true, false },
	{ true, false, false, true },
};

const char* BGM_START = "Sounds/bgm.mp3";

const char* EFFECT_ADD = "Sounds/add.mp3";
const char* EFFECT_BOOM = "Sounds/boom.mp3";
const char* EFFECT_CHANGE = "Sounds/change.mp3";
const char* EFFECT_CHANGE2 = "Sounds/change2.mp3";
const char* EFFECT_DELETE = "Sounds/delete.mp3";
const char* EFFECT_NEXT = "Sounds/next.mp3";
const char* EFFECT_PAUSE = "Sounds/pause.mp3";
const char* EFFECT_SOUNDOFF = "Sounds/sndoff.mp3";
const char* EFFECT_SOUNDON = "Sounds/sndon.mp3";
const char* EFFECT_WALL = "Sounds/wall.mp3";


int Random(int iStart, int iEnd, int iStep)
{
	//�����һ�λ�ȡ�������ʱ��ͱ�����ͬ�������������
	bool bSameTime = true;
	static time_t stLastTime = 0;
	time_t tCurTime = time(NULL);
	if (difftime(tCurTime, stLastTime) > 0)
	{
		srand((unsigned)time(NULL));
		stLastTime = tCurTime;
		
		bSameTime = false;
	}

	vector<int> vecNum;
	for (int i = iStart < iEnd ? iStart : iEnd; i < (iEnd > iStart ? iEnd : iStart); i += iStep)
	{
		vecNum.push_back(i);
	}

	random_shuffle(vecNum.begin(), vecNum.end());
	
	//���ؽ�����������ͬʱ�䣬�򷵻ز�ͬλ�õ�ֵ
	int iIndex = 0;
	if (bSameTime)
	{
		iIndex = rand() % vecNum.size();
	}
	return vecNum[iIndex];
}
