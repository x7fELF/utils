CC=gcc
CFLAGS=-Wall -Wextra -Werror -O2
TARGET_TEST=main
TARGET_LIB_SHARED=
TARGET_LIB_STATIC=

.PHONY: all
all: $(TARGET_TEST)

.PHONY: $(TARGET_TEST)
$(TARGET_TEST): main.c sysfs.c
	$(CC) $(CFLAGS) -o $(TARGET_TEST) main.c sysfs.c

.PHONY: clean
clean:
	rm -f $(TARGET_TEST)

