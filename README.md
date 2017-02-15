# 4d-plugin-window-control
Better control of window state and position

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|||<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

###Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />


```
minimized:=WND Is minimized (window)
```

Parameter|Type|Description
------------|------|----
window|INT32|
minimized|INT32|

```
maximized:=WND Is maximized (window)
```

Parameter|Type|Description
------------|------|----
window|INT32|
maximized|INT32|

```
WND SET TITLE (window;title)
title:=WND Get title (window)
```

Parameter|Type|Description
------------|------|----
window|INT32|
title|TEXT|

```
WND USE ICON FILE (window;path)
```

Parameter|Type|Description
------------|------|----
window|INT32|
path|TEXT|


```
WND MAXIMIZE (window)
WND MINIMIZE (window)
WND RESTORE (window)
```

Parameter|Type|Description
------------|------|----
window|INT32|

```
WND SET POSITION (window;x;y;width;height{;orderFlag_or_insertAfterWindow{;positionFlag}})
```

Parameter|Type|Description
------------|------|----
window|INT32|
x|INT32|
y|INT32|
width|INT32|
height|INT32|
orderFlag_or_insertAfterWindow|INT32|
positionFlag|INT32|

```
WND GET POSITION (window;x;y;width;height)
```

Parameter|Type|Description
------------|------|----
window|INT32|
x|INT32|
y|INT32|
width|INT32|
height|INT32|

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
