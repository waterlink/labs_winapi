
/*								*
 *			Lab_1	Variant #2			*
 *	  		Edited by Fedorov Alex			*
 * Task: v							*
 * v	1. wndclass parameters					*
 *	v	1) wnd class name  <- <last name> of author	*
 *	v	2) wnd class style <- CS_OWNDC			*
 *	v	3) icon handle     <- IDI_QUESTION		*
 *	v	4) cursor handle   <- IDC_UPARROW		*
 *	v	5) brush handle    <- BLACK_BRUSH		*
 * v	2. window example parameters				*
 *	v	1) window title	   <- "Author is <last name>"	*
 *	v	2) window position				*
 *	v	3) window style    <-WS_OVERLAPPED & WS_VSCROLL *
 *								*/


/*					*
 *	Refactored by Fedorov Alex	*
 *	      source: x.cpp		*
 *    This is a main file of project	*
 *   other files:			*
 *		constants.hpp		*
 *		includes.hpp		*
 *		prototypes.hpp		*
 *		wininitcore.hpp		*
 *		winmsgcore.hpp		*
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


