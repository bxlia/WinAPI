#include<Windows.h>
#include<iostream>
#include"resource.h"

CONST CHAR* ITEMS[] = { "This", "is", "my", "fitst", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPARAM)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		if (hIcon) {
			SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
	}
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			//AllocConsole();
			for (int i = 0; i < sizeof(ITEMS) / sizeof(ITEMS[0]); i++)
			{
				// std::cout << ITEMS[i] << std::endl;
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)ITEMS[i]);
			}
			SendMessage(hCombo, CB_SETCURSEL, 0, 0);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0); //Получаем номер выбранного текста
			if (i != CB_ERR)
			{
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer); //Считываем содержимое выбранной строки в строке буфер
				sprintf_s(sz_message, SIZE, "Вы выбрали пункт №%d со значением '%s'.", i+1, sz_buffer);
				MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			}
			
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}