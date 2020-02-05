#pragma once
#include "stdafx.h"

// unsigned int Ÿ���� ������ 2�� ����
struct tag_U_INT
{
	unsigned int x;
	unsigned int y;
};

// ��� �ϱ� ���ϴ� Ÿ���� �ε����� ��Ƶд�.
class tag_FindTile
{
protected:
	tag_U_INT start_Index;		// ���� �ε���
	tag_U_INT end_Index;		// ������ �ε���
	tag_U_INT range;			// ��� �ϱ� ���ϴ� ���� 


public:
	tag_FindTile() {};
	~tag_FindTile() {};

	void init()
	{
		start_Index.x = start_Index.y = 0;
		end_Index.x = end_Index.y = 0;
		range.x = range.y = 0;

	}

	// �ε����� ã�´�. (��ǥ�� �޾ƿͼ� �� ��ǥ�� ��ġ�� �ε����� ���Ѵ�.)
	void Find_startIndex(float x, float y)
	{
		start_Index.x = x / TILE_SIZE_X;
		start_Index.y = y / TILE_SIZE_Y; 

		//cout << "start x : " << start_Index.x << endl;
		//cout << "start y : " << start_Index.y << endl;
		//cout << "=============================" << endl;
	}

	// �ε����� ã�´�. (��ǥ�� �޾ƿͼ� �� ��ǥ�� ��ġ�� �ε����� ���Ѵ�.)
	void Find_endIndex(float x, float y)
	{
		end_Index.x = (x + WINSIZEX) / TILE_SIZE_X;
		end_Index.y = (y + WINSIZEY) / TILE_SIZE_Y + 1;	// ȭ�� �Ʒ� �� ��¦ �� ������ ����ϱ� ���� ����ó��

		//cout << "end x : " << end_Index.x << endl;
		//cout << "end y : " << end_Index.y << endl;
		//cout << "=============================" << endl;
	}

	// ã�� ���ϴ� Ÿ���� ������ ���Ѵ�.
	void Find_Tile_Range()
	{
		range.x = unsigned int(end_Index.x - start_Index.x);	// ã�ƾ� �ϴ� x�� ����
		range.y = unsigned int(end_Index.y - start_Index.y);	// ã�ƾ� �ϴ� y�� ����

		//cout << "range x : " << range.x << endl;
		//cout << "range y : " << range.y << endl;
		//cout << "=============================" << endl;
	}

	// Ÿ���� ������ �޾ƿ´�.
	tag_U_INT get_Start_Index() { return start_Index; }		// ��ŸƮ �ε����� �޾ƿ´�.
	tag_U_INT get_End_Index() { return end_Index; }			// ���� �ε����� �޾ƿ´�.
	tag_U_INT get_Tile_Range() { return range; }			// ��� Ÿ�� ������ �޾ƿ´�.

};
