#include<windows.h>

// прототип оконной функции
LRESULT CALLBACK 
DepartComTechWndProc(
			HWND, 
			UINT, 
			UINT, 
			LONG
		);

// описание функции WinMain - точки входа в программу
int __stdcall 
WinMain(
		HINSTANCE hInstance, 
		HINSTANCE,
		LPSTR lpszCmdParam, 
		int nCmdShow
	){


	// структура с характеристиками создаваемого класса
	WNDCLASS WndClass; 

	HWND hWnd; // дескриптор создаваемого окна

	MSG Msg; // структура, описывающая сообщение

	// инициализация имени класса как строки
	char szClassName[] = "DepartComTech";

	// заполнение структуры типа WNDCLASS

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = DepartComTechWndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(
					NULL, 
					IDI_APPLICATION
				);
	WndClass.hCursor = LoadCursor(
					NULL,
					IDC_ARROW
				);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szClassName;

	// регистрация создаваемого класса и выдача сообщения в случае
	// невозможности регистрации

	if (!RegisterClass(&WndClass)){

		MessageBox(
				NULL,
				"Cannot register class",
				"Error",
				MB_OK
			);

		return 0;

	}

	// создание окна зарегистрированного класса

	hWnd = CreateWindow(
				szClassName,
				"First Example",
				WS_OVERLAPPEDWINDOW, 
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				NULL,
				NULL,
				hInstance,
				NULL
			);

	// выдача сообщения в случае невозможности создания окна

	if(!hWnd){

		MessageBox(
				NULL,
				"Cannot create window",
				"Error",
				MB_OK
			);

		return 0;

	}

	// отображение окна на экране

	ShowWindow(
			hWnd,
			nCmdShow
		);

	// посылка оконной функции сообщения WM_PAINT с требованием
	// перерисовать рабочую область окна

	UpdateWindow(hWnd);

	// цикл обработки сообщений
	// выбор сообщений из очереди функцией GetMessage

	while(
			GetMessage(
					&Msg,
					NULL,
					0,
					0
				)
		){


		// преобразование сообщения к одному стилю обработки

		TranslateMessage(&Msg);

		// передача сообщения в оконную функцию

		DispatchMessage(&Msg);
	}

	// возврат дополнительной информации о сообщении

	return Msg.wParam;

}

LRESULT CALLBACK 
DepartComTechWndProc(
			HWND hWnd,
			UINT Message, 
			UINT wParam,
			LONG lParam
		){

	// дескриптор контекста устройства
	HDC hDC;

	// характеристики области рисования
	PAINTSTRUCT PaintStruct;

	// определение области рисования
	RECT Rect;

	// выбор нужной последовательности обработки для
	// конкретного сообщения
	switch(Message){

		case WM_PAINT:

			// обработка сообщения о перерисовке рабочей зоны окна
			// получение дескриптора устройства
			hDC = BeginPaint(
						hWnd,
						&PaintStruct
					);

			// определение клиентской области для рисования,
			// в структуре Rect первые две координаты равны 0, а -
			// третья и четвертая - значения ширины и высоты окна
			GetClientRect(
					hWnd,
					&Rect
				);

			// вывод строки в зону, определенную флажками
			DrawText(
					hDC,
					"Department of Computer Technology",
					-1,
					&Rect,
					DT_SINGLELINE|DT_CENTER|DT_VCENTER
				);

			// завершение перерисовки
			EndPaint(
					hWnd,
					&PaintStruct
				);

			return 0;

		// начало операции уничтожения окна
		// сообщение WM_DESTROY появляется в очереди сообщений при
		// закрытии окна
		case WM_DESTROY:

			// функция PostQuitMessage посылает окну (данным об окне в 
			// системе) сообщение WM_QUIT, которое вызывает прекращение
			// цикла обработки
			PostQuitMessage(0);

			return 0;
	}

	// обработка всех остальных сообщений (по умолчанию)
	return DefWindowProc(hWnd,Message,wParam,lParam);

}
