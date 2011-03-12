
/*					*
 *	Refactored by Fedorov Alex	*
 *	  source: wininitcore.cpp	*
 *					*/

#include "includes.hpp"
#include "prototypes.hpp"
#include "constants.hpp"

#ifdef debug
#include <cstdio>
#endif

void
initWndClass(
		WNDCLASS & WndClass,
		HINSTANCE & hInstance
	){

	WndClass.style = wc_style;
	WndClass.lpfnWndProc = wc_wndproc;
	WndClass.cbClsExtra = wc_clsextra;
	WndClass.cbWndExtra = wc_wndextra;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(
					NULL, 
					wc_iconname
				);
	#ifdef debug
		printf("%d %d\n", IDI_APPLICATION, IDC_ARROW);
	#endif
	WndClass.hCursor = LoadCursor(
					NULL,
					wc_cursorname
				);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(wc_background_stock);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = wc_ClassName;

}

void
Die(
	const char * err_msg
){

	MessageBox(
			NULL,
			err_msg,
			err_type,
			err_buttons
		);
}

int
regWndClass_orDie(
			WNDCLASS & WndClass
		){

	if (!RegisterClass(&WndClass)){

		Die(err_regwndclass);

		return 1;

	}

	return 0;

}

int
createWindow_orDie(
			HWND & hWnd,
			HINSTANCE & hInstance
		){

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

	if(!hWnd){

		Die(err_createwnd);

		return 1;

	}

	return 0;

}
