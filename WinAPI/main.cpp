#include<Windows.h>

INT WINAPI  WinMain(HINSTANCE hInsance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmsShow)
{
	MessageBox(NULL, 
		"Привет Windows", 
		"Hello", 
		MB_YESNOCANCEL | MB_HELP | MB_ICONINFORMATION | MB_DEFBUTTON4 | MB_SYSTEMMODAL); //Окно сообщения
	return 0;
}