#pragma once
#include "image.h"

class gameNode
{
private:
	image* _backBuffer;		//백버퍼 이미지
	void setBackBuffer();	//백버퍼 세팅하기

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	//백버퍼 이미지 얻기
	image* getBackBuffer() { return _backBuffer; }

	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};

