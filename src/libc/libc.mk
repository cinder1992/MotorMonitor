SRCS += $(wildcard $(LIBCDIR)/*.c)
SRCS += $(wildcard $(LIBCDIR)/string/*.c)
SRCS += $(wildcard $(LIBCDIR)/stdio/*.c)

LIBCVPATH := $(LIBCDIR):$(LIBCDIR)/string:$(LIBCDIR)/stdio
