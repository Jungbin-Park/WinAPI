#include "pch.h"

#include "framework.h"
#include "GameClient.h"

#include "Resource.h"

#include "CEngine.h"


// 전역 변수:
HINSTANCE   hInst;                       // 현재 인스턴스입니다.
HWND        g_hWnd;                     // 메인 윈도우 핸들

wchar_t szTitle[100];                  // 제목 표시줄 텍스트입니다.
wchar_t szWindowClass[100];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// SAL : 주석 언어
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(215);

    // 윈도우 클래스 등록
    MyRegisterClass(hInstance);
        
    // 윈도우 생성
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
     
    // CreateWindow 윈도우 생성
    // 반환값은 윈도우 핸들(ID) 값,
    //  커널 오브젝트 : OS 가 관리하는 오브젝트, 직접적인 접근이 불가능하고 ID 값을 통해서 제어함
    g_hWnd = CreateWindowW(L"Window Class Key", L"My Game", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
        return FALSE;    

    // 윈도우를 화면에 보여줄지 말지 설정
    ShowWindow(g_hWnd, true);
    UpdateWindow(g_hWnd);
    
    // Engine 초기화
    if (FAILED(CEngine::GetInst()->init(g_hWnd, POINT{1280, 768})))
    {
        // Engine 초기화 실패 ==> 프로그램 종료
        MessageBox(nullptr, L"엔진 초기화 실패", L"에러 발생", MB_OK);        
        return 0;
    }

    // 리소스(단축키 테이블 핸들 얻기)
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMECLIENT));

    // 메세지 루프
    // 메세지 정보를 받을 구조체 변수
    MSG msg;    
      
	while (true)
	{
		// Peek 엿보다
		// 메세지가 있던 없던, 리턴된다.
		// 메세지가 있었으면 true, 메세지가 없었으면 false
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 꺼내온 메세지가 WM_QUIT 이면 프로그램 종료
			if (msg.message == WM_QUIT)
				break;

			// 꺼내온 메세지 처리
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// 메세지가 큐에 없을 때에는 게임 코드 실행
            CEngine::GetInst()->progress();
		}
	}

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMECLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMECLIENT);
    wcex.lpszClassName  = L"Window Class Key";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


// CallBack
// 함수의 주소를 알려줘서, 특정 상황(조건) 이 맞으면 알려준 함수가 호출되는 구조

// 각 윈도우들은 해당 윈도우에 메세지가 발생했을 때 처리를 해줄 프로시저함수를 등록해야한다.
// 메인 윈도우는 MyRegisterClass 함수 안에서 윈도우 정보를 만들때 호출함 함수의 주소를 등록해둠
// 도움말 윈도우는 다이얼로그 형태로서, DialogBox 함수를 호출할때 사용할 
// 프로시저 함수의 주소를 입력으로 넣어줬다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        ShowWindow(g_hWnd, false);
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                // 윈도우 생성 함수
                // 
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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

    case WM_TIMER:
    {
        int a = 0;
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
