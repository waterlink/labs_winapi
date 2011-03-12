
/************************************************************************
 *									*
 *			Lab_2	Variant #2				*
 *			Edited by Fedorov Alex				*
 *	L2T: v								*
 *	v	1. image modifications					*
 *		v	1) stretched and unstretched bitmap		*
 *		v	2) do not load image each time			*
 *		v	3) out text over an image			*
 *		v	4) out this text on printer			*
 *	v	2. graphical primitives, second over first		*
 *		v	1) first   <- Ellipse				*
 *			v	a. pen style	<- PS_NULL		*
 *			v	b. pen thickness<- 2			*
 *			v	c. pen color	<- 0, 0, 255		*
 *			v	d. brush color	<- 0, 0, 255		*
 *		v	2) second  <- Rectangle				*
 *			v	a. brush style	<- HS_VERTICAL		*
 *			v	b. brush color 	<- 128, 128, 255	*
 *			v	c. pen style	<- PS_INSIDEFRAME	*
 *			v	d. pen thickness<- 3			*
 *			v	e. pen color	<- 0, 0, 0		*
 *									*
 *									*
 ************************************************************************/

/****************************************************************
 *								*
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
 *								*
 ****************************************************************/


/****************************************
 *					*
 *	Refactored by Fedorov Alex	*
 *	      source: x.cpp		*
 *    This is a main file of project	*
 *   other files:			*
 *		constants.hpp		*
 *		includes.hpp		*
 *		prototypes.hpp		*
 *		wininitcore.cpp		*
 *		winmsgcore.cpp		*
 *		imgcore.cpp		*
 *					*
 ****************************************/

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

	printf("%d\n", _WIN32_WINNT);

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


