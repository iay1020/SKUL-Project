#pragma once

// ����Ʈ Ÿ��
enum class EffectType
{
	NONE,
	JUMP,
	DOUBLE_JUMP,
	DASH,
	THROW_HEAD

};

// ����Ʈ�� �Ѹ� ��ġ ���� ����ü
struct EffectPosInfo
{
	POINTFLOAT		center;			// ������ ������ ����
	animation*		ani;			// �ִϸ��̼��� ������ ����
	string			aniImgName;		// �ִϸ��̼� �̹����� �̸� ���� ����
	string			aniName;		// �ִϸ��̼� Ű��

	EffectType		type;			// ����Ʈ Ÿ��
};