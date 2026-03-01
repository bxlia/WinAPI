#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* VALUES[] = { "This", "is", "my", "first", "List", "Box" };

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
        HWND hListBox = GetDlgItem(hwnd, IDC_LIST);

        // Загружаем список файлов из текущего каталога
        WIN32_FIND_DATA findData;
        HANDLE hFind = FindFirstFile("*.*", &findData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                // Пропускаем текущий и родительский каталоги
                if (strcmp(findData.cFileName, ".") != 0 &&
                    strcmp(findData.cFileName, "..") != 0)
                {
                    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)findData.cFileName);
                }
            } while (FindNextFile(hFind, &findData));

            FindClose(hFind);
        }
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_LIST:
            if (HIWORD(wParam) == LBN_DBLCLK)
                DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEdit, 0);
            break;
        case IDC_BUTTON_ADD:
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
            break;
        case IDC_BUTTON_DELETE:
        {
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            SendMessage(hListBox, LB_DELETESTRING, i, 0);
        }
        break;
        case IDOK:
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE] = {};
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);

            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
            CHAR sz_message[SIZE] = {};
            sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\".", i, sz_buffer);
            if (i != LB_ERR) MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
            else MessageBox(hwnd, "Для начала выберите элемент", "Info", MB_OK | MB_ICONINFORMATION);
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

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE] = {};
            HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);
            SendMessage(hEditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

            if (strlen(sz_buffer) > 0)
            {
                HWND hParent = GetParent(hwnd);
                HWND hListBox = GetDlgItem(hParent, IDC_LIST);
                if (SendMessage(hListBox, LB_FINDSTRING, 0, (LPARAM)sz_buffer) == LB_ERR)
                    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
            }
        }
        case IDCANCEL: EndDialog(hwnd, 0);
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, 0);
    }
    return FALSE;
}

BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CONST INT SIZE = 256;
    CHAR sz_buffer[SIZE] = {};
    HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD);
    HWND hParent = GetParent(hwnd);
    HWND hListBox = GetDlgItem(hParent, IDC_LIST);

    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменить выбранный элемент");
        INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
        SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
        SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
        SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
        SendMessage(hEdit, EM_SETSEL, 0, -1);
        SendMessage(hEdit, EM_SETSEL, -1, -1);
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
            if (strlen(sz_buffer) > 0 && SendMessage(hListBox, LB_FINDSTRING, 0, (LPARAM)sz_buffer) == LB_ERR)
            {
                INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                SendMessage(hListBox, LB_DELETESTRING, i, 0);
                SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
            }
            EndDialog(hwnd, 0);
            break;
        }
        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, 0);
    }
    return FALSE;
}