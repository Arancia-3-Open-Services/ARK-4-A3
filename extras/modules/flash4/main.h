#include <pspsdk.h>
#include <pspkernel.h>

extern int flash_sizes[4];
extern int totalflash_size;
extern void *sm_buffer1;
extern void *sm_buffer2;
extern void *big_buffer;

extern int SMALL_BUFFER_SIZE;
extern int BIG_BUFFER_SIZE;

int dcGetHardwareInfo(void* a, void *b, void* c, void* d, void* e, void* f, u32* nandsize);
int CallbackThread(SceSize args, void *argp);