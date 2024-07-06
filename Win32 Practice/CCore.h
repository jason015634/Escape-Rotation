#pragma once


// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능

class CTexture;

class CCore
{

	SINGLE(CCore);
	//static CCore* GetInst()
	//{
	//	static CCore core; //정적 변수는 한번만 선언됨.
	//	return &core; //주소를 주면 다른 곳에서도 접근이 가능하다.
	//}

private:
	HWND m_hWnd;		  // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC;			  // 메인 윈도우 DC

	// 배경 > 오브젝트 > UI 순으로 memDC에 겹쳐서 m_hDC로 전송
	// 배경 memDC -> Scene의 텍스쳐로 사용

	// Object Rendering memDC
	HBITMAP m_hObjBit;
	HDC m_hObjDC;

	// 회전 memDC : ObjMemDC를 복사해서 회전
	HBITMAP m_hRotateBit;
	HDC m_hRotateDC;

	// UI memDC
	HBITMAP m_hUIBit;
	HDC m_hUIDC;

	// 회전용 여분 memDC -> Scene으로 이동

	// 통합 memDC
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