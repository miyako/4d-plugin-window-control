# 4d-plugin-window-control
Better control of window state and position.

## Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|||<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />*|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" /> <img src="https://user-images.githubusercontent.com/1725068/41266195-ddf767b2-6e30-11e8-9d6b-2adf6a9f57a5.png" width="32" height="32" />

- * **Remarks** plugin seems to not work on Windows 32-bit (v17) 

### Releases

[2.3](https://github.com/miyako/4d-plugin-window-control/releases/tag/2.3) fix constant groups, call in main process  

[2.2](https://github.com/miyako/4d-plugin-window-control/releases/tag/2.2)

[2.1](https://github.com/miyako/4d-plugin-window-control/releases/tag/2.1)

### Remarks

Since 17R4, passing the ``HWMD`` of the MDI seems to hang on 4D Server. Workaround was to use ``PA_RunInMainProcess``.

On some versions of Windows 10 Pro 1809 (tested 17763.253), using ``SHGetFileInfo`` to obtain ``HICON`` seems to fail. ``LoadImage``, on the other hand, seems more stable. So the code was change in [2.2](https://github.com/miyako/4d-plugin-window-control/releases/tag/2.2) to use ``LoadImage`` instead.

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
