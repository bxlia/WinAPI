#include <Windows.h>
#include "resource.h"

CONST CHAR g_sz_INVITE[] = "¬ведите им€ пользовател€";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
    return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //HWND - Handler to Window
    //Ёто указатель, при помощи которого можно обратитьс€ к окну
    //(указатель, на который можнл отправить сообщение - SendMessage)
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
        if (hIcon) {
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        }

        HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
        SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_EDIT_LOGIN:
        {
            //WPARAM - это DWORD
            CONST INT SIZE = 256; 
            CHAR sz_buffer[SIZE] = {};
            HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
            SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
            if(HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_INVITE) == 0)
                SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
            if(HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
                SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);

        }
            break;
        case IDC_BUTTON_COPY:
        {
            CONST INT SIZE = 256; //
            CHAR sz_buffer[SIZE] = {};
            HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
            HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
            SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем текст из пол€ 'Login'
            SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer); //загружаем текст из буфера в поле 'Password'
            
        }
        break;
        case IDOK:
            MessageBox(hwnd, "OK", "Info", MB_OK | MB_ICONINFORMATION);
            break;

        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
        return TRUE;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        return TRUE;
    }
    return FALSE;
}