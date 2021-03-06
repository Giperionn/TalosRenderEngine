﻿// DirectDrawApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DirectDrawApp.h"
#include "DrawEngine.h"
#include "PrivateMacro.h"
#include "Window.h"
#include "unicode\unistr.h"
#include "Log.h"


LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

Window* window;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	RECT DesktopRect;
	HWND DesktopHwnd = GetDesktopWindow();
	GetWindowRect(DesktopHwnd, &DesktopRect);
	int Width = DesktopRect.right - DesktopRect.left;
	int Height = DesktopRect.bottom - DesktopRect.top;


	WindowParam param;
	param.width = ENGINEWIDTH;
	param.height = ENGINEHEIGHT;
	param.x = (Width / 2) - (ENGINEWIDTH / 2);
	param.y = (Height / 2) - (ENGINEHEIGHT / 2);
	param.type = WindowType::WT_Graphic;

	window = new Window(param, hInstance, nCmdShow);

	WindowParam consoleParam;
	consoleParam.type = WindowType::WT_Console;

	Window* wConsole = new Window(consoleParam, nullptr, 0);
	Log* log = Log::GetInstance();
	log->PrintMsg(UnicodeString(L"Veliya Engine initialize routine start..."));

	DWORD returnResult = window->Go(WndProc);
	delete window;
	delete log;
	delete wConsole;
	return returnResult;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return window->MessageHandler(hWnd, message, wParam, lParam);
}