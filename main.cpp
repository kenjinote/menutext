#pragma comment(linker, "/opt:nowin98")
#include <windows.h>
#include "resource.h"

#define IDM_TEXT 5000

CHAR szClassName[]="window";
LPDRAWITEMSTRUCT lpDI;//メニューに文字列表示に必要

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	TCHAR str[20];
	RECT rt;

    switch (msg){
		case WM_COMMAND:
			switch (LOWORD(wParam)){
				case IDM_EXIT:
					SendMessage(hWnd,WM_CLOSE,0,0);
					break;
			}
			break;
		case WM_CREATE:
			AppendMenu(GetMenu(hWnd),MF_OWNERDRAW|MF_HELP,IDM_TEXT,NULL);
			break;
        case WM_DRAWITEM:
            lpDI=(LPDRAWITEMSTRUCT)lParam;
            rt=lpDI->rcItem;
            hdc=lpDI->hDC;
            switch (lpDI->itemID){
				case IDM_TEXT:
					wsprintf(str,"%s","表示する文字列");
					if(GetFocus()==hWnd){SetTextColor(hdc,GetSysColor(COLOR_MENUTEXT));}
					else {SetTextColor(hdc,GetSysColor(COLOR_GRAYTEXT));}
					DrawText(hdc,str,-1,&rt,DT_RIGHT|DT_NOCLIP|DT_VCENTER|DT_SINGLELINE);
					break;
            }
            break;
		case WM_SETFOCUS:
		case WM_KILLFOCUS:
			DrawMenuBar(hWnd);
			break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd,msg,wParam,lParam));
    }
    return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
                   LPSTR pCmdLine,int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS wndclass;
    if(!hPreInst){
        wndclass.style=CS_HREDRAW|CS_VREDRAW;
        wndclass.lpfnWndProc=WndProc;
        wndclass.cbClsExtra=0;
        wndclass.cbWndExtra=0;
        wndclass.hInstance =hinst;
        wndclass.hIcon=NULL;
        wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
        wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
        wndclass.lpszMenuName=(LPCSTR)IDR_MENU1;
        wndclass.lpszClassName=szClassName;
        if(!RegisterClass(&wndclass))
            return FALSE;
    }
    hWnd=CreateWindow(szClassName,
        "タイトル",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hinst,
        NULL);
    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}


