TARGET := m68k-elf
# override CC
CC := $(TARGET)-gcc
AS := $(TARGET)-as
LD := $(TARGET)-gcc
OBJCOPY := $(TARGET)-objcopy

SRCS += $(wildcard $(PLATDIR)/*.c)
ASSRCS += $(wildcard $(PLATDIR)/*.s)
PLATVPATH := $(PLATDIR)

OPTIMISE := 2

LDFLAGS := -march=68000 -ffreestanding -O$(OPTIMISE) -nostdlib -static-libgcc -lgcc -T $(SRCDIR)/platform/$(PLATFORM)/linker.ld
CFLAGS := -I$(INCDIR) -I$(LIBCINCDIR) -march=68010 -std=gnu99 -ffreestanding -O$(OPTIMISE) -Wall -Wextra

PLATFILES := *.bin* *.elf *.o *.s.o

PLATEXT := .elf

.PHONY: platform

mm.bin: mm.elf
	$(OBJCOPY) -O binary --gap-fill 0x00 --pad-to 0x100000 $< $@

mm.bin.lo: mm.bin
	$(OBJCOPY) -F binary -i 2 -b 1 $< $@

mm.bin.hi: mm.bin
	$(OBJCOPY) -F binary -i 2 -b 0 $< $@

mm.s68: mm.elf
	$(OBJCOPY) -O srec $< $@

platform: mm.bin.lo mm.bin.hi
