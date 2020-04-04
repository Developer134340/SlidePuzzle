#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//이곳에서 초기화를 한다

	index = 8;
	randCount = 0;

	count = 0;


	//이미지 초기화
	_bgImage = new image;
	_bgImage->init("벽돌.bmp", WINSIZEX, WINSIZEY);

	_puzzleImg = new image;
	_puzzleImg->init("정사각배경.bmp", 600, 600);

	_puzzleSmallImg = new image;
	_puzzleSmallImg->init("정사각배경2.bmp", 300, 300);

	_spaceOn = false;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_rc[i*3 + j] = RectMake(100 + j * 200, 100 + i * 200, 200, 200);
			_puzzle[i * 3 + j].num = i * 3 + j;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		_puzzle[i].rc = _rc[i];
	}


	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다

	//이미지 해제
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_puzzleImg);
	SAFE_DELETE(_puzzleSmallImg);
}


//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	
	count++;

	if(KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_spaceOn = true;
	}

	if (_spaceOn == true)
	{
		if (count % 5 == 0)
		{
		this->shuffle();
		randCount++;
		}

	}

	if (randCount >= 20 && _puzzle[index].num == 8)
	{
		_spaceOn = false;
	}

	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 9; i++)
		{
			if (PtInRect(&_puzzle[i].rc, _ptMouse))
			{
				if (_puzzle[index].num -1 == _puzzle[i].num)
				{
					if (_puzzle[index].num % 3 == 0) break;
					PUZZLE temp = _puzzle[i];
					_puzzle[i] = _puzzle[index];
					_puzzle[index] = temp;
					break;
				}
				else if (_puzzle[index].num + 1 == _puzzle[i].num)
				{
					if (_puzzle[index].num % 3 == 2) break;
					PUZZLE temp = _puzzle[i];
					_puzzle[i] = _puzzle[index];
					_puzzle[index] = temp;
					break;
				}
				else if (_puzzle[index].num - 3 == _puzzle[i].num)
				{
					if (_puzzle[index].num < 3) break;
					PUZZLE temp = _puzzle[i];
					_puzzle[i] = _puzzle[index];
					_puzzle[index] = temp;
					break;
				}
				else if (_puzzle[index].num + 3 == _puzzle[i].num)
				{
					if (_puzzle[index].num > 5) break;
					PUZZLE temp = _puzzle[i];
					_puzzle[i] = _puzzle[index];
					_puzzle[index] = temp;
					break;
				}

			}
		}
	}



	
	
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void mainGame::render(HDC hdc)
{
	//백버퍼 가져오기 (이건 렌더에 두기)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	//PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다

	//백그라운드 렌더
	_bgImage->render(memDC);

	for (int i = 0; i < 9; i++)
	{
		Rectangle(memDC, _rc[i]);
	}

	_puzzleSmallImg->render(memDC, 850, 250);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{	
			if (i*3 + j == index) continue;
			_puzzleImg->render(memDC, _puzzle[i * 3 + j].rc.left, _puzzle[i * 3 + j].rc.top, j*200, i*200, 200, 200);
		}
	}

	

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(hdc);
}

void mainGame::shuffle()
{
	int randNum = RND->range(4);
	switch (randNum)
	{
	case 0:
		if (_puzzle[index].num % 3 == 0) break;

		for (int i = 0; i < 9; i++)
		{
			if (_puzzle[i].num == _puzzle[index].num - 1)
			{
				PUZZLE temp = _puzzle[i];
				_puzzle[i] = _puzzle[index];
				_puzzle[index] = temp;
				break;
			}
		}
		break;
	case 1:
		if (_puzzle[index].num % 3 == 2) break;
		for (int i = 0; i < 9; i++)
		{
			if (_puzzle[i].num == _puzzle[index].num + 1)
			{
				PUZZLE temp = _puzzle[i];
				_puzzle[i] = _puzzle[index];
				_puzzle[index] = temp;
				break;
			}
		}
		break;
	case 2:
		if (_puzzle[index].num < 3) break;
		for (int i = 0; i < 9; i++)
		{
			if (_puzzle[i].num == _puzzle[index].num - 3)
			{
				PUZZLE temp = _puzzle[i];
				_puzzle[i] = _puzzle[index];
				_puzzle[index] = temp;
				break;
			}
		}
		break;
	case 3:
		if (_puzzle[index].num > 5) break;
		for (int i = 0; i < 9; i++)
		{
			if (_puzzle[i].num == _puzzle[index].num + 3)
			{
				PUZZLE temp = _puzzle[i];
				_puzzle[i] = _puzzle[index];
				_puzzle[index] = temp;
				break;
			}
		}
		break;
	}
}
