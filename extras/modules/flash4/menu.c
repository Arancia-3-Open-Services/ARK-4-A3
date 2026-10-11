#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>

#include "main.h"

void flash4menustack(void)
{
    pspDebugScreenInit();
    pspDebugScreenSetTextColor(0xFF0000FF);
    pspDebugScreenPrintf("flash4:/ Management *\n");
    pspDebugScreenPrintf("*********************\n");
    pspDebugScreenPrintf("\n");
    pspDebugScreenSetTextColor(0xFFFFFFFF);
    pspDebugScreenPrintf("* Remove flash4:/ related modules on ms0:/  * Button: Cross\n");
    pspDebugScreenPrintf("* Check injected flash4:/ file              * Button: Circle\n");
    pspDebugScreenPrintf("* Unassign flash4:/                         * Button: Square\n");
    pspDebugScreenPrintf("* Exit from flash4:/ Management             * Button: Triangle\n");
    pspDebugScreenPrintf("\n");
    pspDebugScreenPrintf("Logs:\n");
    pspDebugScreenPrintf("\n");
    while(1)
    {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);
        // BUTTONS.
        if (pad.Buttons & PSP_CTRL_TRIANGLE)
        {
            pspDebugScreenClear();
            pspDebugScreenPrintf("Exiting...\n");
            return 0;
        };
        if (pad.Buttons & PSP_CTRL_CROSS)
        {
            pspDebugScreenPrintf("Removing Modules...\n");
            sceIoRemove("ms0:/flash4.txt");
            sceIoRmdir("ms0:/flash4/cel");
            sceIoRmdir("ms0:/flash4/A3");
            sceIoRmdir("ms0:/flash4/");
            pspDebugScreenPrintf("Removal is complete. This plugin will re-install the modules at reboot.\n");
            sceKernelDelayThread(1000000);
        };
    };
}
