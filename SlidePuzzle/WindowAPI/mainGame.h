#pragma once
#include "gameNode.h"

struct PUZZLE
{
	RECT rc;		//�����ǽ��� �� �׸�
	int num;		//�����ǽ��� �ڸ�

};

class mainGame : public gameNode
{
private:
	image* _bgImage;	//��׶��� �̹���
	image* _puzzleImg;	//���� �̹���
	image* _puzzleSmallImg;		//���� ���� �̹���
	int index;
	bool _spaceOn;
	int count;
	int randCount;
	RECT _rc[9]; //�ε����� ã�� ��

	PUZZLE _puzzle[9];

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void shuffle();



	mainGame() {}
	~mainGame() {}
};

