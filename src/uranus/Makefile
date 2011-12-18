# Uranus (Gaia user space kernel) Configuration
DEBUG = true

TARGET = uranus

SOURCE_PATH = .
SOURCE_LIBS = ../lib

SOURCES  = $(SOURCE_PATH)/main.c
SOURCES += $(SOURCE_PATH)/syscall_userspace.c
SOURCES += $(SOURCE_PATH)/drivers/PIT.c

#SOURCES_LIBS  = $(SOURCE_LIBS)/stdio.c
#SOURCES_LIBS += $(SOURCE_LIBS)/ordered_array.c

OBJS = $(SOURCES:.c=.o) $(SOURCES_LIBS:.c=.o)

CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement
#CWARN = -Wall -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CINCS = -I$(SOURCE_PATH) -I$(SOURCE_PATH)/include -I$(SOURCE_PATH)/../include
ifeq ($(DEBUG),true)
	CDEBUGS += -g -D__DEBUG__=1
else
    CDEBUGS += -Os
endif
CFLAGS = $(CWARN) $(CDEBUGS) $(CINCS) \
         -fno-strict-aliasing \
         -m32 -nostdinc -fno-builtin -nostdlib -fno-stack-protector


.PHONY: all clean run

all : $(TARGET).a

clean :
	$(RM) $(TARGET).a $(OBJS)


# Rules
$(TARGET).a : $(OBJS)
	$(AR) rcs $@ $(OBJS)