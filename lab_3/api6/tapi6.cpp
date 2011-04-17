// author Fedorov Alex

#include "tapi6.hpp"

#include <windows.h>
#include <commctrl.h>
#include "menu.h"
#include <cstdio>


char* pMessages[]=
{
"Enable or disable exit", 
"Exit from the program", 
"About this program", 
"Draw image", 
"Draw ellipse", 
"Draw rectangle", 
"File operations", 
"Draw primitives", 
"Help operations", 
"Menu example", 
"System menu"
};

long WINAPI DepartComTechWndProc(HWND,UINT,UINT,LONG);

HWND hStatusWindow;
UINT wId;
HMENU hMenu,hFileMenu,hHelpMenu;
HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance,
				LPSTR lpszCmdParam, int nCmdShow)
{

HWND hWnd; 
WNDCLASS WndClass; 
MSG Msg;
HACCEL hAccel1, hAccel2, hAccel3, hAccel4;
hInst=hInstance;

// инициализация имени класса как строки

WndClass.style=CS_HREDRAW|CS_VREDRAW;
WndClass.lpfnWndProc=(WNDPROC)DepartComTechWndProc;
WndClass.cbClsExtra=0;
WndClass.cbWndExtra=0;
WndClass.hInstance=hInstance;
WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
WndClass.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
WndClass.lpszMenuName="MyMenu";
WndClass.lpszClassName="DepartComTech_Menu";

if(!RegisterClass(&WndClass))
{
	MessageBox(NULL,"Cannot register class","Error",MB_OK);
	return 0;
}

hWnd=CreateWindow("DepartComTech_Menu","Sixth Example",
				WS_OVERLAPPEDWINDOW, 
				CW_USEDEFAULT,CW_USEDEFAULT,
				CW_USEDEFAULT,CW_USEDEFAULT,
				NULL,NULL,
				hInstance,NULL);

if(!hWnd)

{
	MessageBox(NULL,"Cannot create window","Error",MB_OK);
	return 0;
}
//
InitCommonControls();
hStatusWindow=CreateStatusWindow(WS_CHILD|WS_VISIBLE,
								 NULL,hWnd,wId);

if(!hStatusWindow)

{
	MessageBox(NULL,"Cannot create status window",
		"Error",MB_OK);
	return 0;
}

//загрузка таблицы акселераторов
hAccel1=LoadAccelerators(hInst,"MyAccelerators");
/*hAccel2=LoadAccelerators(hInst,"EX");
hAccel3=LoadAccelerators(hInst,"ABO");
hAccel4=LoadAccelerators(hInst,"DISEN");*/

if (hAccel1 == NULL/* || hAccel2 == NULL || hAccel3 == NULL || hAccel4 == NULL */){

	printf("can't load acc\n");

}

//отобразить окно		   
ShowWindow(hWnd,nCmdShow);
UpdateWindow(hWnd);

hFileMenu=GetSubMenu(GetMenu(hWnd),0);

while(GetMessage(&Msg,NULL,0,0))
{
	if(!TranslateAccelerator(hWnd,hAccel1,&Msg))
	{
		TranslateMessage(&Msg);
	}
	DispatchMessage(&Msg);
}
return Msg.wParam;
}

HANDLE
img_load(
		HWND & hWnd,
		const char * path,
		int imgtype
	){

	static HANDLE
	hBitmap;

	static bool 
	loaded = false;

	if (!loaded){

		hBitmap = LoadImage(
					NULL,
					path, 
					imgtype,
					0,
					0,
					LR_LOADFROMFILE
				);

		loaded = true;

	}

	return hBitmap;

}

