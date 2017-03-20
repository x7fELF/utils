/*
 * x7fELF, x7fELF@gmail.com, 2017
 * GNU GPL v2
 */

#include <poll.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int sysfs_open(const char *pathname, int flags)
{
	return open(pathname, flags);
}

ssize_t sysfs_read(int fd, void *buf, size_t count)
{
	return read(fd, buf, count);
}

/* 
 * Opened file is considered as changed, so we need to do dummy
 * read before polling. Without this, poll() will return immediately
 * without blocking.
 */
static ssize_t sysfs_prepare_fd_before_poll(int fd)
{
	char buf;

	return sysfs_read(fd, &buf, 1);
}

off_t sysfs_lseek(int fd, off_t offset, int whence)
{
	return lseek(fd, offset, whence);
}

/* 
 * Based on the kernfs_fop_poll() description, after poll() we
 * have two choices:
 * 
 * Once poll/select indicates that the value has changed, you
 * need to close and re-open the file, or seek to 0 and read again.
 *
 * Seek is my choice.
 */
static int sysfs_prepare_fd_after_poll(int fd)
{
	return sysfs_lseek(fd, 0, SEEK_SET);
}

int sysfs_poll(int fd, int timeout)
{
	int poll_retval;
	struct pollfd poll_fildes;

	poll_fildes.fd = fd;
	poll_fildes.events = POLLERR | POLLPRI;

	if (sysfs_prepare_fd_before_poll(poll_fildes.fd) == -1)
		return -1;

	if ((poll_retval = poll(&poll_fildes, 1, timeout)) == -1)
		return -1;

	if (sysfs_prepare_fd_after_poll(poll_fildes.fd) == -1)
		return -1;
	
	return poll_retval;
}

int sysfs_close(int fd)
{
	return close(fd);
}

