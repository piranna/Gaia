# Gaia assembler Configuration
DEBUG = true

TARGET = gaia_asm
PLATFORM = x86

SOURCE_PATH = $(PLATFORM)

OBJS  = $(SOURCE_PATH)/multiboot.o
OBJS += $(SOURCE_PATH)/gdt.o $(SOURCE_PATH)/idt.o
OBJS += $(SOURCE_PATH)/irq.o $(SOURCE_PATH)/isr.o
OBJS += $(SOURCE_PATH)/process.o $(SOURCE_PATH)/tss.o

CINCS = -I../include
CFLAGS = $(CINCS) \
         -m32 -nostdinc -fno-builtin -nostdlib -fno-stack-protector

ASFLAGS=-felf


.PHONY: all clean

all : $(TARGET).a

clean :
	$(RM) $(TARGET).out $(OBJS)


# Rules
$(TARGET).a : $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(SOURCE_PATH)/multiboot.o:
	$(CC) -o $@ -c $(SOURCE_PATH)/multiboot.S $(CFLAGS)

$(SOURCE_PATH)/gdt.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/gdt.s $(CFLAGS)
	nasm $(ASFLAGS) $(SOURCE_PATH)/gdt.s

$(SOURCE_PATH)/idt.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/idt.s $(CFLAGS)
	nasm $(ASFLAGS) $(SOURCE_PATH)/idt.s

$(SOURCE_PATH)/irq.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/irq.s $(CFLAGS)
	nasm $(ASFLAGS) $(SOURCE_PATH)/irq.s

$(SOURCE_PATH)/isr.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/isr.s $(CFLAGS)
	nasm $(ASFLAGS) $(SOURCE_PATH)/isr.s

$(SOURCE_PATH)/process.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/process.s $(CFLAGS)
	nasm $(ASFLAGS) $(SOURCE_PATH)/process.s

$(SOURCE_PATH)/tss.o:
#	$(CC) -o $@ -c $(SOURCE_PATH)/tss.s $(CFLAGS)
	nasm $(ASFLAGS) $(SOURCE_PATH)/tss.s