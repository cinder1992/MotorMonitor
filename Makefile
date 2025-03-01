#Platform to compile
PLATFORM := my68k

#basic multi-platform sources and directores
SRCDIR := src
INCDIR := include
LIBCDIR := $(SRCDIR)/libc
LIBCINCDIR := $(INCDIR)/libc
PLATDIR := $(SRCDIR)/platform/$(PLATFORM)
SRCS := $(wildcard $(SRCDIR)/*.c)
LIBCSRCS := $(wildcard $(LIBCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,%.o,$(SRCS))
OBJS += $(patsubst $(LIBCDIR)/%.c,%.o,$(LIBCSRCS))

include ${PLATDIR}/platform.mk

VPATH := $(SRCDIR):$(PLATDIR):$(LIBCDIR)

.PHONY: all clean

default: all

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.s.o: %.s
	$(AS) -o$@ $<

clean:
	rm -f ${PLATFILES}

all: platform
