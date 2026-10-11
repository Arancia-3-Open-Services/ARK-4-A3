#include <pspsdk.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspsuspend.h>
#include <psppower.h>
#include <pspreg.h>
#include <psprtc.h>
#include <psputils.h>
#include <pspwlan.h>
#include <systemctrl.h>
#include <kubridge.h>
#include <stdlib.h>
#include <vlf.h>

#include "dcman.h"
#include "main.h"
#include "nandoperations.h"
#include "idstools.h"
#include "idsregeneration.h"

static int OnMenuSelect(int sel) {
    switch (sel) {
        case 0: 
        {
            SceUID dir = sceIoDopen("ms0:/flash4");
            if (dir >= 0) {
                SceIoDirent entry;
                memset(&entry, 0, sizeof(SceIoDirent));
                while (sceIoDread(dir, &entry) > 0) {
                    if (strcmp(entry.d_name, ".") != 0 && strcmp(entry.d_name, "..") != 0) {
                        char filepath[128];
                        snprintf(filepath, sizeof(filepath), "ms0:/flash4/%s", entry.d_name);
                        sceIoRemove(filepath);
                    }
                }
                sceIoDclose(dir);
                sceIoRmdir("ms0:/flash4");
            }
            sceIoRemove("ms0:/flash4.txt");

            vlfGuiMessageDialog("Removal is complete.\nIf you have the built-in flash_4 plugin, it will re-install the modules.", VLF_MD_TYPE_NORMAL | VLF_MD_BUTTONS_NONE);
            flash4menu(0);
        }
    }

    return VLF_EV_RET_REMOVE_OBJECTS | VLF_EV_RET_REMOVE_HANDLERS;
}
int OnBackToNANDMenuFromNO(int enter)
{
    if (!enter)
    {
        vlfGuiCancelCentralMenu();
        vlfGuiCancelBottomDialog();
        NandOperationsMenu(0);		
    }

    return VLF_EV_RET_NOTHING;
}

void flash4menu(int sel)
{
    char *items[] = {
        "Remove ms0 flash4 modules"
    };

    vlfGuiCentralMenu(1, items, sel, OnMenuSelect, 0, 0);
    vlfGuiBottomDialog(VLF_DI_BACK, VLF_DI_ENTER, 1, 1, VLF_DEFAULT, OnBackToNANDMenuFromNO);
}

