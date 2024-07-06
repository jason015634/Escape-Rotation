// Win32 Practice.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "CCore.h"
#include "framework.h"
#include "Win32 Practice.h"
#include <wingdi.h>


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다: 아래에서 쓸 함수들을 미리 선언한 것.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//연보라색으로 나타내어지는 것들은 무엇인가? -> SAL 주석
//이것들은 지역변수 앞에 의미를 적어주는 것, 주석과 같은 역할을 한다고 함 ex) _In_은 데이터가 이 변수에 입력된다는 의미. _In_opt_는 부가적인 데이터라는 뜻
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,//프로세스가 시작되는 메모리 주소를 의미하는 변수
	_In_opt_ HINSTANCE hPrevInstance,//이 프로세스가 실행되기 전에 실행되었던 프로세스의 메모리 주소(이것은 옛날 윈도우의 잔재, 현재는 의미 없는 변수로 항상 0을 반환한다고 함)
	_In_ LPWSTR    lpCmdLine,//추가 문자열 옵션
	_In_ int       nCmdShow)//기본 애플리케이션 창이 최소화, 최대화 또는 정상적으로 표시되는지 여부를 나타내는 변수
{
	//메모리 누수 찾기
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(205);

	UNREFERENCED_PARAMETER(hPrevInstance);//괄호안에 있는 것이 쓰이지 않는다는 걸 나타내는 메크로 실제 컴파일러에서는 무시됨.
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);//리소스 파일의 String Table에 있는 문자열을 불러와서 초기화 해줌 이 줄은 윈도우 타이틀을 초기화해줌
	LoadStringW(hInstance, IDC_WIN32PRACTICE, szWindowClass, MAX_LOADSTRING);//윈도우 클래스 이름을 초기화 해주는 코드, 윈도우 클래스 이름은 윈도우를 생성하거나 검색할 때 사용.
	MyRegisterClass(hInstance);//WNDCLASSEX를 초기화한 후 RegisterClassEx()함수를 호출하여 윈도우 클래스를 등록

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))//윈도우를 생성하는 코드(모든 프로세스가 윈도우를 생성하는 것은 아님 ex)백그라운드 프로그램들)
	{
		return FALSE;//윈도우 생성에 실패하면 false를 리턴하여 프로그램을 종료 시킴
	}

	// Core 초기화
	if (FAILED(CCore::GetInst()->init(hWnd, POINT{ 1920, 1080 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

		return FALSE;
	}
	//단축키 테이블 정보 로딩
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PRACTICE));//리소스 파일의 Accelerator에 단축키를 등록할 수 있음

	MSG msg;//MSG 구조체 선언
	//hwnd: 메시지를 수신하는 윈도우의 핸들. 필수!!
	//message : 수신된 메시지의 종류(ex.WM_CREATE, WM_DESTROY, WM_PAINT 등). 필수!!
	//wParam : 메시지와 함께 전달되는 부가 정보1(메시지 종류에 따라 다르게 사용됨)     
	//lParam : 메시지와 함께 전달되는 부가 정보2(메시지 종류에 따라 다르게 사용됨)
	//time : 메시지를 보낸 시각(운영체제가 자동으로 설정함)
	//pt : 메시지를 보낸 지점의 좌표(운영체제가 자동으로 설정함)
	//lPrivate : 운영체제가 내부적으로 사용하는 멤버


	//PeekMessage
	//메시지 유무와 관계없이 반환
	//메시지큐에서 메시지를 확인한 경우 true, 메시지큐에 메시지가 없는 경우 false를 반환
	//비동기 방식을 쓸 경우 윈도우 포커싱이 안되어있어도 메시지를 받아옴 -> 예외처리 해줘야 함.
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;


			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			CCore::GetInst()->progress();
		}
	}

	return (int)msg.wParam;//WM_QUIT메시지를 받았을 때, 종료 코드를 반환
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);//구조체의 크기를 지정

	wcex.style = CS_HREDRAW | CS_VREDRAW;//윈도우 클래스의 스타일을 지정
	//CS_VREDRAW: 윈도우의 세로 크기가 변경되었을 때 윈도우 내부의 컨텐츠를 다시 그림.
	//CS_HREDRAW : 윈도우의 가로 크기가 변경되었을 때 윈도우 내부의 컨텐츠를 다시 그림.
	//CS_DBLCLKS : 더블 클릭 이벤트를 처리.
	//CS_OWNDC : 윈도우 클래스가 각 윈도우에 대해 고유한 디바이스 컨텍스트를 생성.
	//CS_CLASSDC : 윈도우 클래스에 대해 공유 디바이스 컨텍스트 생성.
	//CS_PARENTDC : 부모 윈도우의 디바이스 컨텍스트 사용.
	//CS_SAVEBITS : 윈도우가 숨겨진 상태에서도 내용을 그리고 있을 때, 이전에 그렸던 내용을 저장.
	wcex.lpfnWndProc = WndProc;//WNDPROC 윈도우 프로시저 함수의 주소를 지정합니다.(함수 포인터 사용)
	wcex.cbClsExtra = 0;//윈도우 클래스의 여분 바이트 수를 지정
	wcex.cbWndExtra = 0;//개별 윈도우의 여분 바이트 수 지정
	wcex.hInstance = hInstance;//윈도우 클래스를 등록한 모듈의 인스턴스 핸들을 지정.
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PRACTICE));//클래스의 아이콘 지정
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//클래스의 커서 지정
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);//클래스의 배경 브러시 핸들을 지정
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_WIN32PRACTICE);//클래스와 관련된 메뉴 이름을 지정.(리소스 파일의 IDC_WIN32PRACTICE에서 메뉴 생성 및 수정가능)
	wcex.lpszClassName = szWindowClass;//윈도우 클래스의 이름을 지정.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//클래스의 작은 아이콘을 지정

	return RegisterClassExW(&wcex);//클래스 등록
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// 제목표시줄 지우기
	hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

 	/*hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
 		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);*/
	

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
				//모달 방식으로 윈도우를 켤 수 있는 함수
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_MENU_TILE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
