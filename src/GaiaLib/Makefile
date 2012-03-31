# Gaia Configuration
DEBUG = true

TARGET = GaiaLib

SOURCE_PATH = .
SOURCE_LIBS = ./lib

SOURCES = $(SOURCE_PATH)/stdio.c $(SOURCE_PATH)/stdlib.c $(SOURCE_PATH)/string
OBJS = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o)

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS  = -I$(SOURCE_PATH)/include
CINCS += -I$(SOURCE_PATH)/../libgaia/include

ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif

CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -O2 -m32 -nostdinc -fno-builtin -nostdlib


.PHONY: all clean

all : $(TARGET).a

clean :
	$(RM) $(TARGET).a $(OBJS)


# Rules
$(TARGET).a : $(OBJS)
#	$(MAKE) -C $(SOURCE_PATH)/asm

	$(AR) rcs $@ $(OBJS) $(LIB_OBJS)
#	$(CC) -o $@ $(OBJS) $(LIB_OBJS) -m32 -nostdinc -nostdlib -fno-builtin
#	$(LD) -o $@ $(OBJS) $(LIB_OBJS) -Ttext 0x100000 -melf_i386