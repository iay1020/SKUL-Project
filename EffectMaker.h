#pragma once
#include "gameNode.h"

class EffectMaker : public gameNode
{
private:
	vector<EffectPosInfo>				_vEffect;		// ����Ʈ ���� ����
	vector<EffectPosInfo>::iterator		_viEffect;		// ����Ʈ ���� �ݺ���

public:
	EffectMaker();
	~EffectMaker();

	HRESULT init();
	void release();
	void update();
	void render();

	// ����Ʈ�� ������ش�. (�Ű����� : �ִϸ��̼� �̹����� �̸�, �ִϸ��̼� �̸�, �ѷ��� ���� x, �ѷ��� ���� y)
	void Create_Effect(string aniImgName, string aniName, EffectType type_V, float x, float y);

};

