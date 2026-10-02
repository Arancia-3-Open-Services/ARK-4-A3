#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <string.h>

PSP_MODULE_INFO("flash4", 0, 1, 0);

int main(int argc, char *argv[]) {
              pspDebugScreenInit();
              pspDebugScreenPrintf("Assigning flash4...\n");
              sceIoAssign("flash4:", "lflash0:0,4", "flashfat4:", IOASSIGN_RDWR, NULL, 0);
              int fd;
              int filecontent;
              pspDebugScreenPrintf("Flashing files...\n");
              fd = sceIoOpen("flash4:/onstack.A3", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *initdata = "Ready"; sceIoWrite(fd, initdata, strlen(initdata)); sceIoClose(fd);};
              fd = sceIoOpen("flash4:/A3/it_postoffice.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
              if (fd >= 0) {const char *write = "On flash4:\nFile is flashed."; sceIoWrite(fd, write, strlen(write)); sceIoClose(fd);};
              pspDebugScreenPrintf("Done.\n");
              sceKernelDelayThread(1000000);
              return 0;
};