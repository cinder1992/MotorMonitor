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

LDFLAGS := -g -O$(OPTIMISE) -nostdlib -static-libgcc -lgcc
CFLAGS := -g -I$(INCDIR) -I$(LIBCINCDIR) -std=gnu99 -O$(OPTIMISE) -Wall -Wextra

PLATFILES := mm *.o *.s.o

PLATEXT :=

.PHONY: platform debug

platform: mm

debug: mm
	gdb mm
