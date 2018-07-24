/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : Window Control
 #	author : miyako
 #	2016/02/09
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

#if VERSIONWIN

namespace MDI
{
	HWND windowRef = NULL;
	HICON iconRef = NULL;

	HWND getWindowHWND(PA_WindowRef windowId)
	{
		if (windowId == (PA_WindowRef)MDI_WINDOW_ID)
		{
			return windowRef;
		}else
		{
			return (HWND)PA_GetHWND(windowId);
		}
	}
	
}
#endif

void OnStartup()
{
#if VERSIONWIN              
	PA_ulong32 version = PA_Get4DVersion();

	if (version >= 16)
	{
		MDI::windowRef = (HWND)PA_GetMainWindowHWND();
	}
	else
	{
		//the window class is the folder name of the application 
		HWND mdi = NULL;
		wchar_t path[_MAX_PATH] = { 0 };
		wchar_t * applicationPath = wcscpy(path, (const wchar_t *)PA_GetApplicationFullPath().fString);
		//remove file name (4D.exe)
		PathRemoveFileSpec(path);
		//check instance as well, to be sure
		HINSTANCE h = (HINSTANCE)PA_Get4DHInstance();
		do {
			mdi = FindWindowEx(NULL, mdi, (LPCTSTR)path, NULL);
			if (mdi)
			{
				if (h == (HINSTANCE)GetWindowLongPtr(mdi, GWLP_HINSTANCE))
				{
					break;
				}
			}
		} while (mdi);
		MDI::windowRef = mdi;
	}
	if (MDI::windowRef)
	{
		MDI::iconRef = (HICON)SendMessage(MDI::windowRef, WM_GETICON, ICON_BIG, (LPARAM)0);
	}
#endif 
}

void OnExit()
{
#if VERSIONWIN 
	if (MDI::windowRef)
	{
		wchar_t path[_MAX_PATH] = { 0 };
		wchar_t * applicationPath = wcscpy(path, (const wchar_t *)PA_GetApplicationFullPath().fString);
		
		SHFILEINFO fileinfo;
		if (SHGetFileInfo((LPCTSTR)applicationPath,
			0,
			&fileinfo,
			sizeof(fileinfo),
			SHGFI_LARGEICON | SHGFI_ICON))
		{
			HICON hIcon = fileinfo.hIcon;
			SendMessage(MDI::windowRef, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			/* "you are responsible for freeing it with DestroyIcon when you no longer need it" */
			/* https://docs.microsoft.com/ja-jp/windows/desktop/api/shellapi/nf-shellapi-shgetfileinfoa */
			DestroyIcon(hIcon);
		}

	}
#endif 
}

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
		case kInitPlugin :
		case kServerInitPlugin :  
			OnStartup();           
			break;

		case kDeinitPlugin:
			OnExit();
			break;

// --- Window Control

		case 1 :
			WND_Is_minimized(pResult, pParams);
			break;

		case 2 :
			WND_Is_maximized(pResult, pParams);
			break;

		case 3 :
			WND_SET_TITLE(pResult, pParams);
			break;

		case 4 :
			WND_Get_title(pResult, pParams);
			break;

		case 5 :
			WND_USE_ICON_FILE(pResult, pParams);
			break;

		case 6 :
			WND_MAXIMIZE(pResult, pParams);
			break;

		case 7 :
			WND_MINIMIZE(pResult, pParams);
			break;

		case 8 :
			WND_RESTORE(pResult, pParams);
			break;

		case 9:
			WND_SET_POSITION(pResult, pParams);
			break;

		case 10:
			WND_GET_POSITION(pResult, pParams);
			break;

	}
}

// -------------------------------- Window Control --------------------------------


void WND_Is_minimized(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	returnValue.setIntValue(IsIconic(window));
#endif

	returnValue.setReturn(pResult);
}

void WND_Is_maximized(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	returnValue.setIntValue(IsZoomed(window));
#endif

	returnValue.setReturn(pResult);
}

void WND_SET_TITLE(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_TEXT Param2;

	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);

#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	SetWindowText(window, (LPCTSTR)Param2.getUTF16StringPtr());
#endif
}

