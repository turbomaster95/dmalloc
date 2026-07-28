SRCS := malloc.c
OBJS := $(SRCS:.c=.o)

CFLAGS += -fno-builtin -Wall -Wextra -I.

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

clean:
	rm -f $(OBJS)

.PHONY: all clean
