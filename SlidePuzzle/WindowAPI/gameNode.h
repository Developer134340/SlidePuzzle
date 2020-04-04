#pragma once
#include "image.h"

class gameNode
{
private:
	image* _backBuffer;		//����� �̹���
	void setBackBuffer();	//����� �����ϱ�

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	//����� �̹��� ���
	image* getBackBuffer() { return _backBuffer; }

	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};
