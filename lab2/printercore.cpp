
/*					*
 *	Refactored by Fedorov Alex	*
 *	 source: printercore.cpp	*
 *					*/

#include "includes.hpp"
#include "prototypes.hpp"
#include "constants.hpp"

// L2T1.4
void
print_out_text(
			HWND & hWnd
		){

	char
	PrinterName[max_prname_size];

        unsigned long 
	PrinterNameLength;

        GetDefaultPrinter(
				PrinterName, 
				&PrinterNameLength
			);

        HDC 
	hPrinterDC = CreateDC(
					prn_driver, 
					PrinterName, 
					0, 
					0
				);

        DOCINFO 
	di;

        di.cbSize = sizeof(DOCINFO);
        di.lpszDocName = prn_docname;
        di.lpszOutput = 0;
        di.lpszDatatype = 0;
        di.fwType = 0;

        if (
		StartDoc(
				hPrinterDC, 
				&di
			) < 0) 
		Die(err_printer);

        int 
	WidthPels = GetDeviceCaps(
					hPrinterDC, 
					HORZRES
				),
        HeightPels = GetDeviceCaps(
					hPrinterDC, 
					VERTRES
				);
        
        RECT 
	rcPrinter;

        rcPrinter.top = prn_top;
        rcPrinter.left = prn_left;
        rcPrinter.right = WidthPels - prn_right;
        rcPrinter.bottom = HeightPels - prn_bottom;

        if(StartPage(hPrinterDC) < 0) Die(err_printer_prepare);

        DrawText(
			hPrinterDC, 
			td_text, 
			td_nullterminated, 
			&rcPrinter, 
			td_format
		);

        EndPage(hPrinterDC);

        EndDoc(hPrinterDC);

        DeleteDC(hPrinterDC);

        MessageBox(
			hWnd, 
			prn_okmsg, 
			prn_oktitle, 
			0
		);

}

