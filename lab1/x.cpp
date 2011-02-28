
/*					*
 *	Refactored by Fedorov Alex	*
 *	      source: x.cpp		*
 *					*/

#include "includes.hpp"
#include "prototypes.hpp"
#include "constants.hpp"

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
	initWndClass(
			WndClass,
			hInstance
		);

	// register our window class or die with error message
	if (regWndClass_orDie(WndClass)) return q_success;

	// create example window of our window class 
	// or die with error message
	if (
		createWindow_orDie(
					hWnd, 
					hInstance
				)
		) return q_success;

	// show our window on our display|monitor
	ShowWindow(
			hWnd,
			nCmdShow
		);

	// send WM_PAINT message to update and repaint our window
	UpdateWindow(hWnd);

	// main loop, gets messages from system using 
	// GetMessage function and processes it
	mainloop(Msg);

	// return extra information about message
	return Msg.wParam;

}


