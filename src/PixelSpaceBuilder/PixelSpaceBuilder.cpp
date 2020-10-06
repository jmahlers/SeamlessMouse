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
    RECT i = *monitorsInfo.MonitorRects.begin();
    std::cout << " Monitor 1 is " << (i.right - i.left) << " wide.";
    return 0;
}

