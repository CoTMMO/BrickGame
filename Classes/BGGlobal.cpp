#include "BGGlobal.h"

int Random(int iStart, int iEnd, int iStep)
{
	//�����һ�λ�ȡ�������ʱ��ͱ�����ͬ�������������
	static time_t stLastTime = 0;
	time_t tCurTime = time(NULL);
	if (difftime(tCurTime, stLastTime) > 0)
	{
		srand((unsigned)time(NULL));
		stLastTime = tCurTime;
	}

	vector<int> vecNum;
	for (int i = iStart < iEnd ? iStart : iEnd; i < (iEnd > iStart ? iEnd : iStart); i += iStep)
	{
		vecNum.push_back(i);
	}

	random_shuffle(vecNum.begin(), vecNum.end());
	
	//���ص�һ��
	vector<int>::iterator pIter = vecNum.begin();
	return *pIter;
}
