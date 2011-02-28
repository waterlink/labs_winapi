
/*					*
 *	Refactored by Fedorov Alex	*
 *					*/

#include <windows.h>
#include <cstring>

// my window procedure prototype
LRESULT CALLBACK 
WndProc(
			HWND, 
			UINT, 
			UINT, 
			LONG
		);

// WNDCLASS constants
const char 
wc_ClassName[] = "DepartComTech",
wc_wndname[] = "First Example";

UINT 
wc_style = CS_HREDRAW | CS_VREDRAW;

WNDPROC
wc_wndproc = WndProc;

int
wc_clsextra = 0,
wc_wndextra = 0,
wc_background_stock = WHITE_BRUSH;

LPCTSTR
wc_iconname = IDI_APPLICATION,
wc_cursorname = IDC_ARROW;

// window constants
DWORD
wnd_style = WS_OVERLAPPEDWINDOW;

int
wnd_left = CW_USEDEFAULT,
wnd_top = CW_USEDEFAULT,
wnd_width = CW_USEDEFAULT,
wnd_height = CW_USEDEFAULT;

// error messages
const char
err_regwndclass[] = "Cannot register class",
err_type[] = "Error",
err_createwnd[] = "Cannot create window";

UINT
err_buttons = MB_OK;

// messaging subsystem constants
UINT
msg_minfilter = 0,
msg_maxfilter = 0;

// text drawing constants
char
td_text[] = "Department of Computer Technology";

int
td_nullterminated = -1;

UINT
td_format = DT_SINGLELINE | DT_CENTER | DT_VCENTER;

// onquit constants
int
q_success = 0;

// definition of main windows function - start point of program
int __stdcall 
WinMain(
		HINSTANCE hInstance, 
		HINSTANCE,
		LPSTR lpszCmdParam, 
		int nCmdShow
	){

	WNDCLASS 
	WndClass; // structure with features of my window class

	HWND 
	hWnd; // window handle

	MSG 
	Msg; // message struct

	// initializing structure WNDCLASS
	WndClass.style = wc_style;
	WndClass.lpfnWndProc = wc_wndproc;
	WndClass.cbClsExtra = wc_clsextra;
	WndClass.cbWndExtra = wc_wndextra;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(
					NULL, 
					wc_iconname
				);
	WndClass.hCursor = LoadCursor(
					NULL,
					wc_cursorname
				);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(wc_background_stock);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = wc_ClassName;

	// register our window class or die with error message
	if (!RegisterClass(&WndClass)){

		MessageBox(
				NULL,
				err_regwndclass,
				err_type,
				err_buttons
			);

		return q_success;

	}

	// create example window of our window class ...
	hWnd = CreateWindow(
				wc_ClassName,
				wc_wndname,
				wnd_style, 
				wnd_left,
				wnd_top,
				wnd_width,
				wnd_height,
				NULL,
				NULL,
				hInstance,
				NULL
			);

	// ... or die with error message
	if(!hWnd){

		MessageBox(
				NULL,
				err_createwnd,
				err_type,
				err_buttons
			);

		return q_success;

	}

	// show our window on our display|monitor
	ShowWindow(
			hWnd,
			nCmdShow
		);

	// send WM_PAINT message to update and repaint our window
	UpdateWindow(hWnd);

	// main loop, gets messages from system using 
	// GetMessage function and processes it
	while(
			GetMessage(
					&Msg,
					NULL,
					msg_minfilter,
					msg_maxfilter
				)
		){


		// translating message to identic form
		TranslateMessage(&Msg);

		// force our window procedure to process our message
		DispatchMessage(&Msg);
	}

	// return extra information about message
	return Msg.wParam;

}

LRESULT CALLBACK 
WndProc(
			HWND hWnd,
			UINT Message, 
			UINT wParam,
			LONG lParam
		){

	HDC 
	hDC; // device context handle

	PAINTSTRUCT 
	PaintStruct; // features of our painting area

	RECT 
	Rect; // painting area rectangle

	// we are interesting only in paint and destroy messages
	switch (Message){

		case WM_PAINT:

			// get our device context handle
			hDC = BeginPaint(
						hWnd,
						&PaintStruct
					);

			// determine our client area for painting
			// usually, (0, 0), (a, b)
			// where a - width, b - height
			GetClientRect(
					hWnd,
					&Rect
				);

			// out our text in our format
			DrawText(
					hDC,
					td_text,
					td_nullterminated,
					&Rect,
					td_format
				);

			// finilization of painting
			EndPaint(
					hWnd,
					&PaintStruct
				);

			return q_success;

		// somebody wants to close our window!
		case WM_DESTROY:

			// here we want to save smth, or clean up
			// but sadly, project is too light, nothing to do here

			// tell system "everything is ok, close me"
			PostQuitMessage(q_success);

			return q_success;
	}

	// another message? don't care. call default window procedure
	return DefWindowProc(
				hWnd,
				Message,
				wParam,
				lParam
			);

}

