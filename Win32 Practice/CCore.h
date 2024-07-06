#pragma once


// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����

class CTexture;

class CCore
{

	SINGLE(CCore);
	//static CCore* GetInst()
	//{
	//	static CCore core; //���� ������ �ѹ��� �����.
	//	return &core; //�ּҸ� �ָ� �ٸ� �������� ������ �����ϴ�.
	//}

private:
	HWND m_hWnd;		  // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC;			  // ���� ������ DC

	// ��� > ������Ʈ > UI ������ memDC�� ���ļ� m_hDC�� ����
	// ��� memDC -> Scene�� �ؽ��ķ� ���

	// Object Rendering memDC
	HBITMAP m_hObjBit;
	HDC m_hObjDC;

	// ȸ�� memDC : ObjMemDC�� �����ؼ� ȸ��
	HBITMAP m_hRotateBit;
	HDC m_hRotateDC;

	// UI memDC
	HBITMAP m_hUIBit;
	HDC m_hUIDC;

	// ȸ���� ���� memDC -> Scene���� �̵�

	// ���� memDC
	HBITMAP m_hBit;
	HDC m_hMemDC;


	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	int m_ckRotate;
	Vec2 m_playerPosition;

public:
	int init(HWND _hWnd, POINT _ptResolution);  
	void progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetObjDC() { return m_hObjDC; }
	HDC GetRotateDC() { return m_hRotateDC; }
	HDC GetUIDC() { return m_hUIDC; }
	HDC GetMemDC() { return m_hMemDC; }

	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

};
extern int index;