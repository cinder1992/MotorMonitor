#Platform to compile
PLATFORM := my68k

#basic multi-platform sources and directores
SRCDIR := src
INCDIR := include
PLATDIR := $(SRCDIR)/platform/$(PLATFORM)
LIBCDIR := $(SRCDIR)/libc
LIBCINCDIR := $(INCDIR)/libc
SRCS := $(wildcard $(SRCDIR)/*.c)

include ${LIBCDIR}/libc.mk
include ${PLATDIR}/platform.mk

OBJS := $(patsubst %.c,%.o,$(notdir $(SRCS)))
OBJS += $(patsubst %.s,%.s.o, $(notdir $(ASSRCS)))
$(info $(OBJS))

VPATH := $(SRCDIR):$(PLATVPATH):$(LIBCVPATH)

.PHONY: all clean

default: all

mm$(PLATEXT): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.s.o: %.s
	$(AS) -o$@ $<

clean:
	rm -f ${PLATFILES}

all: platform