void WND_Get_title(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_TEXT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	size_t size = GetWindowTextLength(window);
	size++;
	std::vector<wchar_t> buf(size);
	size = GetWindowText(window, (LPTSTR)&buf[0], size);
	returnValue.setUTF16String((const PA_Unichar *)&buf[0], size);
	returnValue.setReturn(pResult);
#endif

	returnValue.setReturn(pResult);
}

void WND_USE_ICON_FILE(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_TEXT Param2;

	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);

#if VERSIONWIN
	SHFILEINFO fileinfo;
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());

	if (IsChild(MDI::windowRef, window))
	{
		/* seems child window can only accept ICON_SMALL */

		//system small size (currently, SHGFI_SHELLICONSIZE == SHGFI_SMALLICON
		//https://docs.microsoft.com/en-us/windows/desktop/menurc/about-icons

		if (SHGetFileInfo((LPCTSTR)Param2.getUTF16StringPtr(),
			0,
			&fileinfo,
			sizeof(fileinfo),
			SHGFI_SMALLICON | SHGFI_ICON))
		{
			HICON hIcon = fileinfo.hIcon;
			SendMessage(window, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			/* "you are responsible for freeing it with DestroyIcon when you no longer need it" */
			/* https://docs.microsoft.com/ja-jp/windows/desktop/api/shellapi/nf-shellapi-shgetfileinfoa */
			//DestroyIcon(hIcon);
			//but it seems this doesn't apply to MDI child windows
		}
	}
	else
	{
		if (SHGetFileInfo((LPCTSTR)Param2.getUTF16StringPtr(),
			0,
			&fileinfo,
			sizeof(fileinfo),
			SHGFI_LARGEICON | SHGFI_ICON))
		{
			HICON hIcon = fileinfo.hIcon;
			SendMessage(window, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			/* "you are responsible for freeing it with DestroyIcon when you no longer need it" */
			/* https://docs.microsoft.com/ja-jp/windows/desktop/api/shellapi/nf-shellapi-shgetfileinfoa */
			DestroyIcon(hIcon);
		}
	}
#endif
}

void WND_MAXIMIZE(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;

	Param1.fromParamAtIndex(pParams, 1);

#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	ShowWindow(window, SW_MAXIMIZE);
#endif

}

void WND_MINIMIZE(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;

	Param1.fromParamAtIndex(pParams, 1);
	
#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	ShowWindow(window, SW_MINIMIZE);
#endif

}

void WND_RESTORE(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;

	Param1.fromParamAtIndex(pParams, 1);
	
#if VERSIONWIN
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	ShowWindow(window, SW_RESTORE);
#endif
}

void WND_SET_POSITION(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT Param6;
	C_LONGINT Param7;

	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);

#if VERSIONWIN	
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	HWND hWndInsertAfter = (HWND)Param6.getIntValue();
	UINT flags = Param7.getIntValue();
	
	if (flags && hWndInsertAfter)
	{
		if((hWndInsertAfter != HWND_BOTTOM)
		&& (hWndInsertAfter != HWND_NOTOPMOST)
		&& (hWndInsertAfter != HWND_TOP)
		&& (hWndInsertAfter != HWND_TOPMOST))
		{
			 hWndInsertAfter = (HWND)PA_GetHWND((PA_WindowRef)hWndInsertAfter); 
		}
		
	}else
	{
		flags = SWP_NOZORDER;
	}
	
	SetWindowPos(window,
				 hWndInsertAfter, 
				 Param2.getIntValue(),
				 Param3.getIntValue(),
				 Param4.getIntValue(),
				 Param5.getIntValue(),
				 flags);
#endif

}

void WND_GET_POSITION(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;

	Param1.fromParamAtIndex(pParams, 1);

#if VERSIONWIN
	RECT rect;
	HWND window = MDI::getWindowHWND((PA_WindowRef)Param1.getIntValue());
	if (GetWindowRect(window, &rect))
	{
		Param2.setIntValue(rect.left);
		Param3.setIntValue(rect.top);
		Param4.setIntValue(rect.right - rect.left);
		Param5.setIntValue(rect.bottom - rect.top);
	}
#endif

	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
}

