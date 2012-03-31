# Gaia Configuration
DEBUG = true

TARGET = gaia
PLATFORM = x86

SOURCE_PATH = src
SOURCE_LIBS = src/lib
SOURCE_ASM_PATH = src/asm/$(PLATFORM)

SOURCES       = $(SOURCE_PATH)/main.c
SOURCES      += $(SOURCE_PATH)/gdt.c $(SOURCE_PATH)/idt.c $(SOURCE_PATH)/irq.c
SOURCES      += $(SOURCE_PATH)/isr.c $(SOURCE_PATH)/multiboot.c
#SOURCES      += $(SOURCE_PATH)/kheap.c $(SOURCE_PATH)/paging.c
SOURCES      += $(SOURCE_PATH)/syscall.c
SOURCES      += $(SOURCE_PATH)/common.c $(SOURCE_PATH)/video.c

SOURCES_LIBS  = $(SOURCE_LIBS)/stdio.c $(SOURCE_LIBS)/stdlib.c
#SOURCES_LIBS += $(SOURCE_LIBS)/ordered_array.c

OBJS_ASM  = $(SOURCE_ASM_PATH)/multiboot.o
OBJS_ASM += $(SOURCE_ASM_PATH)/gdt.o $(SOURCE_ASM_PATH)/idt.o
OBJS_ASM += $(SOURCE_ASM_PATH)/irq.o $(SOURCE_ASM_PATH)/isr.o
OBJS_ASM += $(SOURCE_ASM_PATH)/process.o $(SOURCE_ASM_PATH)/tss.o

OBJS  = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o) $(OBJS_ASM)
OBJS += $(SOURCE_PATH)/uranus/uranus.a

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

ASFLAGS=-felf


.PHONY: all clean run

all : $(TARGET).out

clean :
	$(RM) $(TARGET).out $(OBJS)
	$(MAKE) clean -C $(SOURCE_PATH)/uranus

run :
	qemu --kernel $(TARGET).out


# Rules
$(TARGET).out : $(OBJS)
	$(CC) -o $@ $(OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) -Ttext 0x100000 -melf_i386

$(SOURCE_PATH)/uranus/uranus.a :
	$(MAKE) -C $(SOURCE_PATH)/uranus

$(SOURCE_ASM_PATH)/multiboot.o:
	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/multiboot.S $(CFLAGS)
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/multiboot.S -m32 -nostdinc -nostdlib -fno-builtin

$(SOURCE_ASM_PATH)/gdt.o:
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/gdt.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_ASM_PATH)/gdt.s

$(SOURCE_ASM_PATH)/idt.o:
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/idt.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_ASM_PATH)/idt.s

$(SOURCE_ASM_PATH)/irq.o:
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/irq.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_ASM_PATH)/irq.s

$(SOURCE_ASM_PATH)/isr.o:
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/isr.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_ASM_PATH)/isr.s

$(SOURCE_ASM_PATH)/process.o:
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/process.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_ASM_PATH)/process.s

$(SOURCE_ASM_PATH)/tss.o:
#	$(CC) -o $@ -c $(SOURCE_ASM_PATH)/tss.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_ASM_PATH)/tss.s