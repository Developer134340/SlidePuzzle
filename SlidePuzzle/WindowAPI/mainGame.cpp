#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//�̰����� �ʱ�ȭ�� �Ѵ�

	index = 8;
	randCount = 0;

	count = 0;


	//�̹��� �ʱ�ȭ
	_bgImage = new image;
	_bgImage->init("����.bmp", WINSIZEX, WINSIZEY);

	_puzzleImg = new image;
	_puzzleImg->init("���簢���.bmp", 600, 600);

	_puzzleSmallImg = new image;
	_puzzleSmallImg->init("���簢���2.bmp", 300, 300);

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
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�

	//�̹��� ����
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_puzzleImg);
	SAFE_DELETE(_puzzleSmallImg);
}


//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�
	
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
//	## ���� ## render(HDC hdc)
//=============================================================
void mainGame::render(HDC hdc)
{
	//����� �������� (�̰� ������ �α�)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	//PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	//�̰����� WM_PAINT���� �ߴ����� ó���ϸ� �ȴ�

	//��׶��� ����
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
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
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
