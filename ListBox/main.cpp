#include<Windows.h>
#include<iostream>
#include"resource.h"

CONST CHAR* ITEMS[] = { "This", "is", "my", "fitst", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc, 0);
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
        HWND hList = GetDlgItem(hwnd, IDC_LIST);
        for (int i = 0; i < sizeof(ITEMS) / sizeof(ITEMS[0]); i++)
        {
            SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)ITEMS[i]);
        }
        SendMessage(hList, LB_SETCURSEL, 0, 0); 
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CONST INT SIZE = 156;
            CHAR sz_buffer[SIZE] = {};
            HWND hCombo = GetDlgItem(hwnd, IDC_LIST);

            INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0); //Получаем номер выбранного текста

            SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer); //Считываем содержимое выбранной строки в строке буфер


        }
        break;

        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}