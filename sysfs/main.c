#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "sysfs.h"

int main(void)
{
	int fd;
	int pollret;
	char attr[0x1000] = {0};

	fd = sysfs_open("/sys/kernel/kobject_example/foo", O_RDONLY);
	if (fd == -1)
		return -1;

	pollret = sysfs_poll(fd, -1);

	printf("pollret=%d\n", pollret);

	if (sysfs_read(fd, attr, sizeof attr) == -1)
		return -1;

	printf("attribute value changed to => %s\n", attr);

	sysfs_close(fd);
}

