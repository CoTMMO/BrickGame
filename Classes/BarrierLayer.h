#pragma once
#include "BGGlobal.h"

class CBarrierLayer : public Layer
{
public:
	CBarrierLayer();
	~CBarrierLayer();

	virtual bool init();

	//���ô���������
	void SetListenerEnabled(bool bEnabledFlag);

	CREATE_FUNC(CBarrierLayer);

private:
	//Listener
	EventListenerTouchOneByOne* m_pListener;
};