#include <windows.h>
#include <tchar.h>
#include <ctime>

void itowa(int val, TCHAR* &dest, int _Radix) {
	char* temp = new char[5];
	itoa(val, temp, 10);
	int iLength = mbstowcs(NULL, temp, 0);
	if (dest) {
		delete[] dest;
	}
	dest = new TCHAR[iLength + 1];
	mbstowcs(dest, temp, iLength + 1);
	delete[] temp;
}

// прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");   /* Имя класса окна */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	// 1. Определение класса окна
	wcl.cbSize = sizeof(wcl);   // размер структуры WNDCLASSEX
	// Перерисовать всё окно, если изменён размер по горизонтали или по вертикали
	wcl.style = CS_HREDRAW | CS_VREDRAW;    // CS (Class Style) - стиль класса окна
	wcl.lpfnWndProc = WindowProc;   // адрес оконной процедуры
	wcl.cbClsExtra = 0;     // используется Windows 
	wcl.cbWndExtra = 0;    // используется Windows 
	wcl.hInstance = hInst;  // дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);    // загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // загрузка стандартного курсора    
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // заполнение окна белым цветом
	wcl.lpszMenuName = NULL;    // приложение не содержит меню
	wcl.lpszClassName = szClassWindow;  // имя класса окна
	wcl.hIconSm = NULL; // отсутствие маленькой иконки для связи с классом окна

	// 2. Регистрация класса окна
	if (!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход

	// 3. Создание окна
	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,      // расширенный стиль окна
		szClassWindow,  //имя класса окна
		TEXT("Каркас Windows приложения"), // заголовок окна
		WS_OVERLAPPEDWINDOW,                // стиль окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню, кнопки развёртывания и свёртывания окна  */
		CW_USEDEFAULT,  // х-координата левого верхнего угла окна
		CW_USEDEFAULT,  // y-координата левого верхнего угла окна
		CW_USEDEFAULT,  // ширина окна
		CW_USEDEFAULT,  // высота окна
		NULL,           // дескриптор родительского окна
		NULL,           // дескриптор меню окна
		hInst,      // идентификатор приложения, создавшего окно
		NULL);      // указатель на область данных приложения

	// 4. Отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // перерисовка окна
	
	
	int times = 0;
	while (1) {
		srand(unsigned int(time(NULL)));
		int num = rand() % 101;
		char* temp = new char[5];
		itoa(num, temp, 10);
		strcat(temp, "?");
		int iLength = mbstowcs(NULL, temp, 0);
		TCHAR* wszUserDigit = new TCHAR[iLength + 1];
		mbstowcs(wszUserDigit, temp, iLength + 1);
		TCHAR* temp2 = TEXT("Ваше число: ");
		TCHAR* wszUserAnswer = new TCHAR[wcslen(temp2) + 1];
		wcscpy(wszUserAnswer, temp2);
		_tcscat(wszUserAnswer, wszUserDigit);

		int res = MessageBox(
			hWnd,
			wszUserAnswer,
			TEXT("Число"),
			MB_YESNO | MB_ICONQUESTION);
		if (res == IDYES) {
			TCHAR* wszTimes = new TCHAR[5];
			itowa(times, wszTimes, 10);
			MessageBox(
				hWnd,
				wszTimes,
				TEXT("Потраченные попытки"),
				MB_OK | MB_ICONINFORMATION
				);

			if(MessageBox(
				hWnd,
				TEXT("Вы хотите сыграть ещё раз"),
				TEXT("Конец игры"),
				MB_YESNO | MB_ICONQUESTION
				) == IDNO)
				break;
			else {
				times = 0;
			}
		}
		else ++times;
		delete[] wszUserDigit;
	}

	// 5. Запуск цикла обработки сообщений
	while (GetMessage(&lpMsg, NULL, 0, 0)) // получение очередного сообщения из очереди сообщений
	{
		TranslateMessage(&lpMsg);   // трансляция сообщения
		DispatchMessage(&lpMsg);    // диспетчеризация сообщений
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	int result;
	switch (uMessage)
	{
	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0); // посылка сообщения WM_QUIT
		break;
	default:
		// все сообщения, которые не обрабатываются в данной оконной функции 
		// направляются обратно Windows на обработку по умолчанию
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
