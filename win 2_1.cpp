#include <Windows.h>
#include <wchar.h>

int l = 0, r = 0, m = 0;
//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Дз 2_1");

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow) {

	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl; //структура типа Окно

	//1.Определить класс окна
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	//2.Зарегистрировать окно
	if (!RegisterClassEx(&wcl))
		return 0;
	//3.Содать окно
	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("Количество нажатий - ПКМ: 0, Колёсико: 0, ЛКМ: 0"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL
		);

	//4.Отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//5.Запустить цикли обработки сообщений
	while (GetMessage(&lpMsg, hWnd, 0, 0)) {
	//	int i = 0;
	//	if (i == 3)
	//		break;
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	//	++i;
	}
	return lpMsg.wParam;
}

LPARAM CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	TCHAR str[50];
	switch (uMessage) {
	case WM_LBUTTONUP:
		wsprintf(str, TEXT("Количество нажатий - ПКМ: %d, Колёсико: %d, ЛКМ: %d"), r, m, ++l);
		SetWindowText(hWnd, str);
		break;
	case WM_RBUTTONUP:
		wsprintf(str, TEXT("Количество нажатий - ПКМ: %d, Колёсико: %d, ЛКМ: %d"), ++r, m, l);
		SetWindowText(hWnd, str);
		break;
	case WM_MBUTTONUP:
		wsprintf(str, TEXT("Количество нажатий - ПКМ: %d, Колёсико: %d, ЛКМ: %d"), r, ++m, l);
		SetWindowText(hWnd, str);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
