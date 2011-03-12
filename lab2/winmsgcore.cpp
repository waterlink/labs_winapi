
/*					*
 *	Refactored by Fedorov Alex	*
 *	  source: winmsgcore.cpp	*
 *					*/

#include "includes.hpp"
#include "prototypes.hpp"
#include "constants.hpp"

LRESULT CALLBACK 
WndProc(
			HWND hWnd,
			UINT Message, 
			UINT wParam,
			LONG lParam
		){	

	// we are interesting only in paint and destroy messages
	switch (Message){

		case WM_PAINT:

			on_paint(hWnd);

			return q_success;

		case WM_KEYDOWN:

			on_keydown(
					hWnd,
					wParam
				);

			return q_success;

		// somebody wants to close our window!
		case WM_DESTROY:

			// here we want to save smth, or clean up
			// but suddenly, project is too light, nothing to do here

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

void
mainloop(
		MSG & Msg
	){

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

}

void
on_paint(
		HWND & hWnd
	){

	HDC 
	hDC, 				// driver context handle
	hCompatibleDC;			// driver context handle in memory

	PAINTSTRUCT 
	PaintStruct;			// features of painting area

	HANDLE 
	hBitmap,			// loaded bitmap handle
	hOldBitmap;			// old bitmap handle
	
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

	// get handle of our driver context
	hDC = BeginPaint(
				hWnd,
				&PaintStruct
			);

	// load our bitmap from file in current folder
	hBitmap = img_load(							// **************
				hWnd,						// *		*
				img_path,					// *   L2T1.2	*
				img_type					// *		*
			);							// **************

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

	Rect2 = Rect;								// **************
										// *		*
	Rect2.left = Rect2.right / 6;						// *		*
	Rect2.top = Rect2.bottom / 6;						// *	L2T1.1	*
	Rect2.right = Rect2.right * 2 / 3;					// *		*
	Rect2.bottom = Rect2.bottom * 2 / 3;					// *		*
										// *		*
	if (!stretched) Rect = Rect2;						// **************

	// copy our bitmap to compatible context with stretching, if flag is active
	StretchBlt(
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
	DrawText(							// **************
			hDC,						// *		*
			td_text,					// *		*
			td_nullterminated,				// *	L2T1.3	*
			&Rect,						// *		*
			td_format					// *		*
		);							// **************


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
	if (flag_prim1)
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
	if (flag_prim2)
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

void
on_keydown(
		HWND & hWnd,
		UINT wParam
	){

	printf("wParam = %d\n", wParam);

	switch ((LOWORD(wParam))){

		case 'S':

			printf("catched stretch\n");

			stretched = !stretched;					//	L2T1.1
			return;

		case 'P':

			printf("catched print\n");

			print_out_text(hWnd);					//	L2T1.4
			return;

		case '1':

			printf("1 catched\n");

			flag_prim1 = !flag_prim1;
			return;

		case '2':

			printf("2 catched\n");

			flag_prim2 = !flag_prim2;
			return;

	}

}

