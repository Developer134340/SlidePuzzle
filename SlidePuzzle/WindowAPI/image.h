#pragma once
//=============================================================
//	## image ## (앞으로 계속 업데이트 된다)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,  //리소스로 로딩
		LOAD_FILE,			//파일로 로딩
		LOAD_EMPTY,			//빈비트맵으로 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD	resID;		//리소스 ID
		HDC		hMemDC;		//메모리 DC
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드비트맵
		int		width;		//이미지 가로크기
		int		height;		//이미지 세로크기
		BYTE	loadType;	//이미지 로드타입
		tagImage()			//생성자 = 초기화
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_EMPTY;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 없앨거냐?
	COLORREF		_transColor;	//배경색 없앨 RGB색상 (마젠타 = RGB(255, 0, 255))

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스 초기화 => 사용안함
	HRESULT init(DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화 => 주사용
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//해제
	void release();

	//렌더(원하는 좌표에 렌더시켜라, 일반적으로 렉트의 LT좌표에 이미지를 붙인다)
	void render(HDC hdc, int destX = 0, int destY = 0);
	//렌더(원하는 좌표에 이미지를 잘라서 붙이기)
	void render(HDC hdc, int destX, int destY, 
		int sourX, int sourY, 
		int sourWidth, int sourHeight);


	//DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
};

