ARKROOT = ../../..
TARGET = flash_4
OBJS = main.o
INCDIR = $(ARKROOT)/common/include
CFLAGS := -Os -G0 -Wall -std=gnu99
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp
all: $(TARGET).prx
	psp-packer $(TARGET).prx
clean:
	$(Q)rm -rf main.o
	$(Q)rm -rf flash_4.elf
	$(Q)rm -rf flash_4.prx
PSPSDK ?= $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak