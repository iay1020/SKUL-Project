#pragma once

// 이펙트 타입
enum class EffectType
{
	NONE,
	JUMP,
	DOUBLE_JUMP,
	DASH,
	THROW_HEAD

};

// 이펙트를 뿌릴 위치 정보 구조체
struct EffectPosInfo
{
	POINTFLOAT		center;			// 중점을 저장할 변수
	animation*		ani;			// 애니메이션을 저장할 변수
	string			aniImgName;		// 애니메이션 이미지의 이름 저장 변수
	string			aniName;		// 애니메이션 키값

	EffectType		type;			// 이펙트 타입
};