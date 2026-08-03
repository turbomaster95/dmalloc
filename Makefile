BLDDIR := build/
OBJDIR := $(BLDDIR)obj/
SRCS   := malloc.c free.c calloc.c realloc.c
OBJS   := $(patsubst %.c,$(OBJDIR)%.o,$(SRCS))
TARGET := $(BLDDIR)dmalloc.a

CFLAGS += -fno-builtin -Wall -Wextra -I. -Iinclude

all: $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -f $(TARGET)
	rm -rf $(BLDDIR)

.PHONY: all clean
