# 4d-plugin-window-control
Better control of window state and position

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|🚫|🚫|🆗|🆗|

Commands
---

```c
// --- Window Control
WND_Is_minimized
WND_Is_maximized
WND_SET_TITLE
WND_Get_title
WND_USE_ICON_FILE
WND_MAXIMIZE
WND_MINIMIZE
WND_RESTORE
WND_SET_POSITION
WND_GET_POSITION
```

**Note**: Pass the constant ``WND_MDI (-1)`` to access the MDI window.

``$5`` and ``$6`` of ``WND SET POSITION`` is optional. 

In ``$5`` you can pass one of the following options: 

* HWND_NOTOPMOST -2
* HWND_TOPMOST -1
* HWND_TOP 0
* HWND_BOTTOM 1

In ``$6`` you can pass one of the following options: 

* SWP_NOSIZE 1
* SWP_NOMOVE 2
* SWP_NOZORDER 4
* SWP_NOREDRAW 8
* SWP_NOACTIVATE 16
* SWP_DRAWFRAME 32
* SWP_SHOWWINDOW 64
* SWP_HIDEWINDOW 128
* SWP_NOCOPYBITS 256
* SWP_NOOWNERZORDER 512
* SWP_NOSENDCHANGING 1024
* SWP_DEFERERASE 8192
* SWP_ASYNCWINDOWPOS 16384
 
If you omit ``$5`` and ``$6``, ``SWP_NOZORDER`` is used.
