# Gaia Configuration
DEBUG = true

TARGET = gaia

SOURCE_PATH = src
SOURCE_LIBS = src/lib

SOURCES = $(SOURCE_PATH)/main.c

LIB_OBJS  = $(SOURCE_PATH)/libgaia/libgaia.a $(SOURCE_PATH)/uranus/uranus.a
LIB_OBJS += $(SOURCE_PATH)/asm/gaia_asm.a $(SOURCE_PATH)/GaiaLib/GaiaLib.a

OBJS = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o)

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS  = -I$(SOURCE_PATH)/include -I$(SOURCE_PATH)/asm/include
CINCS += -I$(SOURCE_PATH)/GaiaLib/include -I$(SOURCE_PATH)/libgaia/include

ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif

CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -O2 -m32 -nostdinc -fno-builtin -nostdlib


.PHONY: all clean run

all : $(TARGET).out

clean :
	$(MAKE) clean -C $(SOURCE_PATH)/asm
	$(MAKE) clean -C $(SOURCE_PATH)/GaiaLib
	$(MAKE) clean -C $(SOURCE_PATH)/libgaia
	$(MAKE) clean -C $(SOURCE_PATH)/uranus

	$(RM) $(TARGET).out $(OBJS)

run :
	qemu --kernel $(TARGET).out


# Rules
$(TARGET).out : $(OBJS)
	$(MAKE) -C $(SOURCE_PATH)/asm
	$(MAKE) -C $(SOURCE_PATH)/GaiaLib
	$(MAKE) -C $(SOURCE_PATH)/libgaia
	$(MAKE) -C $(SOURCE_PATH)/uranus

	$(CC) -o $@ $(OBJS) $(LIB_OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) $(LIB_OBJS) -Ttext 0x100000 -melf_i386