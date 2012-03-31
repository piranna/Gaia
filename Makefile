# Gaia Configuration
DEBUG = true

TARGET = gaia
SOURCE_PATH = src
SOURCES = $(SOURCE_PATH)/main.c
SOURCES += $(SOURCE_PATH)/descriptor_tables.c $(SOURCE_PATH)/isr.c $(SOURCE_PATH)/common.c
SOURCES += $(SOURCE_PATH)/include/stdio.c
OBJS = $(SOURCES:.c=.o) $(SOURCE_PATH)/multiboot/boot.o
OBJS += $(SOURCE_PATH)/gdt.o $(SOURCE_PATH)/interrupt.o

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS = -I$(SOURCE_PATH) -I$(SOURCE_PATH)/include -I$(SOURCE_PATH)/multiboot
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

run :
	qemu --kernel $(TARGET).out


# Rules
$(TARGET).out : $(OBJS)
	$(CC) -o $@ $(OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) -Ttext 0x100000 -melf_i386

$(SOURCE_PATH)/multiboot/boot.o:
	$(CC) -o $@ -c $(SOURCE_PATH)/multiboot/boot.S -m32 -nostdinc -nostdlib -fno-builtin

$(SOURCE_PATH)/gdt.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/gdt.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_PATH)/gdt.s

$(SOURCE_PATH)/interrupt.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/interrupt.s -m32 -nostdinc -nostdlib -fno-builtin
	nasm $(ASFLAGS) $(SOURCE_PATH)/interrupt.s