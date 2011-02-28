#ifndef __constants_hpp
#define __constants_hpp

/*					*
 *	Refactored by Fedorov Alex	*
 *	  header: constants.hpp		*
 *					*/

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


#endif
