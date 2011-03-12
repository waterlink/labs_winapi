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

const UINT 
wc_style = CS_OWNDC;				// T1.2

const WNDPROC
wc_wndproc = WndProc;

const int
wc_clsextra = 0,
wc_wndextra = 0,
wc_background_stock = 
#ifdef debug
COLOR_WINDOW + 1;
#else
BLACK_BRUSH;					// T1.5
#endif

LPCTSTR
wc_iconname = IDI_QUESTION,			// T1.3
wc_cursorname = IDC_UPARROW;			// T1.4

// window constants
DWORD
wnd_style = WS_OVERLAPPED | WS_VSCROLL;		// T2.3

const int
wnd_left = 100,					// *		*
wnd_top = 100,					// *  	T2.2	*
wnd_width = 800,				// *	here	*
wnd_height = 700;				// *		*

// error messages
const char
err_regwndclass[] = "Cannot register class",
err_type[] = "Error",
err_createwnd[] = "Cannot create window",
err_printer[] = "Cannot open printer",
err_printer_prepare[] = "Cannot prepare printer";

const UINT
err_buttons = MB_OK;

// messaging subsystem constants
UINT
msg_minfilter = 0,
msg_maxfilter = 0;

// text drawing constants
const char
td_text[] = "Edited by Fedorov Alex";

const int
td_nullterminated = -1;

const UINT
td_format = DT_SINGLELINE | DT_CENTER | DT_VCENTER;

// onquit constants
const int
q_success = 0;

// image loading constants
const char
img_path[] = "MyFile.bmp";

const int
img_type = IMAGE_BITMAP;

// printer constants
const int
max_prname_size = 255;

const char
prn_driver[] = "WINSPOOL",
prn_docname[] = "TextToPrint",
prn_okmsg[] = "Document queued for print",
prn_oktitle[] = "Everything is ok";

const int
prn_left = 5,
prn_top = 5,
prn_right = 10,
prn_bottom = 10;

// global variables
bool
stretched = true,
flag_prim1 = false,
flag_prim2 = false;

#endif

