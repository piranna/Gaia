# Gaia Configuration
DEBUG = true

TARGET = gaia

SOURCE_PATH = .
SOURCE_LIBS = ./lib

SOURCES       = $(SOURCE_PATH)/multiboot.c
SOURCES      += $(SOURCE_PATH)/gdt.c $(SOURCE_PATH)/idt.c $(SOURCE_PATH)/irq.c
SOURCES      += $(SOURCE_PATH)/isr.c $(SOURCE_PATH)/interruptmanager.c
#SOURCES      += $(SOURCE_PATH)/kheap.c $(SOURCE_PATH)/paging.c
SOURCES      += $(SOURCE_PATH)/syscall.c $(SOURCE_PATH)/sys/io.c
SOURCES      += $(SOURCE_PATH)/panic.c

#SOURCES_LIBS = $(SOURCE_LIBS)/ordered_array.c

OBJS = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o)

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS  = -I$(SOURCE_PATH)/include
CINCS += -I$(SOURCE_PATH)/../asm/include -I$(SOURCE_PATH)/../GaiaLib/include

ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif

CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -O2 -m32 -nostdinc -fno-builtin -nostdlib


.PHONY: all clean

all : lib$(TARGET).a

clean :
#	$(MAKE) clean -C $(SOURCE_PATH)/asm

	$(RM) lib$(TARGET).a $(OBJS)


# Rules
lib$(TARGET).a : $(OBJS)
#	$(MAKE) -C $(SOURCE_PATH)/asm

	$(AR) rcs $@ $(OBJS) $(LIB_OBJS)
#	$(CC) -o $@ $(OBJS) $(LIB_OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) $(LIB_OBJS) -Ttext 0x100000 -melf_i386