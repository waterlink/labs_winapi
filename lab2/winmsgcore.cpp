
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
	Rect;				// client area for painting

	BITMAP 
	Bitmap;				// logical parameters of our bitmap

	// get handle of our driver context
	hDC = BeginPaint(
				hWnd,
				&PaintStruct
			);

	// load our bitmap from file in current folder
	hBitmap = LoadImage(
				NULL,
				img_path, 
				img_type,
				0,
				0,
				LR_LOADFROMFILE
			);

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

	// copy our bitmap to compatible context with stretching
	StretchBlt(
			hDC,
			0,
			0,
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

	// delete loaded bitmap
	DeleteObject(hBitmap);

	// delete compatible context in memory
	DeleteDC(hCompatibleDC);

	// finalizing painting
	EndPaint(
			hWnd,
			&PaintStruct
		);

}

