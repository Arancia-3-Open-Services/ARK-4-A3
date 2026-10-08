#include <pspsdk.h>
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
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <pspipl_update.h>
#include <vlf.h>

#include "dcman.h"
#include "main.h"
#include "nandoperations.h"
#include "idstools.h"
#include "idsregeneration.h"

void flash4menu(void) {
int OnMenuSelect(int sel)
{
    void *wi;
    
    switch (sel)
    {
        case 0:
        	vlfGuiMessageDialog("flash4 module removal will now start.", VLF_MD_TYPE_NORMAL | VLF_MD_BUTTONS_NONE);
            sceIoRemove("ms0:/flash4/");
            sceIoRemove("ms0:/flash4.txt");
            vlfGuiMessageDialog("Removal is complete.\nIf you have the built-in flash4 plugin, it will install the modules again.", VLF_MD_TYPE_NORMAL | VLF_MD_BUTTONS_NONE);
        break;
    }    
    
    return VLF_EV_RET_REMOVE_OBJECTS | VLF_EV_RET_REMOVE_HANDLERS;
}

void Menu(int sel)
{
    char *items[] =
    {
        "Remove ms0 flash4 modules"
    };

    vlfGuiCentralMenu(1, items, sel, OnMenuSelect, 0, 0);
    vlfGuiBottomDialog(-1, VLF_DI_ENTER, 1, 0, VLF_DEFAULT, NULL);
}
}