TARGET := m68k-elf
PLATFORM := my68k
# override CC
CC := $(TARGET)-gcc
AS := $(TARGET)-as
LD := $(TARGET)-gcc
OBJCOPY := $(TARGET)-objcopy

OPTIMISE := 2

SRCDIR := src
INCDIR := include
LIBCDIR := $(SRCDIR)/libc
LIBCINCDIR := $(INCDIR)/libc
PLATDIR := $(SRCDIR)/platform/$(PLATFORM)
CSRCS := $(wildcard $(SRCDIR)/*.c)
LIBCSRCS := $(wildcard $(LIBCDIR)/*.c)
PLATSRCS := $(wildcard $(PLATDIR)/*.c)
COBJS := $(patsubst $(SRCDIR)/%.c,%.o,$(CSRCS))
COBJS += $(patsubst $(LIBCDIR)/%.c,%.o,$(LIBCSRCS))
COBJS += $(patsubst $(PLATDIR)/%.c,%.o,$(PLATSRCS))
ASSRCS := $(wildcard $(PLATDIR)/*.s)
ASOBJS := $(patsubst $(PLATDIR)/%.s,%.s.o,$(ASSRCS))

VPATH := $(SRCDIR):$(PLATDIR):$(LIBCDIR)

LDFLAGS := -march=68000 -ffreestanding -O$(OPTIMISE) -nostdlib -static-libgcc -lgcc -T $(SRCDIR)/platform/$(PLATFORM)/linker.ld
CFLAGS := -I$(INCDIR) -I$(LIBCINCDIR) -march=68010 -std=gnu99 -ffreestanding -O$(OPTIMISE) -Wall -Wextra


.PHONY: all clean

default: all

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.s.o: %.s
	$(AS) -o$@ $<

mm.elf: $(COBJS) $(ASOBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

mm.bin: mm.elf
	$(OBJCOPY) -O binary --gap-fill 0x00 --pad-to 0x100000 $< $@

mm.bin.lo: mm.bin
	$(OBJCOPY) -F binary -i 2 -b 1 $< $@

mm.bin.hi: mm.bin
	$(OBJCOPY) -F binary -i 2 -b 0 $< $@

mm.s68: mm.elf
	$(OBJCOPY) -O srec $< $@
clean:
	rm -f *.bin* *.elf *.s68 *.o*

all: mm.s68 mm.bin.lo mm.bin.hi
