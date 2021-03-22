![version](https://img.shields.io/badge/version-17%2B-3E8B93)
![platform](https://img.shields.io/static/v1?label=platform&message=win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-window-control)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-window-control/total)

# 4d-plugin-window-control
Better control of window state and position.

### Remarks

Since 17R4, passing the ``HWMD`` of the MDI seems to hang on 4D Server. Workaround was to use ``PA_RunInMainProcess``.

On some versions of Windows 10 Pro 1809 (tested 17763.253), using ``SHGetFileInfo`` to obtain ``HICON`` seems to fail. ``LoadImage``, on the other hand, seems more stable. So the code was changed in [2.2](https://github.com/miyako/4d-plugin-window-control/releases/tag/2.2) to use ``LoadImage`` instead.

## Syntax

```
minimized:=WND Is minimized (window)
```

Parameter|Type|Description
------------|------|----
window|LONGINT|
minimized|LONGINT|

```
maximized:=WND Is maximized (window)
```

Parameter|Type|Description
------------|------|----
window|LONGINT|
maximized|LONGINT|

```
WND SET TITLE (window;title)
title:=WND Get title (window)
```

Parameter|Type|Description
------------|------|----
window|LONGINT|
title|TEXT|

```
WND USE ICON FILE (window;path)
```

Parameter|Type|Description
------------|------|----
window|LONGINT|
path|TEXT|


```
WND MAXIMIZE (window)
WND MINIMIZE (window)
WND RESTORE (window)
```

Parameter|Type|Description
------------|------|----
window|LONGINT|

```
WND SET POSITION (window;x;y;width;height{;orderFlag_or_insertAfterWindow{;positionFlag}})
```

Parameter|Type|Description
------------|------|----
window|LONGINT|
x|LONGINT|
y|LONGINT|
width|LONGINT|
height|LONGINT|
orderFlag_or_insertAfterWindow|LONGINT|
positionFlag|LONGINT|

```
WND GET POSITION (window;x;y;width;height)
```

Parameter|Type|Description
------------|------|----
window|LONGINT|
x|LONGINT|
y|LONGINT|
width|LONGINT|
height|LONGINT|

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
