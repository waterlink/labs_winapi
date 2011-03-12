#ifndef __prototypes_hpp
#define __prototypes_hpp

/*					*
 *	Refactored by Fedorov Alex	*
 *	  header: prototypes.hpp	*
 *					*/

// my window procedure prototype
LRESULT CALLBACK 
WndProc(
			HWND, 
			UINT, 
			UINT, 
			LONG
		);

// inits our window class
void
initWndClass(
		WNDCLASS & WndClass,
		HINSTANCE & hInstance
	);

// outputs error message
void
Die(
	const char *
);

// trying to register window class
int
regWndClass_orDie(
			WNDCLASS & WndClass
		);

// trying to create example window
int
createWindow_orDie(
			HWND & hWnd,
			HINSTANCE & hInstance
		);

// main loop, getting'n'processing messages
void
mainloop(
		MSG & Msg
	);

// WM_PAINT message processor
void
on_paint(
		HWND & hWnd
	);

// WM_KEYDOWN message processor
void
on_keydown(
		HWND & hWnd,
		UINT wParam
	);

// image loader, loads only one time
HANDLE
img_load(
		HWND & hWnd,
		const char * path,
		int imgtype
	);

// prints text on default printer, or dies with error
void
print_out_text(
			HWND & hWnd
		);

#endif
