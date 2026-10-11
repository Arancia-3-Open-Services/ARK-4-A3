#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <ark.h>
#include <kubridge.h>
#include <systemctrl.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

// Module Info. I think this is passive for those prx files.
PSP_MODULE_INFO("flash4", 0, 1, 0);
int module_start(int argc, char *argv[]) {
              SceCtrlData pad;
              sceCtrlPeekBufferPositive(&pad, 1);
              if (pad.Buttons & PSP_CTRL_UP)
              {
                flash4menustack();
              };
              int fd;
              char *directs[] = {
                            "ms0:/flash4",
                            "ms0:/flash4/A3",
                            "ms0:/flash4/cel"
              };
              pspDebugScreenInit();
              pspDebugScreenPrintf("Unassigning flash4...\n");

              sceIoUnassign("flash4:");
              sceKernelDelayThread(1000000);

              pspDebugScreenPrintf("Logical Flash Rendering (flash4)...\n");

              sceIoAssign("flash4:", "lflash0:0,4", "flashfat4:", IOASSIGN_RDWR, 0, 0);
              pspDebugScreenPrintf("Formatting flash4:/ to match structures..\n");
              int res = sceIoDevctl("flash4:", 0x3001, 0, 0, 0, 0);
              if (res < 0)
              {
                pspDebugScreenPrintf("Run failed: %08X\n", res);
              } else  {
                pspDebugScreenPrintf("Run OK.\n");
              };
              pspDebugScreenPrintf("Flashing files...\n");
              // Separator.
              fd = sceIoOpen("flash4:/presencefile.A3", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0)
              {
                const char *writepresfile = "This file will be read by flash4 plugin.";
                sceIoWrite(fd, writepresfile, strlen(writepresfile));
                sceIoClose(fd);
                pspDebugScreenPrintf("Run OK.\n");
              } else {
                pspDebugScreenPrintf("Run failed: %08X\n", fd);
              };
              // Separator.
              fd = sceIoOpen("flash4:/onstack.A3", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *initdata = "Ready"; sceIoWrite(fd, initdata, strlen(initdata)); sceIoClose(fd);};
              fd = sceIoOpen("flash4:/A3/it_postoffice.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *write = "On flash4:\nFile is flashed."; sceIoWrite(fd, write, strlen(write)); sceIoClose(fd);};
              fd = sceIoOpen("flash4:/A3/celpostoffice.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *writecelpostoffice =
              "==================================================================\n"
              " CELPostoffice | : |                                    | In place\n"
              " A3            | : | argument:CEL flash4:/celname.txt   | In place\n"
              " A3            | : | argument:NAME flash4:/unitname.txt | In place\n"
              "==================================================================";
              sceIoWrite(fd, writecelpostoffice, strlen(writecelpostoffice)); sceIoClose(fd);};

              pspDebugScreenPrintf("Writing cons to ms0...\n");

              fd = sceIoOpen("ms0:/flash4.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *writeflashfile = 
              "==========================================================\n"
              "A3 | : | <DIR> flash4:/onstack.A3               | In place\n"
              "A3 | : | <DIR> flash4:/A3/it_postoffice.txt     | In place\n"
              "A3 | : | <DIR> ms0:/flash4.txt                  | In place\n"
              "A3 | : | <DIR> flash4:/A3/celpostoffice.txt     | In place\n"
              "A3 | : | <DIR> flash4:/presencefile.A3          | In place\n"
              "==========================================================";
              sceIoWrite(fd, writeflashfile, strlen(writeflashfile)); sceIoClose(fd);};

              pspDebugScreenPrintf("Creating Directories on ms0:/flash4...\n");

              // Creates directories on the memory stick.
              sceIoRmdir("ms0:/flash4/");
              sceKernelDelayThread(5000);
              for (int i = 0; i < 3; i++) {sceIoMkdir(directs[i], 0777);};
              fd = sceIoOpen("flash4:/unitname.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *writenamefile = "name"; sceIoWrite(fd, writenamefile, strlen(writenamefile)); sceIoClose(fd);};
              fd = sceIoOpen("ms0:/flash4/A3/it_postoffice.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *writepostoffice =
              "========================================================\n"
              "A3 | : | <DIR> ms0:/flash4                    | In place\n"
              "========================================================";
              sceIoWrite(fd, writepostoffice, strlen(writepostoffice)); sceIoClose(fd);};
              fd = sceIoOpen("ms0:/flash4/cel/celpostoffice.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *writecelpostoffice2 =
              "===================================================================\n"
              " CELPostoffice | : |                                     | In place\n"
              " A3            | : | argument:CEL: flash4:/celname.txt   | In place\n"
              " A3            | : | argument:NAME: flash4:/unitname.txt | In place\n"
              " A3            | : | argument:NULL: flash4:/cel          | In place\n"
              "===================================================================\n"
              " CELPostOffice | : | argument:GENERALCEL:                | In place\n"
              " CELPostOffice | : | argument:GENERALCEL: flash4:/A3     | In place\n"
              " CELPostOffice | : | argument:GENERALCELBOOTI: cIPL      | In place\n"
              "===================================================================";
              sceIoWrite(fd, writecelpostoffice2, strlen(writecelpostoffice2)); sceIoClose(fd);};

              pspDebugScreenPrintf("Verifying presence of ms0:/flash4...\n");
              
              int file = sceIoOpen("ms0:/flash4.txt", PSP_O_RDONLY, 0);
              if (file < 0)
              {

                pspDebugScreenPrintf("FILE NON-EXISTENT, Going to flash4 management.\n");

                sceKernelDelayThread(1000000);
                flash4menustack();

              } else {
                
                pspDebugScreenPrintf("Done.\n");
                pspDebugScreenPrintf("Starting process.\n");
                sceIoClose(file);
                
                return 0;
              };


            } 