# Gaia Configuration
DEBUG = true

TARGET = gaia

SOURCE_PATH = src
SOURCE_LIBS = src/lib

SOURCES       = $(SOURCE_PATH)/main.c
SOURCES      += $(SOURCE_PATH)/gdt.c $(SOURCE_PATH)/idt.c $(SOURCE_PATH)/irq.c
SOURCES      += $(SOURCE_PATH)/isr.c $(SOURCE_PATH)/multiboot.c
#SOURCES      += $(SOURCE_PATH)/kheap.c $(SOURCE_PATH)/paging.c
SOURCES      += $(SOURCE_PATH)/syscall.c
SOURCES      += $(SOURCE_PATH)/common.c

SOURCES_LIBS  = $(SOURCE_LIBS)/stdio.c $(SOURCE_LIBS)/stdlib.c
SOURCES_LIBS += $(SOURCE_LIBS)/string.c
#SOURCES_LIBS += $(SOURCE_LIBS)/ordered_array.c

LIB_OBJS = $(SOURCE_PATH)/asm/gaia_asm.a $(SOURCE_PATH)/uranus/uranus.a

OBJS = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o) $(LIB_OBJS)

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS = -I$(SOURCE_PATH) -I$(SOURCE_PATH)/include
ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif
CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -m32 -nostdinc -fno-builtin -nostdlib -fno-stack-protector


.PHONY: all clean run

all : $(TARGET).out

clean :
	$(RM) $(TARGET).out $(OBJS)
	$(MAKE) clean -C $(SOURCE_PATH)/asm
	$(MAKE) clean -C $(SOURCE_PATH)/uranus

run :
	qemu --kernel $(TARGET).out


# Rules
$(TARGET).out : $(OBJS)
	$(CC) -o $@ $(OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) -Ttext 0x100000 -melf_i386

$(SOURCE_PATH)/asm/gaia_asm.a :
	$(MAKE) -C $(SOURCE_PATH)/asm

$(SOURCE_PATH)/uranus/uranus.a :
	$(MAKE) -C $(SOURCE_PATH)/uranus