void
on_paint(
		HWND & hWnd,
		int img,
		int p1,
		int p2,
		HANDLE hBitmap
	){

	HDC 
	hDC, 				// driver context handle
	hCompatibleDC;			// driver context handle in memory

	PAINTSTRUCT 
	PaintStruct;			// features of painting area

	HANDLE
	hOldBitmap;

	RECT 
	Rect,				// client area for painting
	Rect2;

	BITMAP 
	Bitmap;				// logical parameters of our bitmap

	LOGBRUSH
	brush;				// our brush

	HBRUSH
	hBrush;				// our brush handle

	HPEN
	hPen;				// our pen handle

	bool stretched = false;

	// get handle of our driver context
	hDC = BeginPaint(
				hWnd,
				&PaintStruct
			);

	// load our bitmap from file in current folder
	/*hBitmap = img_load(							// **************
				hWnd,						// *		*
				img_path,					// *   L2T1.2	*
				img_type					// *		*
			);							// **************
	*/

	// get a size of our bitmap
	GetObject(
			hBitmap,
			sizeof(BITMAP),
			&Bitmap
		);

	// create compatible driver context
	// with our driver context in memory
	hCompatibleDC = CreateCompatibleDC(hDC);

	// selecting our bitmap as current
	// in our context in memory
	hOldBitmap = SelectObject(
					hCompatibleDC,
					hBitmap
				);

	// get our client painting area
	GetClientRect(
				hWnd,
				&Rect
			);

	static int counter = 0;

	if (counter >= 10){
		InvalidateRect(hWnd, &Rect, true);
		counter = 0;
	}
	counter++;

	Rect2 = Rect;								// **************
										// *		*
	Rect2.left = Rect2.right / 6;						// *		*
	Rect2.top = Rect2.bottom / 6;						// *	L2T1.1	*
	Rect2.right = Rect2.right * 2 / 3;					// *		*
	Rect2.bottom = Rect2.bottom * 2 / 3;					// *		*
										// *		*
	if (!stretched) Rect = Rect2;						// **************

	// copy our bitmap to compatible context with stretching, if flag is active
	if (img) StretchBlt(
			hDC,
			Rect.left,
			Rect.top,					
			Rect.right, 			
			Rect.bottom,			
			hCompatibleDC,
			0,
			0,
			Bitmap.bmWidth,
			Bitmap.bmHeight,
			SRCCOPY
		);

	// older bitmap becomes a current one
	SelectObject(
				hCompatibleDC,
				hOldBitmap
			);

	// out our text in our format
/*	DrawText(							// **************
			hDC,						// *		*
			td_text,					// *		*
			td_nullterminated,				// *	L2T1.3	*
			&Rect,						// *		*
			td_format					// *		*
		);							// **************

*/
	// *******	L2T2.1 here	*******

	// setting up our brush	
	brush.lbStyle = BS_SOLID;
	brush.lbColor = RGB(
				0, 
				0, 
				255
			);

	hBrush = CreateBrushIndirect(&brush);

	SelectObject(
				hDC,
				hBrush
			);

	// setting up our pen
	hPen = CreatePen(
				PS_NULL,
				2,
				RGB(0, 0, 255)
			);

	SelectObject(
				hDC,
				hPen
			);

	// draw our first primitive
	if (p1)
		Ellipse(
				hDC,
				Rect.left,
				Rect.top,
				Rect.right,
				Rect.bottom
			);

	// *******	L2T2.2 here	*******

	// and a brush again
	brush.lbStyle = BS_HATCHED;
	brush.lbColor = RGB(
				0, 
				0, 
				255
			);
	brush.lbHatch = HS_VERTICAL;

	hBrush = CreateBrushIndirect(&brush);

	SelectObject(
				hDC,
				hBrush
			);

	// and a pen again
	hPen = CreatePen(
				PS_INSIDEFRAME,
				3,
				RGB(0, 0, 0)
			);

	SelectObject(
				hDC,
				hPen
			);

	// draw our second primitive
	if (p2)
		Rectangle(
				hDC,
				Rect.left * 3 / 4 + Rect.right / 4,
				Rect.top * 3 / 4 + Rect.bottom / 4,
				Rect.right / 2,
				Rect.bottom / 2
			);
	
	// delete loaded bitmap - we don't want do that now
	//DeleteObject(hBitmap);

	// delete compatible context in memory
	DeleteDC(hCompatibleDC);

	// finalizing painting
	EndPaint(
			hWnd,
			&PaintStruct
		);

}

long WINAPI DepartComTechWndProc(HWND hWnd,
				UINT Message, UINT wParam,LONG lParam)

{
RECT Rect;
static UINT nFlag=MF_ENABLED;

char* pContent[]=
{
"Enable e&xit\tctrl+b",
"Disable e&xit\tctrl+b"

};
static UINT nIndex=0;
static HANDLE hBitmap;
static int img = 0, p1 = 0, p2 = 0;
hBitmap = img_load(hWnd, "my2.bmp", IMAGE_BITMAP);
switch(Message)
{
case WM_PAINT:

	on_paint(hWnd, img, p1, p2, hBitmap);

	return 0;
case WM_SYSCOMMAND:
	fprintf(stderr, "%d %d %d %d\n", LOWORD(wParam), IDM_Exit, IDM_About, IDM_Enable_Disable);
	break;
case WM_COMMAND:
	fprintf(stderr, "%d %d %d %d\n", LOWORD(wParam), IDM_Exit, IDM_About, IDM_Enable_Disable);
	switch(LOWORD(wParam))
	{
	case IDM_Enable_Disable:
		EnableMenuItem(hFileMenu, IDM_Exit, MF_BYCOMMAND|nFlag);
		nFlag=(nFlag==MF_ENABLED)? MF_GRAYED:MF_ENABLED;
		nIndex=(nIndex==0)?1:0;
		ModifyMenu(hFileMenu,IDM_Enable_Disable,
			MF_BYCOMMAND|MF_STRING,IDM_Enable_Disable,
			pContent[nIndex]);

	break;

	case IDM_About:

		MessageBox(hWnd, "By: Fedorov Alex", "About", MB_OK | MB_ICONINFORMATION);

	break;
		
	case IDM_Image:
		img ^= 1;
		UpdateWindow(hWnd);
		on_paint(hWnd, img, p1, p2, hBitmap);
	break;

	case IDM_P1:
		p1 ^= 1;
		UpdateWindow(hWnd);
		on_paint(hWnd, img, p1, p2, hBitmap);
	break;

	case IDM_P2:
		p2 ^= 1;
		UpdateWindow(hWnd);
		on_paint(hWnd, img, p1, p2, hBitmap);
	break;

	case IDM_Exit:
		SendMessage(hWnd,WM_CLOSE,NULL,NULL);
	break;
	}
case WM_SIZE:
	SendMessage(hStatusWindow,WM_SIZE,wParam,lParam);
	GetClientRect(hWnd,&Rect);
	return 0;
//
case WM_MENUSELECT:
	printf("%d %d %d\n", LOWORD(wParam), HIWORD(wParam), MF_POPUP);
	if(((UINT)HIWORD(wParam)==0xffff)&
		((HMENU)lParam==0))
	{
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[mcnt + pcnt + 0]);
	return 0;
	}
	if((UINT)HIWORD(wParam)& MF_SYSMENU)
	{
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[mcnt + pcnt + 1]);
	return 0;
	}
	if((UINT)HIWORD(wParam)& MF_POPUP)
	{
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[mcnt + LOWORD(wParam)]);
	return 0;
	}
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[LOWORD(wParam) - IDM_Enable_Disable]);
	return 0;
case WM_DESTROY:

	PostQuitMessage(0);
	return 0;
}
return DefWindowProc(hWnd,Message,wParam,lParam);
}


