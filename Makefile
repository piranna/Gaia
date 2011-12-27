# Gaia Configuration
DEBUG = true

TARGET = gaia

SOURCE_PATH = src
SOURCE_LIBS = src/lib

SOURCES = $(SOURCE_PATH)/main.c

SOURCES_LIBS  = $(SOURCE_LIBS)/stdio.c $(SOURCE_LIBS)/stdlib.c
SOURCES_LIBS += $(SOURCE_LIBS)/string.c

LIB_OBJS  = $(SOURCE_PATH)/libgaia/libgaia.a $(SOURCE_PATH)/uranus/uranus.a
LIB_OBJS += $(SOURCE_PATH)/libgaia/asm/gaia_asm.a

OBJS = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o)

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS = -I$(SOURCE_PATH)/include -I$(SOURCE_PATH)/libgaia/include
ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif
CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -m32 -nostdinc -fno-builtin -nostdlib -fno-stack-protector

LD_FLAGS = -Tlink.ld


.PHONY: all clean run

all : $(TARGET).out

clean :
	$(MAKE) clean -C $(SOURCE_PATH)/libgaia
	$(MAKE) clean -C $(SOURCE_PATH)/libgaia/asm
	$(MAKE) clean -C $(SOURCE_PATH)/uranus

	$(RM) $(TARGET).out $(OBJS)

run :
	qemu --kernel $(TARGET).out
#	qemu --kernel $(TARGET).out -m 196


# Rules
$(TARGET).out : $(OBJS)
	$(MAKE) -C $(SOURCE_PATH)/libgaia
	$(MAKE) -C $(SOURCE_PATH)/libgaia/asm
	$(MAKE) -C $(SOURCE_PATH)/uranus

	$(LD) $(LD_FLAGS) -o $@ $(OBJS) $(LIB_OBJS) -melf_i386
#	$(CC) -o $@ $(OBJS) $(LIB_OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) $(LIB_OBJS) -Ttext 0x100000 -melf_i386