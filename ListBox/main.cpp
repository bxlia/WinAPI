#include<Windows.h>
#include<iostream>
#include<cstdio>
#include"resource.h"

CONST CHAR* ITEMS[] = { "This", "is", "my", "fitst", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc, 0);
    return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
        if (hIcon) {
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        }

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
        case IDC_BUTTON_ADD:  
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
            break;

        case IDC_BUTTON_DELETE:  
        {
            HWND hList = GetDlgItem(hwnd, IDC_LIST);
            int iSelected = SendMessage(hList, LB_GETCURSEL, 0, 0);
            if (iSelected != LB_ERR)
            {
                SendMessage(hList, LB_DELETESTRING, iSelected, 0);

                int iCount = SendMessage(hList, LB_GETCOUNT, 0, 0);
                if (iCount > 0)
                {
                    if (iSelected < iCount)
                        SendMessage(hList, LB_SETCURSEL, iSelected, 0);
                    else
                        SendMessage(hList, LB_SETCURSEL, iCount - 1, 0);
                }
            }
        }
        break;

        case IDC_LIST:
        {
            if (HIWORD(wParam) == LBN_DBLCLK)
            {
                HWND hList = GetDlgItem(hwnd, IDC_LIST);
                int iSelected = SendMessage(hList, LB_GETCURSEL, 0, 0);

                if (iSelected != LB_ERR)
                {
                    DialogBoxParam(GetModuleHandle(NULL),
                        MAKEINTRESOURCE(IDD_DIALOG_ADD),
                        hwnd,
                        DlgProcEdit,
                        (LPARAM)iSelected);
                }
            }
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

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
        return FALSE; 
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CHAR szBuffer[256] = {};
            HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD);
            GetWindowText(hEdit, szBuffer, 256);

            if (strlen(szBuffer) > 0)  
            {
                HWND hParent = GetParent(hwnd); //Получаем родительское окно
                HWND hListBox = GetDlgItem(hParent, IDC_LIST); //Получаем ListBox родительского окна
                SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)szBuffer);
            }

            EndDialog(hwnd, IDOK);
        }
        break;

        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hwnd, IDCANCEL);
        break;
    }
    return FALSE;
}

BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int iSelectedItem = -1; 

    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        iSelectedItem = (int)lParam;
        HWND hMainDialog = GetParent(hwnd);
        HWND hList = GetDlgItem(hMainDialog, IDC_LIST);

        CHAR szBuffer[256] = {};
        SendMessage(hList, LB_GETTEXT, iSelectedItem, (LPARAM)szBuffer);

        HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD);
        SetWindowText(hEdit, szBuffer);

        SetFocus(hEdit);
        return FALSE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CHAR szBuffer[256] = {};
            HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD);
            GetWindowText(hEdit, szBuffer, 256);

            if (strlen(szBuffer) > 0 && iSelectedItem != -1)
            {
                HWND hMainDialog = GetParent(hwnd);
                HWND hList = GetDlgItem(hMainDialog, IDC_LIST);
                SendMessage(hList, LB_DELETESTRING, iSelectedItem, 0);
                SendMessage(hList, LB_INSERTSTRING, iSelectedItem, (LPARAM)szBuffer);
                SendMessage(hList, LB_SETCURSEL, iSelectedItem, 0);
            }

            EndDialog(hwnd, IDOK);
        }
        break;

        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hwnd, IDCANCEL);
        break;
    }
    return FALSE;
}