# Gaia Configuration
DEBUG = true

TARGET = gaia

SOURCE_PATH = .
SOURCE_LIBS = ./lib
PLATFORM = x86

SOURCES  = $(SOURCE_PATH)/gdt.c $(SOURCE_PATH)/heap.c $(SOURCE_PATH)/idt.c
SOURCES += $(SOURCE_PATH)/interruptmanager.c
SOURCES += $(SOURCE_PATH)/irq.c $(SOURCE_PATH)/isr.c
SOURCES += $(SOURCE_PATH)/kheap.c $(SOURCE_PATH)/panic.c $(SOURCE_PATH)/paging.c
SOURCES += $(SOURCE_PATH)/syscall.c $(SOURCE_PATH)/sys/io.c

SOURCES_LIBS = $(SOURCE_LIBS)/ordered_array.c

OBJS  = $(SOURCE_PATH)/asm/$(PLATFORM)/multiboot.o
OBJS += $(SOURCE_PATH)/asm/$(PLATFORM)/gdt.o $(SOURCE_PATH)/asm/$(PLATFORM)/idt.o
OBJS += $(SOURCE_PATH)/asm/$(PLATFORM)/interrupt.o
OBJS += $(SOURCE_PATH)/asm/$(PLATFORM)/irq.o $(SOURCE_PATH)/asm/$(PLATFORM)/isr.o
OBJS += $(SOURCE_PATH)/asm/$(PLATFORM)/process.o $(SOURCE_PATH)/asm/$(PLATFORM)/tss.o

OBJS += $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o)

CINCS  = -I$(SOURCE_PATH)/include -I$(SOURCE_PATH)/../include
CINCS += -I$(SOURCE_PATH)/../uranus -I$(SOURCE_PATH)/../uranus/include

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement #-Werror

ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif
CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -O2 -m32 -nostdinc -fno-builtin -nostdlib -fno-stack-protector

AS_FLAGS = -felf


.PHONY: all clean

all : lib$(TARGET).a

clean :
	$(RM) lib$(TARGET).a $(OBJS)


# Rules
lib$(TARGET).a : $(OBJS)
	$(AR) rcs $@ $(OBJS)
#	$(CC) -o $@ $(OBJS) $(CFLAGS)
#	$(LD) -o $@ $(OBJS) -Ttext 0x100000 -melf_i386

.S.o:
	$(CC) -o $@ -c $< $(CFLAGS)

.s.o:
	nasm $(AS_FLAGS) $<
