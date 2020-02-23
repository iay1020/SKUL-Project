#pragma once
#include "gameNode.h"

class EffectMaker : public gameNode
{
private:
	vector<EffectPosInfo>				_vEffect;		// 이펙트 저장 벡터
	vector<EffectPosInfo>::iterator		_viEffect;		// 이펙트 벡터 반복자

public:
	EffectMaker();
	~EffectMaker();

	HRESULT init();
	void release();
	void update();
	void render();

	// 이펙트를 만들어준다. (매개변수 : 애니메이션 이미지의 이름, 애니메이션 이름, 뿌려질 중점 x, 뿌려질 중점 y)
	void Create_Effect(string aniImgName, string aniName, EffectType type_V, float x, float y);

};

