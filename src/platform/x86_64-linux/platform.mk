TARGET := x86_64-linux
# override CC
CC := gcc
AS := as
LD := gcc
OBJCOPY := objcopy

PLATSRCS += $(wildcard $(PLATDIR)/*.c)
ASSRCS += $(wildcard $(PLATDIR)/*.s)
OBJS += $(patsubst $(PLATDIR)/%.c,%.o,$(PLATSRCS))
OBJS += $(patsubst $(PLATDIR)/%.s,%.s.o,$(ASSRCS))

OPTIMISE := 0

LDFLAGS := -g -O$(OPTIMISE) -nostdlib -static-libgcc -lgcc
CFLAGS := -g -I$(INCDIR) -I$(LIBCINCDIR) -std=gnu99 -O$(OPTIMISE) -Wall -Wextra

PLATFILES := mm *.o *.s.o

.PHONY: platform

mm: $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

platform: mm
