# Uranus (Gaia user space kernel) Configuration
DEBUG = true

TARGET = uranus

SOURCE_PATH = .
SOURCE_LIBS = ./lib

SOURCES  = $(SOURCE_PATH)/main.c
SOURCES += $(SOURCE_PATH)/syscall.c
SOURCES += $(SOURCE_PATH)/eventmanager.c

DRIVERS  = $(SOURCE_PATH)/drivers/PIT.c $(SOURCE_PATH)/drivers/VGA.c
DRIVERS += $(SOURCE_PATH)/drivers/keyboard.c $(SOURCE_PATH)/drivers/term.c
DRIVERS += $(SOURCE_PATH)/keyboard_layouts/us.c

SOURCES_LIBS  = $(SOURCE_LIBS)/fixedDict.c $(SOURCE_LIBS)/fixedQueue.c
#SOURCES_LIBS += $(SOURCE_LIBS)/ordered_array.c

OBJS = $(SOURCES:.c=.o) $(DRIVERS:.c=.o) $(SOURCES_LIBS:.c=.o)

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

all : $(TARGET).a

clean :
	$(RM) $(TARGET).a $(OBJS)


# Rules
$(TARGET).a : $(OBJS)
	$(AR) rcs $@ $(OBJS)