#include "stdafx.h"
#include "EffectMaker.h"

EffectMaker::EffectMaker()
{
}

EffectMaker::~EffectMaker()
{
}

HRESULT EffectMaker::init()
{
	return S_OK;
}

void EffectMaker::release()
{
}

void EffectMaker::update()
{
}

void EffectMaker::render()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		POINTFLOAT tempCenter = (*_viEffect).center;
		tempCenter.x -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		tempCenter.y -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	
		IMAGEMANAGER->findImage((*_viEffect).aniImgName)->aniRender(getMemDC(), tempCenter.x, tempCenter.y, (*_viEffect).ani);

		if ((*_viEffect).ani->getFramePos().x == 2506 && ((*_viEffect).type == EffectType::JUMP)		||
			(*_viEffect).ani->getFramePos().x == 3222 && ((*_viEffect).type == EffectType::DOUBLE_JUMP) ||
			(*_viEffect).ani->getFramePos().x == 3222 && ((*_viEffect).type == EffectType::DASH))
		{
			_viEffect = _vEffect.erase(_viEffect);
			break;
		}

		if ((*_viEffect).type == EffectType::THROW_HEAD)
		{
			if ((*_viEffect).aniName == "throw_Head_R_Effect" && (*_viEffect).ani->getFramePos().x == 800)
			{
				_viEffect = _vEffect.erase(_viEffect);
				break;
			}

			if ((*_viEffect).aniName == "throw_Head_L_Effect" && (*_viEffect).ani->getFramePos().x == 0)
			{
				_viEffect = _vEffect.erase(_viEffect);
				break;
			}

		}

	}
}

void EffectMaker::Create_Effect(string aniImgName, string aniName, EffectType type_V, float x, float y)
{
	// 새로운 이펙트 정보를 담을 변수를 만든다.
	EffectPosInfo	new_Effect;

	// 이펙트 타입을 저장한다.
	new_Effect.type = type_V;

	// 이펙트 이미지의 이름
	new_Effect.aniImgName = aniImgName;

	// 이펙트 애니메이션 키값
	new_Effect.aniName = aniName;

	// 애니메이션을 저장한다.
	new_Effect.ani = KEYANIMANAGER->findAnimation(aniName);
	new_Effect.ani->start();

	// 이펙트를 뿌릴 좌표를 저장한다.
	new_Effect.center.x = x - new_Effect.ani->getFrameWidth() / 2;
	new_Effect.center.y = y - new_Effect.ani->getFrameHeight() / 2;

	// 벡터에 저장한다.
	_vEffect.push_back(new_Effect);

}
