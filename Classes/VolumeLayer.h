#pragma once
#include "BGGlobal.h"

class CBarrierLayer;

class CVolumeLayer : public Layer
{
public:
	CVolumeLayer();
	~CVolumeLayer();

	//��ʼ��
	virtual bool init();

	//����λ��
	void updatePos();

	CREATE_FUNC(CVolumeLayer);

private:
	//�������仯
	void onSliderValueChanged(Ref* pSender, Control::EventType enEvent);

	//��ť����
	void onButtonEvent(Ref* pSender);

private:
	enum
	{
		DEFAULT_HEIGHT = 150,

		LABEL_FONT_SIZE = 24,
		VALUE_FONT_SIZE = 24,

		X_PADDING = 25,
	};

private:
	//������
	ControlSlider* m_pBGMSlider;
	ControlSlider* m_pEffectSlider;

	//��ǰֵLabel
	Label* m_pBGMVolume;
	Label* m_pEffetVolume;

	//Label
	Label* m_pBGMLabel;
	Label* m_pEffectLabel;

	//������
	Sprite*	m_pBGSprite;

	//�رհ�ť
	MenuItemSprite* m_pCloseMenuItem;

	//�赲��
	CBarrierLayer*	m_pBarrierLayer;
};

