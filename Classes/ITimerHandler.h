#pragma once

// ��ʱ���ص�
class ITimerHandler
{
public:
	virtual void OnTimer(int nTimerID) = 0;
};
