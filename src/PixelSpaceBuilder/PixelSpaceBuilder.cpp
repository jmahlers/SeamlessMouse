#include <Windows.h>
#include <vector>
#include <iostream>
#include "PixelSpaceBuilder.h"

struct PixelSpaceBuilder::MonitorsInfo {
    //Rectangles of display's virtual screen coordinates
    std::vector<RECT> MonitorRects;
    static BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData) {
        MonitorsInfo* pThis = reinterpret_cast<MonitorsInfo*>(pData);
        pThis->MonitorRects.push_back(*lprcMonitor);
        return TRUE;
    }

    MonitorsInfo() {
        //Relevant: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumdisplaymonitors
        EnumDisplayMonitors(0, 0, MonitorEnum, (LPARAM)this);
    }
};


int PixelSpaceBuilder::buildPixelSpace() {

    MonitorsInfo monitorsInfo;
    std::cout << "You have " << monitorsInfo.MonitorRects.size() << " monitors connected.";
    auto i = monitorsInfo.MonitorRects.begin();
    RECT display = *i;
    std::cout << " Monitor 1 is " << (display.right - display.left) << " wide.";
    std::cout << " Left is " << display.left << ". Right is " << display.right <<". \n";
    display = *(i+1);
    std::cout << "Monitor 2 is " << (display.right - display.left) << " wide.";
    std::cout << " Left is " << display.left << ". Right is " << display.right;
    SetCursorPos(2560, 0);
    return 0;
}

int PixelSpaceBuilder::buildRealSpace()
{
    return 0;
}

