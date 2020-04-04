#pragma once
//=============================================================
//	## image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,  //���ҽ��� �ε�
		LOAD_FILE,			//���Ϸ� �ε�
		LOAD_EMPTY,			//���Ʈ������ �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD	resID;		//���ҽ� ID
		HDC		hMemDC;		//�޸� DC
		HBITMAP hBit;		//��Ʈ��
		HBITMAP hOBit;		//�õ��Ʈ��
		int		width;		//�̹��� ����ũ��
		int		height;		//�̹��� ����ũ��
		BYTE	loadType;	//�̹��� �ε�Ÿ��
		tagImage()			//������ = �ʱ�ȭ
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
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� �̸�
	BOOL			_isTrans;		//���� ���ٰų�?
	COLORREF		_transColor;	//���� ���� RGB���� (����Ÿ = RGB(255, 0, 255))

public:
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ� �ʱ�ȭ => ������
	HRESULT init(DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ => �ֻ��
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//����
	void release();

	//����(���ϴ� ��ǥ�� �������Ѷ�, �Ϲ������� ��Ʈ�� LT��ǥ�� �̹����� ���δ�)
	void render(HDC hdc, int destX = 0, int destY = 0);
	//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
	void render(HDC hdc, int destX, int destY, 
		int sourX, int sourY, 
		int sourWidth, int sourHeight);


	//DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
};

