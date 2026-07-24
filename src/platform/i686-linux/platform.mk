TARGET := x86_64-linux
# override CC
CC := gcc
AS := as
LD := gcc
OBJCOPY := objcopy

SRCS += $(wildcard $(PLATDIR)/*.c)
ASSRCS += $(wildcard $(PLATDIR)/*.s)
PLATVPATH := $(PLATDIR)

OPTIMISE := 0

LDFLAGS := -m32 -g -O$(OPTIMISE) -nostdlib -static-libgcc -lgcc -T $(SRCDIR)/platform/$(PLATFORM)/linker.ld
CFLAGS := -m32 -DPLATFORM_CC=\"$(CC)\" -g -I$(INCDIR) -I$(LIBCINCDIR) -I$(INCDIR)/platform/$(PLATFORM) -std=gnu99 -O$(OPTIMISE) -Wall -Wextra

PLATFILES := coach *.o *.s.o

PLATEXT :=

.PHONY: platform debug

platform: coach

debug: coach
	gdb coach
