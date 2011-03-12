#ifndef __constants_hpp
#define __constants_hpp

/*					*
 *	Refactored by Fedorov Alex	*
 *	  header: constants.hpp		*
 *					*/

//debug is off
//#define debug

// WNDCLASS constants
const char 
wc_ClassName[] = "Fedorov",			// T1.1
wc_wndname[] = "Author is Fedorov";		// T2.1

UINT 
wc_style = CS_OWNDC;				// T1.2

WNDPROC
wc_wndproc = WndProc;

int
wc_clsextra = 0,
wc_wndextra = 0,
wc_background_stock = 
#ifdef debug
COLOR_WINDOW + 1;
#else
BLACK_BRUSH;		// T1.5
#endif

LPCTSTR
wc_iconname = IDI_QUESTION,			// T1.3
wc_cursorname = IDC_UPARROW;			// T1.4

// window constants
DWORD
wnd_style = WS_OVERLAPPED | WS_VSCROLL;		// T2.3

int
wnd_left = 200,					// *		*
wnd_top = 200,					// *  	T2.2	*
wnd_width = 400,				// *	here	*
wnd_height = 300;				// *		*

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


#endif
