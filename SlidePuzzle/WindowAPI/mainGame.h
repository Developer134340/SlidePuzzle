#pragma once
#include "gameNode.h"

struct PUZZLE
{
	RECT rc;		//퍼즐피스가 들어갈 네모
	int num;		//퍼즐피스의 자리

};

class mainGame : public gameNode
{
private:
	image* _bgImage;	//백그라운드 이미지
	image* _puzzleImg;	//퍼즐 이미지
	image* _puzzleSmallImg;		//퍼즐 작은 이미지
	int index;
	bool _spaceOn;
	int count;
	int randCount;
	RECT _rc[9]; //인덱스로 찾을 값

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

